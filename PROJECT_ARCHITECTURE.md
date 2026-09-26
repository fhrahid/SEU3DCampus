# Project architecture

- `SEU/src/core`: GLUT bootstrap, callbacks, input edge/held state, configuration, and app-state routing.
- `SEU/src/render`: camera/view transform, fixed-function materials, reusable primitives, procedural texture manager and scoped UI/texture state.
- `SEU/src/world`: reference-locked campus layout, exterior facade, furniture and signage.
- `SEU/src/player`: grounded eye-height player movement, locomotion states, stairs and jump/gravity.
- `SEU/src/physics`: AABB solids, wall sliding, site bounds and collider debug drawing.
- `SEU/src/interaction`: proximity triggers, prompts, seating and game-station requests.
- `SEU/src/games`: shared mini-game lifecycle plus independent Tic-Tac-Toe, RPS, 2048, Rubik’s Cube and Ludo rules/rendering.

The update path is input → game manager or player/interaction → render. Campus geometry remains present while the game overlay owns input. Layout assumptions and room coordinates are documented in `docs/REFERENCE_INTERPRETATION.md` and `docs/LAYOUT_COORDINATES.md`.
