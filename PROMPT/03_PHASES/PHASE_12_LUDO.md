# PHASE 12 — Ludo

## Objective
Implement a simplified but genuinely playable Ludo mini-game appropriate for a GLUT course project.

## Scope
Prefer a stable local implementation over an overcomplicated networked game.

Implement:
- recognizable Ludo board,
- 2 to 4 players or player + simple CPU players,
- dice roll,
- four tokens per side if practical,
- token enters track according to standard start condition,
- legal movement,
- capture on non-safe positions,
- safe/home behavior,
- exact or clearly documented home-entry rule,
- turn progression,
- win detection,
- reset/new game.

If full tournament-grade rule variants are too broad, document the chosen standard rule set in `docs/LUDO_RULES.md`.

## User Experience
Highlight legal movable tokens after a dice roll.

## Acceptance Gate
A full game can progress from start to a declared winner without illegal turn transitions or token positions.
