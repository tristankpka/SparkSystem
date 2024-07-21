//
// Created by Klemp on 11-Jul-24.
//

#include "ComponentManager.h"

void ComponentManager::entityDestroyed(const Entity::Id entityId) {
    componentMaps.erase(entityId);
}