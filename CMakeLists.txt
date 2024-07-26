cmake_minimum_required(VERSION 3.28)
project(Engine)
message(STATUS "C++ Compiler ID: ${CMAKE_CXX_COMPILER_ID}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable strict compiler warnings
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    message("adding")
    add_compile_options(
            -Wall
            -Wextra
            -Wpedantic
            -Werror
            -Wconversion
            -Wsign-conversion
            -Wnon-virtual-dtor
            -Wold-style-cast
            -Wcast-align
            -Wunused
            -Woverloaded-virtual
            -Wnull-dereference
            -Wdouble-promotion
            -Wformat=2
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(
            /W4
            /WX
            /permissive-
            /sdl
            /Zc:__cplusplus
            /wd4127 # Ignore warning for constant conditional expressions
            /wd4324 # Ignore warning for structure was padded due to alignment specifier
    )
endif()

# Check if include-what-you-use is available
find_program(IWYU_PATH NAMES include-what-you-use iwyu)

if (IWYU_PATH)
    set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${IWYU_PATH})
    message(STATUS "Found include-what-you-use: ${IWYU_PATH}")
else()
    message(STATUS "include-what-you-use not found")
endif()

find_package(SFML 2.6.1 COMPONENTS system window graphics audio REQUIRED)
find_package(Catch2 3.6.0 REQUIRED)

# Main executable
add_executable(Engine main.cpp
        include/Component.h
        src/ComponentManager.cpp
        include/ComponentManager.h
        include/ComponentManager.tpp
        include/Entity.h
        src/Entity.cpp
        include/System.h
        include/components/Velocity.h
        src/EntityManager.cpp
        include/EntityManager.h
        src/SystemManager.cpp
        include/SystemManager.h
        include/SystemManager.tpp
        include/World.h
        src/World.cpp
        include/World.tpp
        src/Window.cpp
        include/Window.h
        include/components/Shape.h
        include/components/Node.h
        include/EventDispatcher.h
        include/NodeSystem.h
        src/NodeSystem.cpp
        src/EventDispatcher.cpp
        src/RenderingSystem.cpp
        include/RenderingSystem.h
        include/EntityFactory.h
        include/TransformManager.h
        src/TransformManager.cpp
        src/EntityFactory.cpp
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
        include/components/Velocity.h
        src/EntityManager.cpp
        include/EntityManager.h
        src/SystemManager.cpp
        include/SystemManager.h
        include/SystemManager.tpp
        include/World.h
        src/World.cpp
        include/World.tpp
        src/Window.cpp
        include/Window.h
        include/components/Shape.h
        include/components/Node.h
        include/EventDispatcher.h
        include/NodeSystem.h
        src/NodeSystem.cpp
        src/EventDispatcher.cpp
        src/RenderingSystem.cpp
        include/RenderingSystem.h
        include/EntityFactory.h
        include/TransformManager.h
        src/TransformManager.cpp
        src/EntityFactory.cpp
)

target_include_directories(EngineTests PRIVATE include)
target_link_libraries(EngineTests PRIVATE sfml::sfml Catch2::Catch2WithMain)

# Enable testing
enable_testing()

# Add test to CTest
add_test(NAME EngineTests COMMAND EngineTests)