//
// Created by Klemp on 12-Jul-24.
//

#ifndef SYSTEM_H
#define SYSTEM_H

class System {
public:
    virtual ~System() = default;

    virtual void update() = 0;
};

#endif //SYSTEM_H
