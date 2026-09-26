# PHASE 08 — Gaming Room Interaction + Mini-Game Framework

## Objective
Create a robust way to enter and leave games without breaking the campus.

## Implement
- gaming room stations/tables for each game,
- interaction prompts,
- shared `MiniGame` interface or equivalent,
- `GameManager`,
- game states: inactive, entering, playing, paused, exiting,
- campus input lock while playing,
- mini-game camera/UI mode,
- clean return to player position after exit.

## Games Required
Create separate modules/placeholders for:
- Ludo
- Rubik's Cube
- 2048
- Tic-Tac-Toe
- Rock Paper Scissors

At this phase, each station may initially open a working placeholder screen that proves state switching and exit behavior.

## Acceptance Gate
Player can enter each game station and exit back to the campus with camera/player state restored and no duplicated callbacks or frozen input.
