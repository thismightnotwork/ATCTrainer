#include "ATCTrainerPlugin.h"
#include <iostream>

// Dummy HTTP + Logger implementations
class MyHttpClient : public ECFMP::Plugin::HttpClient {
public:
    ECFMP::Plugin::HttpResponse Get(const std::string& url) override {
        std::cout << "[HTTP] GET " << url << std::endl;
        return {200, "{}"};
    }
};

class MyLogger : public ECFMP::Plugin::Logger {
public:
    void Log(const std::string& msg) override {
        std::cout << "[ECFMP] " << msg << std::endl;
    }
};

CATCTrainerPlugin::CATCTrainerPlugin() {
    auto http = std::make_shared<MyHttpClient>();
    auto logger = std::make_shared<MyLogger>();

    ecfmp = ECFMP::Plugin::SdkFactory::Build()
        .WithLogger(logger)
        .WithHttpClient(http)
        .Instance();

    std::cout << "ATC Trainer Plugin initialized with ECFMP SDK.\n";
}

CATCTrainerPlugin::~CATCTrainerPlugin() {
    if (ecfmp) ecfmp->Dispose();
}

void CATCTrainerPlugin::OnTimer(int time) {
    tickCount++;
    if (ecfmp) ecfmp->OnEuroscopeTimerTick();
    if (tickCount % 10 == 0)
        std::cout << "Timer tick: " << tickCount << "\n";
}
