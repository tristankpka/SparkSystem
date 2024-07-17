//
// Created by Klemp on 12-Jul-24.
//

#ifndef POSITION_H
#define POSITION_H

#include "Component.h"

struct Position {
    float x, y;
};

static_assert(ValidComponent<Position>);

#endif //POSITION_H
