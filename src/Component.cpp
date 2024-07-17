//
// Created by Klemp on 11-Jul-24.
//
#include "Component.h"

struct Position {
    float x, y;
};

struct Velocity {
    float dx, dy;
};

// Ensure our components satisfy the Component concept
static_assert(ValidComponent<Position>);
static_assert(ValidComponent<Velocity>);