*This project has been created as part of the 42 curriculum by ycakmakci, alozpola.*

# Description

**cub3D** is a graphical project from the 42 curriculum inspired by the classic game **Wolfenstein 3D**. The main goal of the project is to create a simple 3D game engine using the **raycasting** technique and the **MiniLibX** graphical library.

The program reads a `.cub` configuration file containing the textures, floor and ceiling colors, and the game map. The map is parsed and validated before the game starts. During execution, the player can move around the map and look at the environment from a first-person perspective.

The project provides an introduction to several important programming concepts, including:

* Raycasting and basic 3D rendering
* 2D coordinate systems and player movement
* Texture mapping
* Keyboard and window event handling
* File parsing and input validation
* Dynamic memory management
* Error handling and resource cleanup
* Working with the MiniLibX graphical library

# Instructions

## Compilation

The project can be compiled using the provided `Makefile`:

```bash
make
```

This creates the `cub3D` executable.

To remove object files:

```bash
make clean
```

To remove object files and the executable:

```bash
make fclean
```

To completely recompile the project:

```bash
make re
```

## Execution

Run the program by providing a valid `.cub` configuration file:

```bash
./cub3D maps/map.cub
```

The configuration file contains the paths to the wall textures, the floor and ceiling colors, and the map layout.

Example:

```text
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 50,50,50
C 135,206,235

111111
100001
10N001
100001
111111
```

The map must contain valid characters and be completely surrounded by walls. It must also contain exactly one player starting position.

During the game, the player can move around the map using the keyboard and close the window using the appropriate exit controls.

# Controls

| Key     | Action        |
| ------- | ------------- |
| `W`   | Move forward  |
| `S`   | Move backward |
| `A`   | Move left     |
| `D`   | Move right    |
| `←`  | Rotate left   |
| `→`  | Rotate right  |
| `ESC` | Exit the game |

# Technical Overview

The rendering system uses **raycasting** to determine which parts of the map are visible from the player's position.

For every vertical column of the window, a ray is projected from the player's position into the map. The distance to the first wall hit by the ray is calculated and used to determine the height of the corresponding wall column on the screen. Textures are then applied according to the wall that was hit.

The map parser is responsible for reading the `.cub` file, validating its contents, loading the required textures, converting the map into an internal representation, and checking that the map is properly enclosed by walls.

Memory allocation and error handling are also important parts of the project. Resources such as textures, images, maps, and other dynamically allocated data must be properly released when the program exits or encounters an error.

# Resources

The following resources were used to understand the concepts and technologies involved in the project:

* [42 cub3D Subject](https://cdn.intra.42.fr/pdf/pdf/960/cub3d.en.pdf)
  Official project subject and requirements.
* [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)
  Documentation and examples for the MiniLibX library.
* `man` pages and standard C documentation were also consulted for system calls, memory management, file handling, and other C functions used throughout the project.

## AI Usage

AI tools were used as a **learning and development aid** during the project.

AI assistance was mainly used for:

* Understanding raycasting concepts and related mathematics
* Discussing possible approaches to map parsing and validation
* Debugging compiler, linker, and runtime errors
* Reviewing code structure and identifying potential problems
* Discussing memory management and error-handling strategies
* Improving the readability and naming of functions and variables

AI-generated suggestions were used as guidance rather than as a replacement for understanding the implementation. The project's final code, architecture, integration, testing, and implementation decisions were made by the project author.
