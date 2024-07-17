//
// Created by Klemp on 12-Jul-24.
//

#ifndef VELOCITY_H
#define VELOCITY_H

#include "Component.h"

struct Velocity {
    float dx, dy;
};

static_assert(ValidComponent<Velocity>);

#endif //VELOCITY_H
