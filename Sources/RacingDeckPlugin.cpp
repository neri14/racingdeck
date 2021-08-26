#include "RacingDeckPlugin.h"
#include "ACCHelper.h"
#include "GameState.h"
#include "Images.h"
#include "Windows/KeyboardHandler.h"

#include <atomic>
#include <map>
#include <WinUser.h>
#include "Common/ESDConnectionManager.h"

namespace Consts {
    const std::string headlightsAction = "it.rokosz.racingdeck.headlights";
    const std::string rainLightAction = "it.rokosz.racingdeck.rainlight";
    const std::string wipersAction = "it.rokosz.racingdeck.wipers";

    const std::map< std::string, std::vector<WORD>> actionKeys = {
        {headlightsAction, {0x4c}}, // L
        {rainLightAction, {VK_CONTROL, 0x4c}}, //Ctrl + L
        {wipersAction, {VK_LMENU, 0x52}} //Alt + R
    };

    const int noVal = -127;
}

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
    accHelper = new ACC::ACCHelper();
    callbackTimer = new CallBackTimer();
    callbackTimer->start(100, [this]()
        {
            this->UpdateStates();
        });
}

RacingDeckPlugin::~RacingDeckPlugin()
{
    if (accHelper != nullptr)
    {
        delete accHelper;
        accHelper = nullptr;
    }
    if (callbackTimer != nullptr)
    {
        callbackTimer->stop();

        delete callbackTimer;
        callbackTimer = nullptr;
    }
}

void RacingDeckPlugin::UpdateStates()
{
    GameState state = accHelper->getUpdate();

    if (mConnectionManager != nullptr)
    {
        mutex.lock();
        for (const auto& item : contextsActions) {
            if (item.second == Consts::headlightsAction) {
                if (contextsStates[item.first] != static_cast<int>(state.headlights)) {
                    mConnectionManager->SetImage(Images::getImage(state.headlights), item.first, kESDSDKTarget_HardwareAndSoftware);
                    contextsStates[item.first] = static_cast<int>(state.headlights);
                }
            }
            else if (item.second == Consts::rainLightAction) {
                if (contextsStates[item.first] != static_cast<int>(state.rainLight)) {
                    mConnectionManager->SetImage(Images::getImage(state.rainLight), item.first, kESDSDKTarget_HardwareAndSoftware);
                    contextsStates[item.first] = static_cast<int>(state.rainLight);
                }
            }
            else if (item.second == Consts::wipersAction) {
                if (contextsStates[item.first] != static_cast<int>(state.wipers)) {
                    mConnectionManager->SetImage(Images::getImage(state.wipers), item.first, kESDSDKTarget_HardwareAndSoftware);
                    contextsStates[item.first] = static_cast<int>(state.wipers);
                }
            }
        }
        mutex.unlock();
    }
}

void RacingDeckPlugin::KeyDownForAction(const std::string& inAction, const std::string& inContext, const json &inPayload, const std::string& inDeviceID)
{
    auto it = Consts::actionKeys.find(inAction);

    if (it != Consts::actionKeys.end()) {
        keysDown(it->second);
    }
}

void RacingDeckPlugin::KeyUpForAction(const std::string& inAction, const std::string& inContext, const json &inPayload, const std::string& inDeviceID)
{
    auto it = Consts::actionKeys.find(inAction);

    if (it != Consts::actionKeys.end()) {
        keysUp(it->second);
    }
    UpdateStates();
}

void RacingDeckPlugin::WillAppearForAction(const std::string& inAction, const std::string& inContext, const json &inPayload, const std::string& inDeviceID)
{
    // Remember the context
    mutex.lock();
    contextsActions[inContext] = inAction;
    contextsStates[inContext] = Consts::noVal;
    mutex.unlock();
}

void RacingDeckPlugin::WillDisappearForAction(const std::string& inAction, const std::string& inContext, const json &inPayload, const std::string& inDeviceID)
{
    // Remove the context
    mutex.lock();
    contextsActions.erase(inContext);
    contextsStates.erase(inContext);
    mutex.unlock();
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
