#pragma once
#include "EuroScopePlugIn.h"
#include <memory>
#include <string>
#include <ECFMP.h>

class CATCTrainerPlugin : public CPlugIn {
private:
    std::shared_ptr<ECFMP::Plugin::ISdk> ecfmp;
    int tickCount = 0;

public:
    CATCTrainerPlugin();
    virtual ~CATCTrainerPlugin();

    void OnTimer(int time) override;
};
