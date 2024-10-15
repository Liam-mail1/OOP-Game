# 2D PvP Tank Game

## Description
This project is a 2D Player vs. Player (PvP) tank game developed using Raylib. Players control tanks using the same keyboard, aiming to eliminate each other while navigating through different maps filled with traps and obstacles. The game features a scoring system, various projectile types, and selectable maps to enhance gameplay.

## Table of Contents
1. [Installation](#installation)
2. [Usage](#usage)
3. [User Menu](#user-menu)
4. [Classes](#classes)
5. [Inheritance Hierarchy](#inheritance-hierarchy)
6. [Overall Program Interactivity](#overall-program-interactivity)
7. [Contributing](#contributing)
8. [License](#license)

## Installation
To run this game, you need to have Raylib installed on your machine. Follow these steps to set up the project:

1. Clone the repository:
    ```bash
    git clone <repository_url>
    cd <project_directory>
    ```

2. Compile the project using the provided Makefile:
    ```bash
    make
    ```

3. Run the game:
    ```bash
    ./<executable_name>
    ```

## Usage
Upon launching the game, you will see the user menu with various options. Select an option by entering the corresponding number:

1. **Start Game**: Begin a new game session.
2. **Load Game**: Load a previously saved game.
3. **Settings**: Adjust game settings, such as controls and difficulty.
4. **Help**: View instructions and gameplay tips.
5. **Exit**: Close the program.

## User Menu
The user menu provides multiple options, making it easy to navigate through the game. Here’s a breakdown of the available options:

- At the start of the program, users can choose to start or load a game.
- Access to the settings and help menus is available from the main menu and during gameplay.
- The game provides hints for controls and gameplay mechanics when starting or during play.

## Classes
This project includes the following meaningful classes:

1. **Entity**: Abstract class for all game entities, containing properties for position and direction.
2. **Player**: Inherits from `Entity`, representing a player-controlled tank with health and damage functionality.
3. **Nodes**: Represents fixed map locations for trap spawns, ensuring traps can randomly appear during gameplay.
4. **TrapBase**: Abstract class for traps, providing common functionalities like spawning and dealing damage.
5. **TrapVariant**: Inherits from `TrapBase`, implementing specific attack patterns for different traps.
6. **Projectile**: Inherits from `Entity`, representing projectiles fired by players, with unique properties for each type.
7. **Map**: Contains information about different maps, including layout and trap placements.
8. **Asset**: Handles UI animations and asset management for the game.

## Inheritance Hierarchy
This project implements a three-level inheritance hierarchy as follows:

- **Base Class**: `Entity`  
  Description: The abstract base class for all game entities, providing basic properties and methods.

- **Intermediate Class**: `Player`  
  Inherits from `Entity` and represents player-controlled tanks, including health management and movement.

- **Derived Class**: `TrapVariant`  
  Inherits from `TrapBase`, implementing different types of traps that deal damage to players upon contact.

## Overall Program Interactivity
- The game features user-friendly hints and instructions throughout to assist players in navigating the menus and understanding gameplay mechanics.
- Error handling messages provide clear guidance on actions, allowing players to recover from mistakes easily.
