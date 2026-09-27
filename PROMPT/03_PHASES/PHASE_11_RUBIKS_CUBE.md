# PHASE 11 — Interactive Rubik's Cube

## Objective
Implement a playable 3x3 Rubik's Cube interaction.

## Representation
Use 27 cubies or an equivalent robust facelet representation.

## Required Features
- visible 3x3x3 cube,
- six colored faces,
- select/rotate standard faces,
- logical state updates matching visual rotations,
- scramble function,
- reset solved state,
- move counter,
- optional undo if straightforward.

## Controls
Use clear keyboard mappings and show them on-screen, for example:
- U/D/L/R/F/B for clockwise face turns,
- Shift + key or another documented modifier for inverse turns,
- Esc to exit.

Do not confuse player movement controls with cube controls while the game is active.

## Animation
Face turns should animate briefly if feasible. Logic must update only once per move and remain synchronized with the visual cube.

## Acceptance Gate
Four quarter-turns of the same face return to the original state. Scramble and reset work. Repeated moves do not deform or separate cubies.
