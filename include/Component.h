//
// Created by Klemp on 11-Jul-24.
//

#ifndef COMPONENT_H
#define COMPONENT_H

#include <type_traits>
#include <cstdint>
#include <variant>

#include "components/Position.h"
#include "components/Velocity.h"

// Concept to check if a type is a valid component (i.e., is a plain data structure)
template<typename T>
concept ValidComponent = requires {
    std::is_trivially_copyable_v<T> && std::is_standard_layout_v<T>;
};

template<ValidComponent T>
class  Component {
public:
    T value;
    Component() = default;
    Component(const Component&) = delete; // Disallow copy
    Component& operator=(const Component&) = delete; // Disallow copy assignment
    Component(Component&&) noexcept {} // Allow move
    Component& operator=(Component&&) noexcept {return *this;} // Allow move assignement

    explicit Component(T data) : value(std::move(data)) {}
};

static_assert(ValidComponent<Position>);
static_assert(ValidComponent<Velocity>);


#endif //COMPONENT_H
