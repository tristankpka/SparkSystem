//
// Created by Tristan Klempka on 22/07/2024.
//

#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

#include <unordered_map>
#include <vector>
#include <functional>
#include <optional>
#include "Entity.h"

enum class EventType {
    EntityUpdated,
    EntityChildAdded,
    ComponentAdded,
    ComponentRemoved,
    EntityCreated,
    EntityDestroyed,

    TransformChanged,
};

struct Event {
    EventType type;
    Entity::Id entityId;
    std::optional<Entity::Id> parentId;
    std::optional<Entity::Id> childId;

    Event(EventType type, Entity::Id entityId, std::optional<Entity::Id> parentId = std::nullopt);
};

class EventBuilder {
public:
    explicit EventBuilder(EventType type, Entity::Id entityId);

    EventBuilder& withParentId(Entity::Id parentId);
    EventBuilder& withChildId(Entity::Id childId);
    [[nodiscard]] Event build() const;

private:
    Event event;
};

class EventDispatcher {
public:
    using EventCallback = std::function<void(const Event&)>;

    void subscribe(EventType eventType, EventCallback callback);
    void dispatch(const Event& event) const;

private:
    std::unordered_map<EventType, std::vector<EventCallback>> listeners;
};

#endif //EVENTDISPATCHER_H
