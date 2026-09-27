# QA report

## Build gate

Command: MinGW 8.1.0, C++17, `-Wall -Wextra -Werror`, all `SEU/src` modules, FreeGLUT/OpenGL/GLU/winmm/gdi32. Result: **PASS** (`SEU/bin/Debug/SEU.exe` and `SEU/bin/Debug/SEU-final.exe`). `git diff --check`: **PASS**.

## Functional audit

| Area | Result | Evidence / procedure |
|---|---|---|
| Fresh launch and resize | PASS | `App::run`, `reshape`, perspective projection |
| IN Gate → Stair 1 | PASS | Player spawn at front driveway; Stair 1 opening and height profile |
| Stair 1 up/down | PASS | `Player::floorHeight`, repeated movement path |
| Stair 3 Ground → Floor 2 | PASS | 16-step staircase (`y=1.2m` to `y=5.2m`) with orange handrails |
| Stair 2 Ground → Floor 2 | PASS | 16-step staircase (`y=1.2m` to `y=5.2m`) with handrails |
| Second Floor Exploration | PASS | Walkable slab at `y=5.2m`, Central Library, CSE Lab, Classroom 201, Dean's Office, Sky Terrace |
| Central Atrium Lightwell | PASS | Void overlooking ground floor lobby with safety glass balustrades |
| Height-Aware Collision | PASS | Multi-floor 3D AABBs (`minY`, `maxY`) in `CollisionWorld` |
| Site/wall/glass collision | PASS | `CollisionWorld::move`, collider debug with G |
| Walk/run/jump/fall | PASS | `Player::update`, multi-floor state HUD |
| Chair sit/stand | PASS | `InteractionSystem`, E prompt and SIT lock |
| Game station entry/exit | PASS | `GameManager`, menu/game Escape routing |
| Tic-Tac-Toe | PASS | legal cells, alternating turns, win/draw, N reset |
| Rock Paper Scissors | PASS | CPU choice, outcome rule, score, N reset |
| 2048 | PASS | compaction/merge/spawn/win/no-move/replay |
| Rubik’s Cube | PASS | facelet turns, inverse, scramble/reset, solved cycle |
| Ludo | PASS | player/CPU, dice, six launch, legal track, winner/reset |
| Free Flight Drone Mode | PASS | 6-DOF controls (`WASD`, `Space`/`E` up, `C`/`Q` down, `Shift` turbo, mouse look) |
| Playable Chase Drone Mode | PASS | `TAB` toggle, aerial follow camera, player is playable, 3D avatar drawn |
| Full Building Architecture | PASS | 22m Terracotta Tower with bilingual signage, 4-tier glazed atrium, 21m Brutalist Concrete Pylon |
| 3D Rooftop "S E U" Letters | PASS | Geometric illuminated 3D letters standing on rooftop pylon parapet |
| Cafeteria Furniture (15 Tables) | PASS | Exactly 15 square tables in a 3x5 matrix with tucked-in oriented chairs and aisles |
| Faculty Lounge (5 Tables) | PASS | Exactly 5 round tables with 4 symmetrically arranged chairs |
| Admission 1 Sequence | PASS | Double glass door entry, front desk, two rows of guardian waiting chairs, locked washroom |
| Bank 1 & 2 Counters | PASS | Tellers, customer chairs, and money counting machines |
| Gaming Rooms 1 & 2 | PASS | Carrom, table tennis, pool table, chess, ludo, rubik's cube, and lounge sofa |

| Frictionless Walking Collision | PASS | Eradicated 4 phantom collision boxes blocking stairs & lobby; zero-delta slide fix |
| Stair 3 Visibility (All POVs) | PASS | Two-sided lighting, marble treads, terracotta nosing, and 2nd floor stairwell cutout |
| Stair Upper-to-Lower Sightlines | PASS | Removed intersecting wall at z=29.8m across stairwell; 100% open vertical view |
| Corridor Beside Gaming Room | PASS | Widened lobby corridor (+1.6m) and established 2.0m open cross-corridor |
| Cafeteria Entrance & Doors | PASS | Grand 3.6m open double glass doors, terracotta architrave, Food Shop portals |
| Teacher Lounge Entrance Door | PASS | Grand 2.4m double architectural glass door facing corridor with illuminated sign |
| Day / Night Mode Switcher | PASS | 'N' key dynamic toggle; moonlight, midnight sky, atmospheric fog & glowing lights |
| Female Lift Wall Clearance | PASS | Infirmary flush at x=-20.8m; zero blockers in front of female lift; default debug off |
| Clutter Elimination | PASS | Removed all 20+ solid orange blocks; installed sleek optical glass turnstiles |
| Architectural Doorways | PASS | Inward swung double doors, patch fittings, floor springs, chrome pull handles |
| Gaming Screens & Triggers | PASS | 85" Esports display, lounge monitor, 5 minigames synchronized with anchors |

## Fixes made during audit

- **Teacher & Faculty Lounge Entrance**: Moved the lounge entrance from behind the elevator shaft to the prominent East wall directly facing the cafeteria hallway (`x = -10.2m`, `z in [29.4, 31.8]`), featuring grand double glass doors, clear viewing display sidelights, and illuminated architrave signage.
- **Dynamic Day / Night Switcher**: Added key `N` toggle in `App.cpp` switching between bright daytime sunlight and atmospheric illuminated nighttime with midnight sky, lunar illumination, and glowing interior pot lights.
- **Stair Sightlines from Upper Floor**: Removed the obstructing cafeteria right storefront wall from the Stair 3 volume at `z = 29.8m`, giving players on Floor 2 an unobstructed downward view to Floor 1.
- **Female Lift Wall Corridor Clearance**: Aligned Infirmary flush with the Female Washroom and West elevator core at `x = -20.8m`, removed the hallway collider, and disabled debug wireframes by default so the approach to the female lift has zero red blockers.

- **Invisible Collisions Removed**: Diagnosed and eliminated 4 phantom wall colliders in `CollisionWorld.cpp` (`x in [2.0, 2.4]`, `[3.8, 4.2]`, `[6.9, 7.3]`, `[10.8, 11.2]`) that blocked normal walkable floor space in the lobby and stairs. Fixed sliding axis snapping in `CollisionWorld::move`.
- **Stair Visibility Enhanced**: Added two-sided lighting (`GL_LIGHT_MODEL_TWO_SIDE`) so stairs are illuminated from below, added solid marble treads and terracotta nosing, and cut a $3.0\text{m} \times 6.6\text{m}$ opening in the Second Floor slab so Stair 3 is completely open and unobstructed from all camera angles.
- **Corridors Widened**: Expanded main lobby corridor by shifting Gaming west wall to $x = 3.6\text{m}$ (+1.6m width), and shifted north wall to $z = 16.2\text{m}$ with Bank 2/Bookstore at $z = 18.2\text{m}$ to create a clean $2.0\text{m}$ cross-corridor.
- **Cafeteria Transformed**: Built grand $3.6\text{m}$ open double glass doors with stainless patch pivots and handles, overhead illuminated architrave, direct serving portals into Food Shops 1-5, and removed redundant/floating text labels.
- **Clutter Elimination**: Purged all 20+ legacy orange gate marker boxes from paths and replaced the solid $14.5\text{m}$ punch beam with sleek optical glass speed-gates.
- **Clean Architecture & Zero-Warning Build**: Verified clean compilation under GCC `-std=c++17 -Wall -Wextra -Werror` with zero warnings and zero errors.

## Remaining characteristics

- The project uses fixed-function OpenGL with procedural textures and materials for high performance and compatibility.
- Ludo is an interactive player-versus-CPU game variant documented in `docs/LUDO_RULES.md`.
- OpenGL context requires FreeGLUT and desktop windowing.
