# PHASE 13A — Mandatory Course Graphics Requirements Audit

## Objective
Before final optimization, verify that every explicit graphics-course requirement is actually implemented and demonstrable.

## Requirement 1 — Basic Transformations
Provide a dedicated transformation-demo mode/object.

Must visibly support:
- translation,
- rotation,
- scaling,
using keyboard and/or mouse.

Record controls in `CONTROLS.md`.

## Requirement 2 — Complex Objects
Identify at least three hierarchical complex objects in the scene.

Recommended:
- staircase + railings,
- campus gate,
- gaming table/game station,
- reception counter,
- articulated player,
- Rubik's Cube.

Document their component primitives.

## Requirement 3 — Continuous Rotation
Verify at least one campus object rotates continuously using delta time.

Recommended: ceiling fan.

## Requirement 4 — View of External Environment
Stand inside the building and verify the real exterior scene can be seen through:
- glass wall,
- window,
- glass door,
or equivalent opening.

## Requirement 5 — Two Lights + Materials
Verify two or more enabled light sources.

For each major material type, verify:
- ambient,
- diffuse,
- specular,
- shininess where useful.

## Requirement 6 — Object and Viewing Coordinates
Create `docs/GRAPHICS_REQUIREMENTS.md`.

Explain:
- model/object transformations,
- viewing/camera transformations,
- where each occurs in source code.

## Requirement 7 — Textures
Verify at least:
- furniture texture,
- wall/building texture,
- floor texture,
- sign/logo/picture texture.

## Requirement 8 — Algorithmic Games
Verify all five games contain working rule/state algorithms, not only decorative 3D models.

## Acceptance Gate
Create a requirement matrix with columns:

| Requirement | Implemented | Source File | Function/Class | Control/Location | Demo Procedure | PASS/FAIL |

Every row must be PASS before proceeding to final QA.
