# PHASE 07 — Sitting + General Interaction Framework

## Objective
Allow the player to interact with the campus naturally.

## Implement
A reusable interaction system with:
- interaction radius,
- facing/distance check,
- nearest valid interactable selection,
- on-screen prompt,
- E to interact,
- Esc/E to exit where suitable,
- input ownership while interacting.

## Sitting
Create `SeatInteractable` or equivalent.

When near a valid chair/bench:
- show `Press E to sit`,
- move/snap the player to the seat position,
- orient the player correctly,
- enter SITTING state,
- disable walk/run/jump,
- allow stand using E or Esc,
- place the player safely beside/in front of the chair when standing.

Do not allow sitting on random decorative objects.

## Optional Interactions
If stable:
- simple door use,
- Punch Gate response,
- information board.

## Acceptance Gate
Player can sit and stand repeatedly without clipping badly, teleporting through walls or retaining movement while seated.
