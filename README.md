# PONG

A simple implementation of the classic Pong game using C++, SFML and CMake. Developed in Visual Studio Code.

## Table of Contents

- [About](#about)
- [Features](#features)
- [Getting Started](#getting-started)
  - [Preriquisites](#prerequisites)
  - [Building the Project](#building-the-project)
  - [Running the Game](#running-the-game)
- [Controls](#controls)
- [Contributing](#contributing)

## About

This project recreates the iconic pong game in 2D using SFML for graphics rendering. The objective is simple: keep the ball in play by bouncing it off your bat. Play solo against a computer opponent, or add multiplayer functionality in future versions.

## Features

- Classic Pong gameplay
- Player and AI-controlled bats
- Score display
- Simple and easy-to-understand codebase for beginners. With assets from [DevAssets's 2D Mega Pack](https://devassets.com/assets/2d-mega-pack/)

## Getting Started

### Prerequisites

- C++ compiler (GCC, Clang, or MSVC)
- SFML library
- CMake for build configuration
- Visual Studio Code (or any prefered IDE)

### Building the Project

1. Clone the repo:

```
git clone https://github.com/pharooque/pongV2.git
cd pongV2
```

2. Create a `build` directory:

```
mkdir build
cd build
```

3. Run CMake to configure project:

```
cmake ..
```

4. Build the project:

```
cmake --build .
```

### Running the Game

After building, you can run the the game executable located in the `build` directory:

```
./pong
```

## Controls

- Player Bat (Left)
  - Move up: `W`
  - Move down: `S`
- AI Bat (Right)
  - Controlled by computer

## Contributing

Contributions are welcome! Feel free to submit issues or pull requests.
