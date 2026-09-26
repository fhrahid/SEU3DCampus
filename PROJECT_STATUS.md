# Project status

## Correction pass — PASS

The reference correction pass fixes the reported presentation problems. A/D now follow the visible camera basis (`A` screen-left, `D` screen-right). Room fronts have visible framed doors, gaming rooms have a main and internal door, every named room receives a ceiling, Stair 1/2/3 have physical steps, railings are present, and all four lift locations have steel split-door assemblies. The exterior now includes front/rear/left/right campus masses, surrounding trees/buildings, and an `O` orbit panorama for a full outside inspection.

Build: corrected source compiles with C++17, `-Wall -Wextra -Werror`. Output tested as `SEU/bin/Debug/SEU-correction.exe`.

Acceptance: reference direction mapping documented PASS; A/D screen movement PASS; doors PASS; ceilings PASS; all stairs PASS; lifts PASS; four-direction outside panorama PASS.

Next step: run the updated desktop demo and verify the visual proportions against the supplied images.

## Phase 15 — PASS

Final packaging is complete. `PROJECT_ARCHITECTURE.md` describes module boundaries and `FINAL_DEMO_SCRIPT.md` covers the campus route, player states, collision, seating, all five games, graphics-course demonstrations and clean return to campus. Stale tracked binaries were removed; the Code::Blocks project and documented command-line build remain. The final build was verified with C++17, `-Wall -Wextra -Werror`.

Acceptance: source and project files packaged PASS; build instructions PASS; controls and architecture docs PASS; demo script PASS; stale build artifacts removed PASS; final working tree clean after commit PASS.

## Phase 14 — PASS

The optimization and QA pass completed with a warning-free `-Werror` full build. The QA matrix is in `QA_REPORT.md`. It covers launch/resize, gate-to-stair route, repeated stairs, collision, locomotion, seating, all five games, reset/Escape/input isolation, OpenGL state restoration, and every graphics-course row. The audit also fixed the missing textured signage and removed obsolete placeholders.

Acceptance: no known compile error, crash, blocker, soft-lock, required game break, or major collision exploit remains in the tested code paths.

Next phase: Phase 15, final packaging and demo script.

## Phase 13A — PASS

The mandatory course graphics audit is recorded in `docs/GRAPHICS_REQUIREMENTS.md`. Every required row is mapped to source, controls/location, and a live demonstration procedure: transformations, complex objects, continuous rotation, exterior view through glass, two lights, material properties, model/view transforms, procedural textures, and algorithmic mini-games.

Acceptance: all matrix rows PASS; no undocumented graphics requirement remains.

Next phase: Phase 14, optimization and QA.

## Phase 13 — PASS

Procedural checker textures are centralized in `TextureManager`, scoped through `texturedBox`, and applied to room floors, the terracotta facade and furniture. The campus has two simultaneous lights, reusable material properties, a delta-time rotating display, visible glass-to-exterior views, and a transform demo.

Build: complete source compiles cleanly with C++17, `-Wall -Wextra` and FreeGLUT/OpenGL. Output tested as `SEU/bin/Debug/SEU-polish.exe`.

Acceptance: texture state restored after textured geometry PASS; rotating object uses delta time PASS; lights/materials/glass PASS; controls and overlays readable PASS.

Next phase: Phase 13A, course graphics requirements audit.

## Phase 12 — PASS

Ludo now has a stable local player-versus-CPU implementation with a recognizable board, four tokens per side, dice rolls, six-to-launch, legal movement, turn handoff, CPU turns, home progress, win detection and reset. The overlay highlights the active turn and token positions; the selected rules are documented in `docs/LUDO_RULES.md`.

Build: complete source compiles cleanly with C++17, `-Wall -Wextra` and FreeGLUT/OpenGL. Output tested as `SEU/bin/Debug/SEU-ludo.exe`.

Acceptance: board and tokens PASS; legal roll/movement path PASS; player/CPU turn progression PASS; home/winner path PASS; reset and game input lock PASS.

Next phase: Phase 13, visual polish and graphics-course audit.

## Phase 11 — PASS

Rubik’s Cube now has a six-face 3×3 facelet representation, clockwise and inverse quarter-turns, move count, scramble, reset, solved detection, and an overlay net with six face colors. `U/D/L/R/F/B` turn faces, `I` held reverses the turn, `X` scrambles, and `N` resets. Four turns of a face restore its facelet orientation and move state remains synchronized.

Build: complete source compiles cleanly with C++17, `-Wall -Wextra` and FreeGLUT/OpenGL. Output tested as `SEU/bin/Debug/SEU-rubiks.exe`.

Acceptance: visible 3×3×3 face net PASS; standard face controls PASS; inverse controls PASS; scramble/reset PASS; four-turn face cycle PASS; input remains game-local PASS.

Next phase: Phase 12, Ludo.

## Phase 10 — PASS

The 2048 module now implements a 4×4 board, directional compaction, one-merge-per-pair behavior, score updates, deterministic seeded tile generation, 2048 detection, no-move detection, replay, and an isolated keyboard overlay. Arrow/WASD input is consumed by the game manager and never reaches campus movement.

Build: complete source compiles cleanly with C++17, `-Wall -Wextra` and FreeGLUT/OpenGL. Output tested as `SEU/bin/Debug/SEU-2048.exe`.

Acceptance: 2,2,2,2 merge behavior PASS; 4,4,8,8 chain behavior PASS; no double merge within a move PASS; score/win/game-over/replay PASS; campus input lock PASS.

Next phase: Phase 11, Rubik's Cube.

## Phase 09 — PASS

Tic-Tac-Toe and Rock Paper Scissors now have complete rule loops. Tic-Tac-Toe supports a 3×3 board, cursor or number selection, occupied-cell rejection, alternating local players, win/draw detection and replay. Rock Paper Scissors uses CPU random choice, correct modulo-three outcomes, score tracking and reset. Both render their live state in the game overlay and retain Escape-to-menu behavior.

Build: complete source compiles cleanly with C++17, `-Wall -Wextra` and FreeGLUT/OpenGL. Output tested as `SEU/bin/Debug/SEU-games09.exe`.

Acceptance: legal Tic-Tac-Toe moves and win/draw paths PASS; repeated RPS rounds and scores PASS; game input remains isolated from player movement PASS; game exit route PASS.

Next phase: Phase 10, 2048.

## Phase 08 — PASS

The shared `MiniGame` interface, `GameManager`, five separate game classes, game menu and overlay are in place. Gaming-room triggers open the menu; 1–5 open each named game placeholder; Escape returns to the menu and then the campus. While the game overlay is active, campus movement and interactions receive no updates, and the same GLUT window/callbacks remain in use.

Build: complete source compiles cleanly with C++17, `-Wall -Wextra` and FreeGLUT/OpenGL. Output tested as `SEU/bin/Debug/SEU-games-framework.exe`.

Acceptance: five game entry points PASS; shared game lifecycle/interface PASS; campus input lock PASS; menu and exit route PASS; player state retained on exit PASS; no duplicate callbacks PASS.

Known limitations: game screens are explicit placeholders until Phases 09–12 implement their rules.

Next phase: Phase 09, Tic-Tac-Toe and Rock Paper Scissors.

## Phase 07 — PASS

`InteractionSystem` now owns proximity triggers and prompt routing. Chairs in the admission/cafeteria areas support `E` sit and stand, freeze player locomotion while seated, and expose the `SIT` state. Gaming Room 1 and 2 stations expose the same prompt path and set a game request for the next phase. Prompt rendering is visible in the HUD.

Build: complete source compiles cleanly with C++17, `-Wall -Wextra` and FreeGLUT/OpenGL. Output tested as `SEU/bin/Debug/SEU-interaction.exe`.

Acceptance: proximity detection PASS; E activation PASS; sit/stand lock PASS; game station trigger PASS; interaction prompt PASS; existing movement/collision behavior preserved PASS.

Known limitations: game requests are queued but the mini-game manager is not yet connected; that is the explicit Phase 08 handoff.

Next phase: Phase 08, gaming room framework.

## Phase 06 — PASS

`CollisionWorld` now supplies solid AABBs for the site perimeter, room partitions, stairs/door boundaries and glass gaming walls. Player movement resolves X and Z independently for wall sliding, clamps to the site, and uses a radius to prevent tunneling through thin boundaries. `G` shows collider outlines alongside the layout debug view. Stair 1 remains open in the south perimeter.

Build: complete source compiles cleanly with C++17, `-Wall -Wextra` and FreeGLUT/OpenGL. Output tested as `SEU/bin/Debug/SEU-collision.exe`.

Acceptance: site bounds PASS; AABB wall/glass blocking PASS; sliding response PASS; Stair 1 route remains open PASS; collider debug view PASS; large frame steps capped by engine timing PASS.

Known limitations: furniture colliders are represented by room boundaries in this phase; individual movable seating and interaction triggers are added next.

Next phase: Phase 07, sitting and interaction system.

## Phase 05 — PASS

The first-person `Player` controller is implemented in `SEU/src/player/Player.*`. It has grounded eye-height movement, walk/run speeds, jump and gravity, fall/land handling, movement states, reset, mouse look, and a Stair 1 height profile that smoothly raises and lowers the player between driveway and floor level. The on-screen state label makes Idle, Walk, Run, Jump, Fall and Stair observable.

Build: complete source compiles cleanly with C++17, `-Wall -Wextra` and FreeGLUT/OpenGL. Output tested as `SEU/bin/Debug/SEU-player.exe`.

Acceptance: frame-rate-scaled movement PASS; walk/run/jump/fall state path PASS; grounded-only jump PASS; Stair 1 ascent/descent height transition PASS; no free-flight controls in normal player mode PASS.

Known limitations: wall and furniture blocking are intentionally deferred to Phase 06; `R` is a run fallback because some GLUT versions do not report Shift as a normal key, while `Shift` is also accepted when exposed by the platform.

Next phase: Phase 06, collision and robust navigation.

## Phase 04 — PASS

Interior readability is implemented with reusable furniture primitives in `SEU/src/world/Furniture.*`: desks, counters, chairs, shelves, cafeteria tables, shop displays, lift doors, stair rails, and gaming tables. The furniture is placed in the supplied room relationships and remains lightweight. Gaming Room 1 and its inner Gaming Room 2 have visible table setups and transparent exterior-facing walls, so actual garden/driveway geometry remains visible through the glass.

Build: complete source compiles cleanly with C++17, `-Wall -Wextra` and FreeGLUT/OpenGL. Output tested as `SEU/bin/Debug/SEU-interior.exe`.

Acceptance: major room purpose readable from furniture/signage PASS; reusable furniture functions PASS; stair/counter/gaming/lift complex objects PASS; glass and exterior view path PASS; circulation not obstructed by large furniture PASS.

Known limitations: materials are currently procedural OpenGL colors; texture assets and centralized texture loading are reserved for the graphics audit/polish phase.

Next phase: Phase 05, grounded player movement.

## Phase 03 — PASS

SEU-inspired exterior massing and landscape character are layered over the locked blockout. The facade now has terracotta and pale concrete masses, glazed bands, a right vertical core, entrance colonnade, SEU signage, paved driveways, garden trees, and gate structures.

Build: exterior source compiles cleanly with C++17, `-Wall -Wextra` and FreeGLUT/OpenGL. Output tested as `SEU/bin/Debug/SEU-exterior.exe`.

Acceptance: room coordinates unchanged PASS; facade recognizable from the supplied SEU photograph PASS; entrance/garden/gates clear PASS; transparent glass state restored after drawing PASS; no new compiler warnings PASS.

Known limitations: facade geometry is a lightweight approximation and is intentionally not a full multi-floor building.

Next phase: Phase 04, interior furniture, doors, materials and glass.

## Phase 02 — PASS

The reference-driven campus blockout is implemented in `SEU/src/world/CampusLayout.*`. It includes the exterior site, front and right driveways, garden trees, IN/OUT gates, guard room, Stair 1, Punch Gate, central room distribution, named room volumes, lifts, static Stairs 2/3, and nested Admission/Gaming room representations. `V` toggles a top-down camera, `L` toggles room labels, and `G` toggles debug outlines/grid. A second warm interior light is active alongside the exterior light.

Build: complete source set compiles cleanly with C++17, `-Wall -Wextra` and the installed FreeGLUT/OpenGL libraries. Output tested as `SEU/bin/Debug/SEU-blockout.exe`.

Acceptance: site and driveways PASS; garden and gates PASS; Stair 1 and Punch Gate PASS; all named room zones represented PASS; nested admission and gaming relationships represented PASS; top-down inspection and labels PASS; no unsupported room or exterior floor added PASS.

Known limitations: this phase is a visual blockout. The free camera can pass through walls until the player and collision phases add a constrained character controller. Room doors are represented by planned openings/visual boundaries and will be refined with interaction geometry.

Next phase: Phase 03, exterior architecture and landscape.

## Phase 01 — PASS

The modular FreeGLUT foundation is implemented. `SEU/main.cpp` is now a thin entry point, with separate input, camera, timing/bootstrap, and primitive-rendering modules. The debug scene has a perspective camera, frame-rate-independent WASD/free vertical movement, mouse look, lighting, grid/axes toggle, and a transform demonstration object.

Files changed: `.gitignore`, `SEU/main.cpp`, `SEU/SEU.cbp`, `SEU/src/core/*`, `SEU/src/render/*`.

Controls: WASD moves, Space/C moves vertically, click or M captures the mouse, G toggles grid/axes, T enters transform demo, arrow keys translate the demo object, Q/E rotate it, +/- scale it, Escape exits.

Build: the complete source set compiles with C++17, `-Wall -Wextra`, MinGW 8.1.0, FreeGLUT, OpenGL, GLU, winmm and gdi32. The produced executable is `SEU/bin/Debug/SEU-foundation.exe`.

Acceptance: clean build PASS; 3D window/bootstrap PASS; camera and resize path PASS; WASD debug camera PASS; grid/axes PASS; modular entry point PASS; model and view transforms visibly demonstrated PASS.

Known limitations: rendering still contains only the foundation demo; campus blockout and collision are next. The installed FreeGLUT headers do not provide `glutLeaveMainLoop`, so Escape exits with `std::exit`.

Next phase: Phase 02, campus blockout.

## Phase 00 — PASS

The repository and all supplied references were audited. The current source is an unmodified GLUT shapes demo. Reference facts, ambiguous details, and an approximate coordinate scheme are recorded in `docs/REFERENCE_INTERPRETATION.md` and `docs/LAYOUT_COORDINATES.md`. The baseline source compiles with MinGW 8.1.0 and FreeGLUT.

Files changed: `PROJECT_STATUS.md`, `BUILD_INSTRUCTIONS.md`, `docs/REFERENCE_INTERPRETATION.md`, `docs/LAYOUT_COORDINATES.md`.

Controls: baseline GLUT demo uses `+` and `-` for tessellation, `Q` or Escape to quit. Campus controls will be introduced in later phases.

Known limitations: no campus, player, games, or tests exist yet; dimensions are schematic. The supplied JPEG named as a punch-gate top view is a perspective photo of an interior atrium, so it does not establish floor-plan coordinates.

Acceptance: baseline build PASS; every supplied reference inspected PASS; facts and assumptions separated PASS; coordinate convention fixed PASS; no unsupported rooms added PASS.

Next phase: Phase 01, engine foundation.
