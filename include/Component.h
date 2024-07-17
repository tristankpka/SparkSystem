//
// Created by Klemp on 11-Jul-24.
//

#ifndef COMPONENT_H
#define COMPONENT_H

#include <type_traits>
#include <cstdint>

// Concept to check if a type is a valid component (i.e., is a plain data structure)
template<typename T>
concept ValidComponent = requires {
    std::is_trivially_copyable_v<T> && std::is_standard_layout_v<T>;
};

template<ValidComponent T>
class Component {
public:
    using Id = std::uint16_t;
    static Id getId();

private:
    static Id nextId;
};

#include "Component.tpp"

#endif //COMPONENT_H
