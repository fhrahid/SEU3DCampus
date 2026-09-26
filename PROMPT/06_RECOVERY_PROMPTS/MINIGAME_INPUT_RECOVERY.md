# Mini-Game Input Recovery Prompt

Stop unrelated work.

Verify input ownership between:
- CAMPUS state,
- MINIGAME state,
- PAUSED state.

When a mini-game is active:
- campus movement must not update,
- game input must route only to the active game,
- Esc must exit safely,
- player/camera state must restore correctly.

Fix the smallest responsible routing/state bug.
Retest all already-completed games.
Stop.
