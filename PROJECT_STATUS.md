# Project status

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
