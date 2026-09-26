# PHASE 00 — Repository Audit + Reference Lock

## Objective
Understand the current codebase and lock the SEU reference interpretation before coding.

## Agent Instructions
Read:
- `00_REFERENCES/location.md`
- `00_REFERENCES/SEU_OpenGL_FreeGLUT_AI_Coding_Prompt.md`
- all supplied reference images.

Inspect the current source tree and build configuration.

Create:
- `PROJECT_STATUS.md`
- `BUILD_INSTRUCTIONS.md`
- `docs/REFERENCE_INTERPRETATION.md`
- `docs/LAYOUT_COORDINATES.md`

`REFERENCE_INTERPRETATION.md` must list:
- entrance sequence,
- IN Gate,
- OUT Gate,
- Garden,
- Stair 1,
- Stair 2,
- Stair 3,
- Punch Gate,
- lifts,
- administrative zone,
- cafeteria/social zone,
- gaming room position,
- stationery/banks/washrooms,
- nested Admission Office 2 inside Admission Office 1,
- any uncertain details.

`LAYOUT_COORDINATES.md` must define a proposed coordinate grid and approximate bounds for every major room/zone without pretending the values are exact surveyed measurements.

Do not perform major rendering changes in this phase.

## Acceptance Gate
Pass only if:
- project can be built or all existing build blockers are documented,
- every supplied reference has been inspected,
- spatial facts and assumptions are separated,
- coordinate convention is fixed,
- no unsupported room has been invented.
