# Minecraft Maze Runner

**Original repository:** [COSC2804 SEP 2023 Assignment 3 — Team 58](https://github.com/rmit-computing-technologies/cosc2804-sep-23-assignment-3-team-58-cosc2804-sep23)  
**Team:** BitBusters

## Resume summary

Collaborated on a C++ Minecraft maze-generation and solving application integrated with a Spigot 1.19.4 server. The program supports terminal-defined and procedurally generated mazes, Minecraft construction, manual navigation, escape-route visualisation, terrain handling and world restoration.

## Engineering highlights

- Recursive-backtracking maze generation with randomized traversal and entrance creation
- Minecraft world integration through `mcpp::MinecraftConnection`
- Menu-driven state machine for generation, construction, solving, team information and cleanup
- Manual player placement and navigation
- Right-hand wall following for route visualisation
- Enhancement 2 shortest-route mode using breadth-first search and path reconstruction
- Automated input/output fixtures covering menu validation, maze generation, solving and route display

## My documented contribution

The source project README maps `LabibaShaikh` to student `s3954789` and records:

- Collaboration on maze initialization and recursive-backtracking logic
- An individual `Labiba_menu` branch implementation for menu navigation
- Development of the Enhancement 2 shortest-escape-route implementation
- Integration of the route implementation into `main`
- Debugging route-visualisation issues where the route did not appear correctly in Minecraft
- Contributions to the shared test cases

The final program was collaborative. The source README identifies teammates and distinguishes code merged from each branch; this summary does not claim sole ownership of the complete application.

## Repository structure

| Area | Purpose |
|---|---|
| `mazeGenerator.cpp`, `genMaze.h` | Random maze generation |
| `genMaze_E1.h` | Terrain-aware Enhancement 1 generation |
| `buildMaze.cpp`, `Maze.cpp` | Minecraft construction and restoration |
| `Agent.cpp` | Player orientation, wall following and shortest-route behavior |
| `solveManually.cpp` | Player placement for manual solving |
| `mazeRunner.cpp` | Command-line modes and application state machine |
| `Tests/` | Input/output regression fixtures |

## Build and run

The original Makefile uses C++17, `-Wall`, `-Werror` and the external `mcpp` library:

```bash
make
./mazeRunner
./mazeRunner -testMode
./mazeRunner -E1
./mazeRunner -E2
```

The application requires a running Minecraft Spigot 1.19.4 server and the `mcpp` headers/library. A build was attempted against the portfolio environment but could not start because `mcpp/mcpp.h` is not installed here.

## Testing

The `Tests/` directory contains regression fixtures for invalid input, random maze dimensions, terminal maze loading, menu options, manual solving, route display and solve-before-build behavior. The source README records that all team members contributed test cases. The full test harness was not executed in this environment because the external Minecraft dependency is unavailable.

## Snapshot provenance

`SOURCE_README.md` is the original project README from the uploaded archive. The archive did not include Git history, so this monorepo preserves the source snapshot and attribution but not the original commit graph. The original repository remains the source of truth for branches and history.
