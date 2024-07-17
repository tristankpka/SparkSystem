//
// Created by Klemp on 11-Jul-24.
//

#include "ComponentManager.h"

void ComponentManager::removeAllComponents(Entity::Id entityId) {
    // TODO foreach ?
    for (std::size_t i = 0; i < MAX_COMPONENTS_PER_ENTITY; ++i) {
        entityComponentMask[entityId].reset(i);
    }
    entityComponentMask.erase(entityId);
}