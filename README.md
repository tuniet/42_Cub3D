*This project has been created as part of the 42 curriculum by antoniof & lsirpa-g.*

# cub3D

## Description

**cub3D** is a graphical project inspired by *Wolfenstein 3D*, one of the first First-Person Shooter games ever created.
The goal of this project is to build a simple 3D engine using **ray-casting** techniques, allowing the player to navigate inside a maze from a first-person perspective.

The project focuses on low-level graphics programming in C, real-time rendering concepts, event handling, and basic mathematics applied to computer graphics, using the **miniLibX** library.

## Instructions

### Requirements
- macOS or Linux
- `cc`
- `make`
- **miniLibX**
- `math` library (`-lm`)

### Compilation
From the root of the repository:

```bash
make
```

### Execution
Run the program with a valid `.cub` map file:

```bash
./cub3D maps/example.cub
```

### Controls
- `W`, `A`, `S`, `D` → Move the player and rotate the view
- `ESC` or window close button → Exit the program

## Map Format (.cub)

The scene file must contain:
- Texture paths for each wall direction (`NO`, `SO`, `WE`, `EA`)
- Floor (`F`) and ceiling (`C`) colors in RGB format
- A map composed of:
  - `1` → Wall
  - `0` → Empty space
  - `N`, `S`, `E`, `W` → Player start position and orientation

The map must be fully closed by walls. Any invalid configuration will result in an error and program exit.

## Bonus Features

The bonus part may include:
- Wall collisions
- Minimap
- Doors
- Animated sprites
- Mouse-controlled view rotation

Bonuses are evaluated only if the mandatory part is flawless.

## Resources

### Technical References
- Lode Vandevenne – Raycasting Tutorial
  https://lodev.org/cgtutor/raycasting.html
- miniLibX documentation and source code
- 42 Network cub3D subject PDF

### AI Usage

AI tools were used only as assistance, mainly for:
- Clarifying ray-casting mathematics
- Improving documentation clarity

All generated suggestions were reviewed, tested, and rewritten when necessary.

## License

This project is for educational purposes as part of the 42 curriculum.
