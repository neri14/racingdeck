#include "RacingDeckPlugin.h"
#include "ACCHelper.h"

#include <atomic>
#include "Common/ESDConnectionManager.h"

class CallBackTimer
{
public:
    CallBackTimer() :_execute(false) { }

    ~CallBackTimer()
    {
        if (_execute.load(std::memory_order_acquire))
        {
            stop();
        };
    }

    void stop()
    {
        _execute.store(false, std::memory_order_release);
        if (_thd.joinable())
            _thd.join();
    }

    void start(int interval, std::function<void(void)> func)
    {
        if (_execute.load(std::memory_order_acquire))
        {
            stop();
        };
        _execute.store(true, std::memory_order_release);
        _thd = std::thread([this, interval, func]()
            {
                while (_execute.load(std::memory_order_acquire))
                {
                    func();
                    std::this_thread::sleep_for(std::chrono::milliseconds(interval));
                }
            });
    }

    bool is_running() const noexcept
    {
        return (_execute.load(std::memory_order_acquire) && _thd.joinable());
    }

private:
    std::atomic<bool> _execute;
    std::thread _thd;
};

RacingDeckPlugin::RacingDeckPlugin()
{
    mHelper = new ACC::ACCHelper();
    mTimer = new CallBackTimer();
    mTimer->start(10, [this]()
        {
            this->UpdateTimer();
        });
}

RacingDeckPlugin::~RacingDeckPlugin()
{
    if (mHelper != nullptr)
    {
        delete mHelper;
        mHelper = nullptr;
    }
    if (mTimer != nullptr)
    {
        mTimer->stop();

        delete mTimer;
        mTimer = nullptr;
    }
}

void RacingDeckPlugin::UpdateTimer() //boilerplate code
{
    ACC::ACCStatus accStatus = mHelper->getUpdate();

    if (mConnectionManager != nullptr)
    {
        mVisibleContextsMutex.lock();
        for (const std::string& context : mVisibleContexts)
        {
            mConnectionManager->SetTitle(std::to_string(accStatus.lights), context, kESDSDKTarget_HardwareAndSoftware);
        }
        mVisibleContextsMutex.unlock();
    }
}

void RacingDeckPlugin::KeyDownForAction(const std::string& inAction, const std::string& inContext, const json &inPayload, const std::string& inDeviceID)
{
}

void RacingDeckPlugin::KeyUpForAction(const std::string& inAction, const std::string& inContext, const json &inPayload, const std::string& inDeviceID)
{
}

void RacingDeckPlugin::WillAppearForAction(const std::string& inAction, const std::string& inContext, const json &inPayload, const std::string& inDeviceID)
{
    // Remember the context
    mVisibleContextsMutex.lock();
    mVisibleContexts.insert(inContext);
    mVisibleContextsMutex.unlock();
}

void RacingDeckPlugin::WillDisappearForAction(const std::string& inAction, const std::string& inContext, const json &inPayload, const std::string& inDeviceID)
{
    // Remove the context
    mVisibleContextsMutex.lock();
    mVisibleContexts.erase(inContext);
    mVisibleContextsMutex.unlock();
}

void RacingDeckPlugin::DeviceDidConnect(const std::string& inDeviceID, const json &inDeviceInfo)
{
}

void RacingDeckPlugin::DeviceDidDisconnect(const std::string& inDeviceID)
{
}

void RacingDeckPlugin::SendToPlugin(const std::string& inAction, const std::string& inContext, const json &inPayload, const std::string& inDeviceID)
{
}
