# 42-CUB3D - A Raycasting Engine

## About the Project
cub3D is a 42 School project that introduces us to the world of raycasting. Inspired by the classic Wolfenstein 3D, the goal is to create a dynamic 3D graphical representation of a maze using a 2D map. This project is a deep dive into mathematics (vectors, trigonometry), algorithmic logic (Digital Differential Analysis - DDA), and window/graphics management using the MiniLibX library. As developers who prefer understanding the core mechanics over using pre-built engines or copying pre-made solutions, we are building this entirely from scratch in C to fully grasp how a basic 3D engine functions under the hood.

## Development Plan & Methodology
Since this is a two-person project, we have structured our development pipeline to maximize parallel work. The architecture is inherently split into two distinct domains: the **Parser (Data Processing)** and the **Raycaster (3D Graphics Engine)**.

*   **Phase 1** focuses on scaffolding and creating a temporary hardcoded map to decouple our dependencies immediately.
*   **Phase 2** allows us to work completely independently: one handles the strict `.cub` file parsing and memory management, while the other builds the DDA algorithm and rendering logic.
*   **Phase 3** is the integration phase, where the dynamic parser feeds into the rendering engine, followed by texturing, movement, and collision detection.

---

## 📋 Task List (Work Breakdown Structure)

### Phase 1: Foundation & Decoupling (Joint Effort)
*   **Task 1: Project Skeleton & Makefile**
    *   *Description:* Setup directory structure (src, inc, textures), include libft/minilibx, and write compilation rules.
*   **Task 2: MLX Testing with Hardcoded Map**
    *   *Description:* Embed a dummy map (e.g., `int map[10][10]`) into the code.
    *   *Importance:* This crucial step allows the Raycaster development to start immediately without waiting for the Parser to be finished.

### Phase 2: Independent Development
#### Developer A: Parsing & Validation
*   **Task 3: `.cub` File Reading & Extraction**
    *   *Description:* Parse the file line-by-line to extract NO, SO, WE, EA texture paths and Floor/Ceiling (F/C) RGB colors.
*   **Task 4: Map Matrix Generation**
    *   *Description:* Extract the actual map layout (0, 1, N, S, etc.) into a 2D array or suitable data structure.
*   **Task 5: Map Validity Check**
    *   *Description:* Ensure the map is completely closed/surrounded by walls (1). Check for invalid characters, multiple spawn points, and empty spaces using a Flood-fill algorithm.

#### Developer B: Raycasting & MLX Graphics
*   **Task 6: DDA (Digital Differential Analysis) Implementation**
    *   *Description:* Write the vector mathematics to shoot rays from the player's perspective until they hit a wall.
*   **Task 7: 3D Projection & Wall Strip Rendering**
    *   *Description:* Calculate the distance to the wall (applying Cosine correction to fix the Fisheye effect) and determine the height of the vertical line to draw on the screen.
*   **Task 8: Image Buffer Optimization**
    *   *Description:* Avoid `mlx_pixel_put`. Create a single MLX image per frame and write pixels directly to its memory buffer array to prevent severe FPS drops.

### Phase 3: Integration & Polish (Joint Effort)
*   **Task 9: Parser & Raycaster Integration**
    *   *Description:* Replace the hardcoded map with the dynamic map parsed from the `.cub` file.
*   **Task 10: Wall Texturing**
    *   *Description:* Read XPM/PNG files using MLX and map the exact pixel column of the texture to the screen based on the ray's wall hit coordinate (X-axis).
*   **Task 11: Movement, Collision, & Event Hooks**
    *   *Description:* Implement WASD movement and camera rotation. Check the map matrix before moving to prevent walking through walls.
