cmake_minimum_required(VERSION 3.28)
project(Engine)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML)
find_package(Catch2)

# Main executable
add_executable(Engine main.cpp
        include/Component.h
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
        include/EntityManager.tpp
        src/SystemManager.cpp
        include/SystemManager.h
        include/SystemManager.tpp
        include/Coordinator.h
        src/Coordinator.cpp
        include/Coordinator.tpp
)

target_include_directories(Engine PRIVATE include)

target_link_libraries(Engine sfml::sfml)

# Add test executable
add_executable(EngineTests
        test/test_main.cpp
        test/ecs_tests.cpp
        include/Component.h
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
        include/EntityManager.tpp
        src/SystemManager.cpp
        include/SystemManager.h
        include/SystemManager.tpp
        include/Coordinator.h
        src/Coordinator.cpp
        include/Coordinator.tpp
)

target_include_directories(EngineTests PRIVATE include)
target_link_libraries(EngineTests PRIVATE sfml::sfml Catch2::Catch2WithMain)

# Enable testing
enable_testing()

# Add test to CTest
add_test(NAME EngineTests COMMAND EngineTests)