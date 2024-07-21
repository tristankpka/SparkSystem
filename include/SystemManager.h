//
// Created by Klemp on 16-Jul-24.
//

#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include "System.h"
#include <vector>
#include <typeindex>
#include <unordered_map>

class SystemManager {
public:
    template<typename T, typename... Args>
    std::shared_ptr<T> registerSystem(Args&&... args);

    void updateSystems() const;

private:
    std::unordered_map<std::type_index, std::shared_ptr<System>> systems;
};

#include "SystemManager.tpp"

#endif //SYSTEMMANAGER_H
