# PHASE 01 — Engine Foundation

## Objective
Create a modular, stable GLUT/OpenGL project foundation.

## Implement
- application/bootstrap module,
- GLUT callbacks,
- delta time,
- keyboard state,
- mouse look input,
- camera,
- renderer utilities,
- reusable primitives: cube/box, plane, cylinder, stairs, glass panel,
- basic material helper,
- basic directional + ambient lighting,
- debug axes/grid toggle,
- resize/projection handling,
- clean exit.

Do not build the detailed campus yet.

## Required Behavior
- stable 60+ FPS on a normal desktop for the empty/debug scene,
- movement/input state updates are frame-rate independent,
- mouse recentering/locking does not produce uncontrolled spinning,
- window resizing preserves perspective.

## Acceptance Gate
- compiles cleanly,
- opens a 3D window,
- camera works,
- WASD debug free-camera works,
- debug grid/axes visible,
- no giant `main.cpp`.


## Mandatory Transformation Foundation

Add reusable transformation helpers and clearly separate:

- model/object transformation:
  - `glTranslate*`
  - `glRotate*`
  - `glScale*`
  - or equivalent matrix helpers.
- viewing transformation:
  - camera position/orientation,
  - `gluLookAt` or equivalent view-matrix logic.

Create a debug transformation demonstration object that can be translated, rotated and scaled by keyboard/mouse while in a dedicated transformation-demo mode.

### Additional Acceptance Checks
- object translation visibly works,
- object rotation visibly works,
- object scaling visibly works,
- camera/view transformation works independently,
- leaving transformation-demo mode restores normal controls.
