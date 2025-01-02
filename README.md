# Cub3D

---

## Collaboration

👉🏻 This project was created together with [MariaErosh](https://github.com/MariaErosh/Cub3D) 

---

**Cub3D** is a 3D graphical representation of a maze, viewed from a first-person perspective, created using ray-casting principles. This project demonstrates the fundamentals of a simple game engine with realistic graphics and smooth controls, powered by the MiniLibX library. It's an introduction to computer graphics, game development, and ray casting mathematics.


<div style="display: flex; flex-wrap: wrap; gap: 10px;">
  <img src="https://github.com/owrmille/cub_3d/blob/main/demo/7.png" alt="Image 7" width="500">
  <img src="https://github.com/owrmille/cub_3d/blob/main/demo/6.png" alt="Image 6" width="500">
</div>

See **.gif** demonstration **in the end**.

---

## Overview

- **Realistic 3D Rendering**  
  View a maze from a first-person perspective.
  
- **Smooth Controls**  
  - Look around using the left and right arrow keys (or a mouse).  
  - Move through the maze with `W`, `A`, `S`, `D`.  
  - Quit the program using the `ESC` key or the window's close button.

- **Wall Textures**  
  Walls have unique textures depending on their orientation: North, South, East, or West.

- **Customizable Environments**  
  Design your own mazes with `.cub` files:
  - Define wall textures.
  - Set floor and ceiling colors.
  - Create a map.

- **Error Handling**  
  The program ensures `.cub` files follow strict rules and provides meaningful error messages for misconfigurations.

---

## Getting Started

### Build the Project

1. Clone the repository:
   ```bash
   git clone --recursive https://github.com/owrmille/cub_3d.git
   ```
2. Compile the program using `make`:
   ```bash
   make
   ```

### Run the Program

Run the program with a `.cub` map file as an argument:
```bash
./cub3d path_to_map.cub
```
e.g.: `./cub3d valid_maps/1.cub`

---

## Creating Custom Maps

You can design your own maze maps for Cub3D. Follow these guidelines:

### File Format

- Save the map as a `.cub` file.

### Components

1. **Wall Textures**  
   Define textures for the four wall orientations using these identifiers (choose default ones from folder 'textures' or upload new ones):
   ```plaintext
   NO ./path_to_north_texture
   SO ./path_to_south_texture
   WE ./path_to_west_texture
   EA ./path_to_east_texture
   ```

2. **Colors**  
   Specify the floor (`F`) and ceiling (`C`) colors using RGB values in the range `[0, 255]`:
   ```plaintext
   F 220,100,0
   C 225,30,0
   ```

3. **Map Layout**  
   - Use the following characters:  
     - `1`: Wall  
     - `0`: Empty space  
     - `N`, `S`, `E`, `W`: Player's starting position and orientation.
   - The map **must be fully enclosed** by walls (`1`) and **must include only one player position**.
   - Example:
     ```plaintext
     111111
     100101
     101001
     1100N1
     111111
     ```

---

### File Structure

The `.cub` file should have the following structure:

1. Start with the texture and color definitions.
2. Add the map as the final component.
3. Separate elements with one or more empty lines.
4. Maintain the order of information within each element.

---

### Example Map File

```plaintext
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm
F 220,100,0
C 225,30,0

111111
100001
1000N1
111111
```

---

## Error Handling

- If the `.cub` file violates any of the above rules, the program will:
  - Exit cleanly.
  - Display `Error\n` followed by a detailed error message.

---

## Examples
<div style="display: flex; flex-wrap: wrap; gap: 10px;">
  <img src="https://github.com/owrmille/cub_3d/blob/main/demo/7.png" alt="Image 7" width="500">
  <img src="https://github.com/owrmille/cub_3d/blob/main/demo/6.png" alt="Image 6" width="500">
  <img src="https://github.com/owrmille/cub_3d/blob/main/demo/3.png" alt="Image 3" width="500">
  <img src="https://github.com/owrmille/cub_3d/blob/main/demo/8.png" alt="Image 8" width="500"> 
  <img src="https://github.com/owrmille/cub_3d/blob/main/demo/10.png" alt="Image 10" width="500">
  <img src="https://github.com/owrmille/cub_3d/blob/main/demo/5.png" alt="Image 5" width="500">

</div>

---

## Gif example

My computer is pretty slow, sorry for the .gif quality 🚀 🫨  

<p align="center">
<img src="https://github.com/owrmille/cub_3d/blob/main/demo/example.gif" alt="gif demo">
</p> 
