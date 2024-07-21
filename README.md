# SparkSystem

A powerful and flexible Entity-Component-System (ECS) engine for game development.
Work-in-progress - First release coming soon!

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Build Instructions](#build-instructions)
- [Running Tests](#running-tests)
- [Contributing](#contributing)
- [License](#license)

## Introduction

Engine is a C++ based ECS engine designed to provide a robust and flexible framework for game development. It utilizes modern C++ features and best practices to ensure high performance and ease of use.

## Features

- Entity-Component-System architecture
- Supports multiple platforms: macOS (ARM and x86), Windows x86, and Linux x86
- Integration with Conan for dependency management
- Continuous Integration setup with GitHub Actions
- Modular and extensible design

## Installation

### Prerequisites

- C++20 compatible compiler
- CMake 3.28 or higher
- Conan package manager

### Setting Up the Project

1. **Clone the repository:**

    ```sh
    git clone https://github.com/yourusername/Engine.git
    cd Engine
    ```

2. **Install dependencies using Conan:**

    ```sh
    mkdir build
    cd build
    conan install .. --build=missing
    ```

3. **Configure the project with CMake:**

    ```sh
    cmake .. -G "Unix Makefiles"
    ```

4. **Build the project:**

    ```sh
    cmake --build .
    ```

## Usage

### Running the Engine

After building the project, you can run the engine executable:

```sh
./Engine
