//
// Created by Klemp on 16-Jul-24.
//

#include "SystemManager.h"
#include "System.h"  // for System

void SystemManager::updateSystems() const {
    for (const auto& system: m_systems) {
        // Todo implement game loop
        system.second->update();
    }
}
