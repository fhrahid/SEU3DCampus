# PHASE 02 — Campus Blockout From the Supplied Layout

## Objective
Create an accurate navigable gray-box/blockout of the SEU exterior site and complete ground-floor plan.

## Reference Priority
Use `location.md` and the supplied top-view image as the primary sources.

## Implement
- site boundary,
- front driveway,
- right-side driveway,
- Garden footprint,
- IN Gate,
- OUT Gate,
- Guard Room,
- Stair 1,
- central ground-floor circulation space,
- Punch Gate,
- all named rooms as correctly positioned block volumes,
- stairs 2 and 3,
- lifts,
- Gaming Room 1/2 if both are in the reference,
- room openings/door gaps.

Do not spend time on fine furniture or facade detailing.

## Critical Requirements
- Stair 1 is the usable exterior-to-ground-floor entrance.
- Admission Office 2 remains inside Admission Office 1.
- Garden is exterior.
- Main circulation stays open.
- Right-edge driveway stays exterior.
- Do not turn the reference's colored guide lines directly into arbitrary colored walls.

## Debug Features
Add:
- top-down debug camera,
- room boundary colors,
- optional room-name labels,
- collider visualization toggle.

## Acceptance Gate
A top-down debug view must visibly correspond to the supplied floor-plan reference in adjacency and circulation. Player-sized test capsule must be able to travel from IN Gate to Stair 1 and into the central ground-floor area without crossing a wall.
