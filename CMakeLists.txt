cmake_minimum_required(VERSION 3.28)
project(Engine)

set(CMAKE_CXX_STANDARD 20)

add_executable(Engine main.cpp
        include/Component.h
        src/Component.cpp
        src/ComponentManager.cpp
        include/ComponentManager.h
        include/ComponentManager.tpp
        include/Entity.h
        src/Entity.cpp
        include/System.h
        src/MovementSystem.cpp
        include/MovementSystem.h
        include/components/Velocity.h
        include/components/Position.h
        src/EntityManager.cpp
        include/EntityManager.h
        include/Component.tpp
        include/EntityManager.tpp
        src/SystemManager.cpp
        include/SystemManager.h
        include/SystemManager.tpp)
target_include_directories(Engine PRIVATE include)