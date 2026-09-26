# PHASE 14 — Optimization, QA and Bug Fixing

## Objective
Stabilize the complete project.

## Required QA Checklist
Test:
- fresh launch,
- window resize,
- IN Gate to Stair 1 route,
- Stair 1 up/down 20 times,
- all major rooms,
- wall collision at walk/run speed,
- jump near walls/stairs,
- every seat,
- every game station,
- enter/exit each game repeatedly,
- 2048 controls,
- Tic-Tac-Toe rules,
- RPS rules,
- Rubik's Cube state consistency,
- Ludo turn progression,
- reset/restart behavior,
- Esc behavior,
- no input stuck after games,
- no OpenGL state leaking from game UI into campus render,
- no obvious memory/resource leaks.

## Optimize
- avoid unnecessary per-frame geometry rebuilding,
- reduce duplicate primitives,
- use display lists/VBOs only if compatible with chosen approach and useful,
- cull or skip distant detail where simple,
- keep update/render logic separate.

## Deliver
Create `QA_REPORT.md` containing:
- tested items,
- pass/fail,
- fixes,
- remaining limitations.

## Acceptance Gate
No known crash, blocker, soft-lock, major collision exploit or broken required game remains.


## Course Requirement Verification

Add explicit PASS/FAIL rows to `QA_REPORT.md` for:

- translation controlled by keyboard/mouse,
- rotation controlled by keyboard/mouse,
- scaling controlled by keyboard/mouse,
- model/object-coordinate transformation,
- camera/view-coordinate transformation,
- at least two complex objects,
- continuous rotating object,
- interior view of external environment,
- at least two active light sources,
- ambient material property,
- diffuse material property,
- specular material property,
- textures on multiple surfaces,
- all five algorithmic mini-games.
