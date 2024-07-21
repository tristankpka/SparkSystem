//
// Created by Klemp on 16-Jul-24.
//

#include "SystemManager.h"

void SystemManager::updateSystems() const {
    for (const auto& system: systems) {
        // Todo implement game loop
        system.second->update();
    }
}
