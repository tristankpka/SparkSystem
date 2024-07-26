//
// Created by Klemp on 16-Jul-24.
//

#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include <memory>         // for shared_ptr
#include <typeindex>      // for hash, type_index
#include <unordered_map>  // for unordered_map
class System;  // lines 12-12

class SystemManager {
public:
    template<typename T, typename... Args>
    std::shared_ptr<T> registerSystem(Args&&... args);

    void updateSystems() const;

private:
    std::unordered_map<std::type_index, std::shared_ptr<System>> m_systems;
};

#include "SystemManager.tpp"

#endif //SYSTEMMANAGER_H
