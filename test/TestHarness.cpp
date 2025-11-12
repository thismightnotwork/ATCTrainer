#include "../plugin/ATCTrainerPlugin.h"
#include <thread>
#include <chrono>

int main() {
    CATCTrainerPlugin plugin;

    for (int i = 0; i < 30; ++i) {
        plugin.OnTimer(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}
