# Project status

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
