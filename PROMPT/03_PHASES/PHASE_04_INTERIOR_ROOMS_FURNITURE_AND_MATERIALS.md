# PHASE 04 — Interior Rooms, Furniture, Doors, Glass and Materials

## Objective
Turn the blockout into a readable university interior.

## Implement
For each named room, use the supplied descriptions for:
- wall/floor material,
- glass walls/doors,
- counters,
- desks,
- tables,
- chairs,
- benches,
- cabinets/shelves,
- cafeteria seating,
- food shop counters,
- bank counters,
- stationery shelving,
- infirmary essentials,
- washroom essentials,
- gaming room furniture,
- lift doors,
- stair rails,
- Punch Gate objects,
- simple signs/nameplates.

Keep furniture modular. Example reusable functions/classes:
- drawDesk
- drawChair
- drawBench
- drawCounter
- drawShelf
- drawDoor
- drawGlassWall
- drawLiftDoor
- drawSign
- drawTable

## Performance Rule
Repeated furniture should reuse geometry/functions rather than copy-pasted vertex code.

## Acceptance Gate
A person navigating the scene should be able to identify the major room purpose from geometry/signage without a top-down map. No furniture blocks required circulation paths.


## Complex Objects + Exterior View Requirement

### Complex Objects
At least several scene elements must be hierarchical complex objects built from reusable components. Required examples should include at least:
- a staircase assembly,
- a counter/desk assembly,
- a gaming-room setup,
- one gate/lift/player-style composite object.

### Interior-to-Exterior View
Implement at least one interior location with a clear view of the real external environment through a glass wall/window/door/opening.

The viewer must be able to stand inside and see exterior geometry such as:
- garden,
- driveway,
- gate,
- sky/background,
or other campus surroundings.

Do not fake this using a flat opaque image if actual exterior geometry exists behind the opening.

### Acceptance Gate Additions
- complex objects are visibly composed of multiple parts,
- exterior environment is visible from inside through at least one architectural viewing element.
