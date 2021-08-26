#pragma once

#include <mutex>
#include "Common/ESDBasePlugin.h"

namespace ACC {
    class ACCHelper;
}

class CallBackTimer;

class RacingDeckPlugin : public ESDBasePlugin
{
public:
    RacingDeckPlugin();
    virtual ~RacingDeckPlugin();
    
    void KeyDownForAction(const std::string& inAction, const std::string& inContext, const json &inPayload, const std::string& inDeviceID) override;
    void KeyUpForAction(const std::string& inAction, const std::string& inContext, const json &inPayload, const std::string& inDeviceID) override;
    
    void WillAppearForAction(const std::string& inAction, const std::string& inContext, const json &inPayload, const std::string& inDeviceID) override;
    void WillDisappearForAction(const std::string& inAction, const std::string& inContext, const json &inPayload, const std::string& inDeviceID) override;
    
    void DeviceDidConnect(const std::string& inDeviceID, const json &inDeviceInfo) override;
    void DeviceDidDisconnect(const std::string& inDeviceID) override;
    
    void SendToPlugin(const std::string& inAction, const std::string& inContext, const json &inPayload, const std::string& inDeviceID) override;

private:

    void UpdateTimer();

    std::mutex mVisibleContextsMutex;
    std::set<std::string> mVisibleContexts;

    CallBackTimer* mTimer;
    ACC::ACCHelper* mHelper;
};
