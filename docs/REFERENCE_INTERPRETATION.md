# Reference interpretation

## Sources and priority

`PROMPT/08_ORIGINAL_REFERENCES/location.md` defines named spaces and relationships. The supplied annotated plan (`seu3dcampus.png`, duplicated at the repository root) defines approximate placement and openings. `seu.jpg` shows the exterior's red brick tower, pale concrete mass, vertical glazing, horizontal bands, and SEU sign. The JPEG named `top view of punch gate right side is game room.jpg` actually shows a multi-storey interior atrium with glazing and walkways; it is useful for material character but not room positions. The legacy OpenGL prompt supplies implementation ideas and does not override these facts.

## Locked facts

- Plan right is +X; plan top/rear is +Z; vertical is +Y. The entire diagram is one ground floor.
- Entry path: start outside → bottom-left IN Gate → front driveway above the garden → Stair 1 → central ground-floor circulation. The OUT Gate is at bottom-right. A guard room is near the IN Gate; the security room is just inside/near the lower-left building frontage.
- A rectangular outdoor garden with trees lies between the two gates. A paved front driveway separates it from the building and continues up the far-right edge.
- Stair 1 is the usable exterior-to-ground-floor stair at the front center. Stair 2 at the upper-right and Stair 3 toward the upper-middle lead toward an unbuilt next floor and remain unusable.
- The Punch Gate spans the lower central approach beyond Stair 1; the central circulation space stays connected and open.
- Lower-left administration contains Admission Office 1 with Admission Office 2 physically inside it, plus separate Bank 1, infirmary, security room and guard room. Admission Office 2 must have no independent corridor entrance.
- Upper-left/upper-middle contains Faculty Lounge, female washroom, Lift 4 and Lift 3, Cafeteria and Food Shops 1 and 2. Food Shop 5 is at the cafeteria's upper-right edge.
- Upper-right contains Food Shops 3 and 4 along the right driveway, Stair 2, side-by-side Lifts 1 and 2 and the male washroom.
- Right-middle contains separate Bank 2 and Stationery. The lower-right Gaming Room 1 contains a partitioned Gaming Room 2. Entry into Gaming Room 2 is only through Gaming Room 1. Gaming Room 1 has carrom, table tennis and pool; Gaming Room 2 has carrom, seats, table, chess, cube and ludo. Exterior-facing gaming-room walls use glass.
- Bank 1 and Bank 2 are separate spaces; their numbering does not imply nesting. The same is true of lifts and stairs.

## Assumptions requiring visual judgment

- The annotated plan is schematic, not a survey. World dimensions, wall thickness, door widths, floor rise, and furniture sizes are implementation assumptions. They are centralized in layout/config data and can be adjusted without changing room topology.
- The plan's orange blocks indicate openings or prominent elements, but exact door swings are unclear. Use simple open door gaps where circulation is required.
- The plan labels Gaming Room 2 below Gaming Room 1; a partition and internal door must connect them. The exact furniture arrangement and partition glazing are not specified.
- The atrium photo is not a plan of the punch gate. Do not derive a new courtyard or extra floors from it.
- Exterior facade masses are stylized from the photo; the photo cannot establish precise heights or ground-floor room boundaries.
