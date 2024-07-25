//
// Created by Tristan Klempka on 25/07/2024.
//

#include "EventDispatcher.h"

#include <utility>  // for move

Event::Event(EventType type, Entity::Id entityId, std::optional<Entity::Id> parentId)
    : type(type), entityId(entityId), parentId(parentId) {}

EventBuilder::EventBuilder(EventType type, Entity::Id entityId)
    : event(type, entityId) {}

EventBuilder& EventBuilder::withParentId(Entity::Id parentId) {
    event.parentId = parentId;
    return *this;
}

EventBuilder& EventBuilder::withChildId(Entity::Id childId) {
    event.childId = childId;
    return *this;
}

Event EventBuilder::build() const {
    return event;
}

void EventDispatcher::subscribe(EventType eventType, EventCallback callback) {
    listeners[eventType].push_back(std::move(callback));
}

void EventDispatcher::dispatch(const Event& event) const {
    auto it = listeners.find(event.type);
    if (it != listeners.end()) {
        for (const auto& listener : it->second) {
            listener(event);
        }
    }
}