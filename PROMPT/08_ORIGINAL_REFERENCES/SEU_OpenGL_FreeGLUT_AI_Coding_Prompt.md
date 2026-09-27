# AI Coding Prompt — Southeast University 3D Campus / Ground-Floor Scene
## OpenGL + FreeGLUT + C++ + Code::Blocks

You are developing a **3D interactive recreation of Southeast University (SEU)** as a university graphics project using **C++ with OpenGL and FreeGLUT**, compiled and run through **Code::Blocks**.

The official project description is:

> **“An interactive 3D recreation of Southeast University where users can explore the university campus from the outside and enter the building to navigate selected interior areas. The experience will include an interactive gaming room where users can participate in one or more simple 3D mini-games.”**

However, **do not implement the complete project at once**.

## CURRENT DEVELOPMENT PRIORITY

For this stage, the priority is:

1. Build the **3D SEU building and surrounding ground-floor environment**.
2. Reconstruct the supplied **ground-floor layout accurately**.
3. Make the building visually recognizable and spatially coherent.
4. Implement basic first-person/free-camera movement.
5. Implement **WASD movement**.
6. Allow the player to enter the building through **Stair 1 only**.
7. Allow the player to move **up Stair 1 into the interior** and back **down Stair 1 to the exterior**.
8. Add basic collision/walkability so the player cannot simply walk through walls.
9. Keep the other stairs, lifts, gates, and interior areas visually present even if they are not yet interactive.
10. Do **not** spend development effort on the mini-games yet.

The result should be a solid, extensible foundation for the later complete project.

---

# 1. SOURCE MATERIALS

There are two authoritative visual/layout references:

### A. Ground-Floor Layout Image

The supplied image is a top-down hand-prepared layout of the SEU ground floor.

**Treat the image as the primary spatial reference for:**

- relative room positions,
- room boundaries,
- circulation paths,
- driveway placement,
- garden placement,
- stair locations,
- lift locations,
- gates,
- punch gate,
- room adjacency,
- and overall floor-plan proportions.

The image is a **schematic layout**, not a photograph and not a final architectural blueprint. Its colors are primarily being used to distinguish zones and boundaries.

### B. SEU Ground-Floor Scene Description

The supplied Markdown scene specification contains detailed descriptions of:

- architectural identity,
- individual rooms,
- furniture,
- materials,
- colors,
- doors,
- glass walls,
- lifts,
- stairs,
- gates,
- landscaping,
- and collision/boundary rules.

Use that specification together with the layout image.

**Do not discard details from the Markdown specification simply because the image is visually simplified.**

When the image gives spatial information and the Markdown gives object/material/function information, combine them.

---

# 2. IMPORTANT INTERPRETATION OF THE FLOOR PLAN

The image represents the ground-floor plan from a **top-down view**.

The scene should therefore be constructed as a real 3D environment rather than as a flat 2D drawing.

Convert:

- red boundary lines → walls / structural boundaries / collision boundaries,
- room regions → enclosed 3D rooms,
- green areas → open circulation or landscaped areas where applicable,
- yellow areas → driveway / vehicle circulation surfaces,
- garden area → actual ground-level landscaped area,
- orange blocks → doors / access points / highlighted circulation elements,
- stairs → actual 3D stair geometry,
- lifts → actual lift-door/elevator structures,
- glass regions → transparent glass walls,
- room labels → optional physical signage in the 3D environment.

Do not literally render the red lines as red walls unless that is useful for debugging. Their primary meaning is **boundary geometry**.

---

# 3. COORDINATE SYSTEM

Use a clear world coordinate system.

Recommended convention:

- **+X = right side of the floor plan**
- **-X = left side of the floor plan**
- **+Z = upper/top side of the floor plan**
- **-Z = lower/bottom/entrance side**
- **+Y = upward / vertical**

The exact numerical dimensions are up to the implementation, but the relative proportions of the supplied plan must be preserved.

Use a consistent scale throughout the scene.

For example:

- 1 OpenGL world unit can represent approximately 1 meter.
- Wall height should be believable for a university building.
- Door height and width should be human-scale.
- Stair risers and treads should be physically plausible.
- Player/camera height should be approximately human eye level.

Do not make rooms arbitrarily huge or tiny.

---

# 4. OVERALL 3D SCENE STRUCTURE

The initial scene should contain at least these major layers:

## Layer 1 — Exterior Environment

Create:

- surrounding ground,
- main building exterior,
- entrance/front area,
- driveway,
- garden,
- IN Gate,
- OUT Gate,
- guard/security structures,
- exterior architectural masses,
- windows/glazing,
- major facade elements.

## Layer 2 — Ground Floor

Reconstruct the supplied floor plan as a navigable 3D floor.

Include:

- all named rooms,
- corridors/open circulation,
- walls,
- doors,
- stairs,
- lifts,
- washrooms,
- cafeteria,
- food shops,
- administrative spaces,
- gaming rooms,
- stationery,
- banks,
- garden,
- gates,
- punch gate.

## Layer 3 — Vertical Entrance

The most important interactive vertical element at this stage is:

### STAIR 1

This is the **only usable stair**.

The player must be able to:

- approach Stair 1 from the exterior,
- enter the staircase,
- walk upward,
- reach the interior floor,
- continue into the ground-floor interior,
- return to Stair 1,
- walk downward,
- exit back into the exterior.

This is the primary transition between the outside and inside during this development stage.

---

# 5. EXTERIOR ARCHITECTURAL IDENTITY

The building should visually resemble the supplied SEU architectural context.

Use the following architectural language:

- modernist / Brutalist-influenced institutional architecture,
- exposed concrete structural masses,
- large glazed curtain-wall areas,
- strong vertical architectural elements,
- terracotta/rust-orange vertical tower elements,
- concrete gray / off-white structural surfaces,
- reflective glass,
- open ground-level architectural areas,
- modern university-campus character.

The supplied architectural description specifies:

### Left Vertical Tower

A tall, slender vertical architectural shaft with:

- terracotta/rust-orange exterior cladding,
- bilingual Southeast University signage:
  - “SOUTHEAST UNIVERSITY”
  - “সাউথইস্ট বিশ্ববিদ্যালয়”

### Central Glazed Volume

Use:

- large curtain-wall glazing,
- horizontal architectural tiers,
- recessed/open sections,
- visible structural divisions.

### Right Vertical Core

Use:

- exposed concrete appearance,
- repetitive small square recessed openings / perforated matrix,
- strong vertical massing,
- large “SEU” rooftop lettering where visible.

### Ground/Base

Use:

- open colonnade/pilotis character,
- paved entrance circulation,
- small landscaped areas,
- institutional-scale entrance architecture.

Do not overcomplicate the exterior with unsupported architecture. The goal is recognizable SEU-inspired architectural massing that supports the supplied floor plan.

---

# 6. GROUND-FLOOR MASTER LAYOUT

Preserve the following overall spatial arrangement from the image.

## TOP / UPPER ZONE

The upper section contains:

- Food Shop 1
- Food Shop 2
- Cafeteria
- Faculty Lounge
- Food Shop 5
- Food Shop 3
- Food Shop 4
- Female Washroom
- Lift 4
- Lift 3
- Infirmary
- Stair 3
- Lift 1
- Lift 2
- Male Washroom
- Stair 2

## LEFT / LOWER-LEFT ZONE

The lower-left and left-middle section contains:

- Admission Office 2
- Bank 1
- Admission Office 1
- Security Room
- Guard Room
- IN Gate

## CENTRAL ZONE

The central open area contains:

- major circulation/open floor space,
- Punch Gate,
- Stair 1,
- access toward the interior,
- connection between the left administrative side and right recreational/service side.

## RIGHT / MIDDLE-LOWER ZONE

The right-middle section contains:

- Bank 2
- Stationery
- Gaming Room 1
- Gaming Room 2

## BOTTOM / EXTERIOR ZONE

The lower portion contains:

- driveway,
- garden,
- IN Gate,
- OUT Gate,
- Guard Room,
- Security Room,
- Stair 1 entrance.

## RIGHT EDGE

The right edge contains a large vertical driveway/circulation strip.

---

# 7. ROOM-BY-ROOM IMPLEMENTATION REQUIREMENTS

The following must be represented in the 3D scene.

---

## ADMISSION OFFICE 1

### Location

Lower-left central region.

It is below Admission Office 2 and close to the Punch Gate / Stair 1 / security-side zone.

### Appearance

- orange walls,
- off-white/light-gray floor,
- formal administrative appearance,
- transparent glass entry sequence.

### Interior

Create:

- outer transparent glass door,
- another transparent glass door,
- admission desk directly inside/front,
- multiple guardian waiting chairs on the left,
- another internal door,
- locked/private washroom behind that door.

The washroom does not need detailed internal fixtures yet.

The room should look like a public-facing university admission/service office.

---

# ADMISSION OFFICE 2

### Location

Above Admission Office 1 in the left-middle area.

### Appearance

- orange walls,
- formal administrative office,
- slightly more internal/staff-oriented than Admission Office 1.

### Interior

Include:

- multiple desks,
- sofa seating,
- organized office layout,
- appropriate transparent access door.

---

# BANK 1

### Location

Adjacent to Admission Office 2 in the left-middle region.

### Interior

Include:

- front service desk,
- chair,
- money-counting machine.

The bank should look like a compact university banking/service counter.

---

# BANK 2

### Location

Right-middle area near Stationery and Gaming Room 1.

### Interior

Include:

- front desk,
- chair,
- money-counting machine.

Keep it visually similar to Bank 1.

---

# CAFETERIA

### Location

Large top-central area.

This is one of the largest spaces on the floor.

### Appearance

- white walls,
- bright institutional interior,
- spacious,
- active student area.

### Furniture

Include **15 square tables**.

Each table should have appropriate chairs.

The tables should be distributed naturally across the cafeteria while preserving walkable circulation.

Food shops around the cafeteria should visually contribute to the food-service environment.

Do not make the cafeteria empty.

---

# FACULTY LOUNGE

### Location

Upper-left, below the food shops and adjacent to the cafeteria region.

### Appearance

- white walls,
- calmer atmosphere than cafeteria.

### Furniture

Include:

- **5 round tables**
- chairs around each table.

The room should feel suitable for faculty seating, discussion, and informal interaction.

---

# FEMALE WASHROOM

### Location

Upper-left/middle region beside Lift 4 and Lift 3.

### Appearance

- clearly identifiable as Female Washroom,
- simple exterior,
- restricted/private feel.

Do not invent an elaborate internal washroom layout unless needed later.

---

# FOOD SHOP 1

### Location

Top-left edge.

Create a compact food-serving shop.

It must visibly display food.

Include:

- service counter,
- food display,
- believable small-shop interior.

---

# FOOD SHOP 2

### Location

Directly below Food Shop 1.

Create another compact food shop.

It must visibly showcase food.

---

# FOOD SHOP 3

### Location

Top-right side near the driveway.

Create a compact food-serving shop.

Include visible food display.

---

# FOOD SHOP 4

### Location

Below Food Shop 3.

Create another compact food shop with visible food.

---

# FOOD SHOP 5

### Location

Upper-right / top area beside the cafeteria.

Create a compact food shop with visible food display.

---

# GAMING ROOM 1

### Location

Right-middle/lower area.

It is above Gaming Room 2.

### Critical Exterior Requirement

**All outside walls are glass.**

The room must look like a transparent glass-walled recreation room when viewed from outside.

### Interior

Include:

- carrom table,
- table tennis table,
- 8-ball pool table.

Arrange the activities so that they remain visually distinct and have believable clearance.

This room does not need to contain the final interactive mini-games yet.

For now, these are static 3D objects.

---

# GAMING ROOM 2

### Location

Below Gaming Room 1.

### Critical Exterior Requirement

**All outside walls are glass.**

### Interior

Include:

- carrom,
- seating area,
- one table,
- chess,
- cube,
- ludu.

The room should feel more relaxed and board-game-oriented than Gaming Room 1.

All objects can initially be static.

---

# GARDEN

### Location

Large bottom-center area between the IN Gate and OUT Gate zones.

### Appearance

- green landscaped ground,
- some trees,
- open and uncluttered,
- visually separated from the driveway.

Do not fill it with excessive furniture.

The Garden should read as an actual campus landscaping element.

---

# GUARD ROOM

### Location

Bottom-left near the IN Gate.

### Appearance

- white walls,
- compact room,
- entry-monitoring function.

It should look like a small campus security/guard booth.

---

# IN GATE

### Location

Bottom-left entrance.

This is the main inbound exterior access point.

It should visually connect:

- exterior environment,
- driveway,
- guard room,
- Stair 1 entrance area.

---

# INFIRMARY

### Location

Left-middle upper side, above Admission Office 2.

### Appearance

- quiet,
- clean,
- private,
- institutional medical-support room.

Use simple medical-room visual cues only.

Do not invent a large hospital or clinic.

---

# LIFT 1

### Location

Upper-right cluster.

### Appearance

- reflective steel,
- modern elevator,
- reflective steel doors.

At this stage:

**Lift 1 is NOT a usable vertical transportation system.**

It is visual scenery only.

---

# LIFT 2

### Location

Beside Lift 1.

### Appearance

- reflective steel,
- same design family as Lift 1.

Not interactive at this stage.

---

# LIFT 3

### Location

Upper-left cluster beside Lift 4.

### Appearance

- reflective steel,
- modern institutional lift.

Not interactive.

---

# LIFT 4

### Location

Beside Lift 3.

### Appearance

- reflective steel,
- same design family.

Not interactive.

---

# MALE WASHROOM

### Location

Upper-right beside Lift 2.

Include:

- Male Washroom signage,
- simple exterior,
- restricted/private appearance.

Do not over-invent internal fixtures.

---

# OUT GATE

### Location

Bottom-right side.

This is the exterior exit access point.

It should connect logically to the driveway.

---

# PUNCH GATE

### Location

Middle-lower central strip between the admission-side zone and the central circulation zone.

This is an **access-control checkpoint**.

Represent it visually as a controlled passage.

Do not make it a random wall gap.

The player may initially encounter it as a non-essential visual/access-control element. Its detailed interaction can be added later.

---

# SECURITY ROOM

### Location

Lower-left above the Guard Room and near Admission Office 1.

### Appearance

- compact,
- practical,
- monitoring/security function.

---

# STAIR 1 — PRIMARY INTERACTIVE ENTRANCE

This is the **most important stair in the first implementation**.

### Location

Bottom-central area.

It connects the exterior driveway/front area to the interior ground-floor circulation area.

### Appearance

- gray stair body,
- orange handrail/handle,
- institutional concrete stair construction.

### Interaction

**Stair 1 is the ONLY usable stair.**

The player must be able to:

1. Walk outside around the driveway.
2. Approach Stair 1.
3. Enter the Stair 1 area.
4. Walk upward step-by-step.
5. Gain vertical height naturally as they ascend.
6. Arrive at the interior floor level.
7. Walk into the central interior area.
8. Return to Stair 1.
9. Walk down the staircase.
10. Return to the exterior.

Do not teleport the player to the top.

The staircase should be represented by actual steps or a sufficiently detailed stair mesh so that the movement system can interact with it naturally.

### Stair collision

The player should not fall through the stairs.

Use appropriate collision logic or a stair-surface height function.

A practical approach is:

- define Stair 1's bounding region,
- calculate the player's Y height based on progress along the stair direction,
- constrain horizontal movement to the staircase width,
- smoothly raise/lower the player as they move along it.

The implementation does not need to simulate advanced physics.

---

# STAIR 2

### Location

Upper-right horizontal stair block.

### Appearance

- gray institutional stair,
- consistent with the building.

### Interaction

**NOT USABLE.**

Do not allow the player to climb it.

It exists as static architectural scenery.

---

# STAIR 3

### Location

Upper-middle/right region.

### Appearance

- gray institutional stair,
- consistent with the building.

### Interaction

**NOT USABLE.**

It is static scenery only.

---

# STATIONERY

### Location

Right-middle area beside Bank 2 and above Gaming Room 1.

The room/shop must visibly look stocked.

Include visual examples such as:

- notebooks,
- pens,
- paper,
- folders,
- office supplies,
- school supplies,
- stacked merchandise,
- display shelves.

Do not make it an empty room.

---

# 8. COMMON MATERIAL RULES

## Floors

General interior flooring:

- off-white,
- light gray,
- clean,
- institutional,
- slightly reflective or matte depending on location.

## Walls

Use the specific room colors defined above.

Do not make every room the same color.

## Glass

Use transparent glass for:

- Gaming Room 1 exterior walls,
- Gaming Room 2 exterior walls,
- transparent admission-office doors,
- architectural curtain-wall areas.

Glass should have:

- transparency,
- subtle reflections,
- believable thickness,
- visible framing.

Do not make glass completely invisible.

## Lifts

Use:

- steel,
- reflective surfaces,
- clean modern doors.

## Stairs

Use:

- concrete gray / off-white gray body,
- orange handrail on Stair 1.

---

# 9. PLAYER MOVEMENT

For this development stage, implement a simple first-person or free-camera controller.

## Required Controls

### W

Move forward.

### S

Move backward.

### A

Strafe/move left.

### D

Strafe/move right.

### Mouse

Preferably use mouse movement for looking around if practical.

If mouse-look complicates the initial Code::Blocks setup, implement keyboard-based camera rotation first and keep the architecture modular so mouse-look can be added later.

### Optional

You may include:

- ESC → exit
- R → reset player position
- Space → optional jump only if it does not interfere with staircase movement.

Do not make jumping necessary for normal navigation.

---

# 10. PLAYER / CAMERA MODEL

Use a human-scale camera.

Recommended starting values:

- eye height around 1.6–1.8 world units,
- moderate movement speed,
- moderate mouse sensitivity,
- no extreme FOV,
- smooth movement.

The camera must remain upright.

Do not allow uncontrolled flying.

The initial controller should behave like a basic first-person university exploration system.

---

# 11. COLLISION SYSTEM

Implement basic collision.

The player should not be able to:

- walk through exterior walls,
- walk through room walls,
- walk through closed boundaries,
- walk through the building shell,
- walk through furniture where collision is intentionally required,
- bypass Stair 1 by clipping through the surrounding wall.

The collision system does not need to be a complex physics engine.

Simple methods are acceptable:

- axis-aligned bounding boxes,
- rectangles,
- circles,
- room bounding regions,
- wall segments,
- explicit collision zones.

Prioritize reliability and understandable code.

---

# 12. STAIR 1 MOVEMENT LOGIC

This deserves special attention.

The staircase is not just decoration.

Create a defined staircase region:

```text
Exterior / lower level
        ↓
      Stair 1
        ↓
Interior / upper level
```

The player's vertical position should change according to their location on the staircase.

For example, conceptually:

```text
stairProgress = distanceAlongStair / stairLength

playerY = lowerY + stairProgress * stairHeight
```

Clamp the progress between 0 and 1.

When the player reaches the bottom:

```text
playerY = exteriorFloorY
```

When the player reaches the top:

```text
playerY = interiorFloorY
```

Do not force the player to jump between these heights.

The transition should feel like walking up/down a real staircase.

---

# 13. NON-USABLE VERTICAL ELEMENTS

For this stage:

### Stair 1
**Usable.**

### Stair 2
**Static only.**

### Stair 3
**Static only.**

### Lift 1
**Static only.**

### Lift 2
**Static only.**

### Lift 3
**Static only.**

### Lift 4
**Static only.**

Do not implement elevator logic yet.

---

# 14. DRIVEWAY

The driveway is a major part of the exterior ground plane.

The image shows driveway regions:

- along the right side of the building,
- across the lower/front side of the building,
- around the Garden.

Create a coherent paved driveway surface.

It should:

- have a road/pavement appearance,
- connect the IN Gate and OUT Gate,
- surround/relate to the Garden,
- provide exterior walking space,
- provide the visual transition toward the building entrance.

Do not turn the driveway into an indoor floor.

---

# 15. GARDEN AND LANDSCAPING

The Garden is a major visual anchor.

Use:

- green grass/ground,
- several trees,
- simple campus landscaping,
- possibly low vegetation.

Keep it visually clean.

Do not overcrowd the garden.

The garden should clearly contrast against the paved driveway.

---

# 16. BUILDING LIGHTING

Use basic OpenGL lighting.

The initial version should include:

- one primary directional/light source,
- ambient contribution,
- diffuse lighting,
- basic specular response where useful.

Interior areas should not be completely dark.

Use simple institutional lighting:

- ceiling lights,
- soft ambient light,
- brighter cafeteria/service areas,
- reasonable lighting near entrance and circulation.

Do not make lighting the primary focus of the first implementation.

---

# 17. RENDERING STYLE

The scene should be recognizable and reasonably realistic while remaining feasible for a FreeGLUT university graphics project.

Prefer:

- solid geometry,
- simple textures where useful,
- basic materials,
- lighting,
- transparency for glass,
- repeated procedural geometry for furniture,
- modular drawing functions.

Do not require a modern game engine.

Do not depend on Unreal Engine, Unity, Godot, or Blender runtime.

The actual application must be:

**C++ + OpenGL + FreeGLUT**

and should be buildable through:

**Code::Blocks**

---

# 18. CODE ARCHITECTURE

Do not put the entire project into one enormous `main()` function.

Use modular functions/classes.

A reasonable structure could include:

```cpp
drawBuilding();
drawExterior();
drawGround();
drawDriveway();
drawGarden();

drawCafeteria();
drawFacultyLounge();
drawAdmissionOffice1();
drawAdmissionOffice2();

drawBank1();
drawBank2();

drawFoodShop1();
drawFoodShop2();
drawFoodShop3();
drawFoodShop4();
drawFoodShop5();

drawGamingRoom1();
drawGamingRoom2();

drawStationery();

drawInfirmary();
drawWashrooms();

drawLift1();
drawLift2();
drawLift3();
drawLift4();

drawStair1();
drawStair2();
drawStair3();

drawGuardRoom();
drawSecurityRoom();

drawInGate();
drawOutGate();
drawPunchGate();
```

For furniture, use reusable primitives:

```cpp
drawTable();
drawChair();
drawDesk();
drawSofa();
drawDoor();
drawGlassWall();
drawWindow();
drawTree();
drawLift();
drawStair();
```

For navigation:

```cpp
updatePlayer();
handleKeyboard();
handleMouse();
checkCollision();
updateStairMovement();
```

For rendering:

```cpp
display();
reshape();
```

The exact architecture may differ, but it must remain modular.

---

# 19. CODEBLOCKS COMPATIBILITY

The generated project must be practical for Code::Blocks.

Avoid requiring:

- CMake,
- advanced package managers,
- Unity,
- Unreal,
- external game engines,
- non-standard compiler extensions,
- unnecessary modern libraries.

Use standard C++ and the OpenGL/FreeGLUT APIs available in a typical Code::Blocks OpenGL setup.

If textures are used, keep the texture-loading system simple and clearly documented.

If external assets are used, make the paths easy to configure.

Prefer procedural geometry for the first build so that the project can compile and run without requiring dozens of external asset files.

---

# 20. DEVELOPMENT PHASES

Do NOT try to implement everything simultaneously.

Build the project in phases.

## Phase 1 — Scene Skeleton

Implement:

- world coordinate system,
- ground,
- building shell,
- major walls,
- driveway,
- garden,
- exterior massing,
- main floor boundaries.

Verify the scale.

## Phase 2 — Ground-Floor Layout

Add:

- all rooms,
- corridors,
- major partitions,
- gates,
- lifts,
- stairs,
- glass rooms.

Verify the plan against the supplied image.

## Phase 3 — Interior Objects

Add:

- tables,
- chairs,
- desks,
- sofas,
- counters,
- food displays,
- stationery displays,
- gaming equipment.

## Phase 4 — Exterior Architecture

Improve:

- facade,
- concrete structure,
- terracotta tower,
- curtain wall,
- windows,
- SEU signage,
- landscaping.

## Phase 5 — Player Navigation

Implement:

- WASD,
- camera,
- collision,
- Stair 1 ascent,
- Stair 1 descent,
- exterior/interior transition.

## Phase 6 — Visual Polish

Add:

- lighting,
- material refinement,
- glass reflections/transparency,
- signage,
- environmental details.

## Phase 7 — Later Project Features

Only after the building and navigation are stable:

- interactive Gaming Room,
- mini-games,
- advanced interactions,
- additional interior navigation,
- elevator interaction,
- additional stairs.

---

# 21. IMPORTANT: DO NOT IMPLEMENT THE MINI-GAMES YET

The official project mentions an interactive gaming room.

That feature is part of the eventual project, but it is **not the current priority**.

For now:

- Gaming Room 1 should be visually complete.
- Gaming Room 2 should be visually complete.
- Their furniture and equipment should exist as 3D objects.
- The rooms should be accessible visually where appropriate.
- No mini-game logic is required yet.

Keep the code modular so mini-games can be added later.

---

# 22. IMPORTANT: DO NOT MAKE ALL STAIRS USABLE

This is a specific project requirement.

Only:

## STAIR 1

is usable.

The other stairs are visual architectural elements.

Do not accidentally allow the player to climb:

- Stair 2,
- Stair 3.

Likewise, do not make lifts functional in this version.

---

# 23. FLOOR-PLAN FIDELITY CHECK

Before considering the first version complete, verify the following:

- [ ] Cafeteria occupies the large top-central region.
- [ ] Food Shops 1 and 2 are at the top-left.
- [ ] Food Shop 5 is near the upper-right cafeteria area.
- [ ] Food Shops 3 and 4 are along the upper-right side.
- [ ] Faculty Lounge is below the left food-shop region.
- [ ] Female Washroom is beside Lift 4/Lift 3.
- [ ] Infirmary is below the female washroom/lift region.
- [ ] Stair 3 is in the upper-middle/right circulation region.
- [ ] Lift 1 and Lift 2 are in the upper-right cluster.
- [ ] Male Washroom is beside Lift 2.
- [ ] Stair 2 is in the upper-right region.
- [ ] Admission Office 2 is on the left-middle/lower-left side.
- [ ] Bank 1 is adjacent to Admission Office 2.
- [ ] Admission Office 1 is below Admission Office 2.
- [ ] Security Room is near the lower-left entrance zone.
- [ ] Guard Room is near the IN Gate.
- [ ] Bank 2 is on the right-middle side.
- [ ] Stationery is beside Bank 2.
- [ ] Gaming Room 1 is above Gaming Room 2.
- [ ] Both Gaming Rooms have glass exterior walls.
- [ ] Punch Gate is in the central lower strip.
- [ ] Stair 1 is at the bottom-center.
- [ ] Stair 1 is the only usable stair.
- [ ] Garden occupies the large bottom-center outdoor area.
- [ ] IN Gate is bottom-left.
- [ ] OUT Gate is bottom-right.
- [ ] Driveway surrounds the main front/garden circulation area.
- [ ] The right side has the long driveway strip.

---

# 24. VISUAL QUALITY TARGET

The final result should look like a **realistic but academically manageable OpenGL recreation of a university campus building**.

It should not look like:

- a flat CAD drawing,
- a 2D floor plan pasted into 3D,
- a generic office,
- an empty box with labels,
- a procedurally generated maze,
- or an unrelated commercial building.

It should look like:

- a real university,
- with recognizable architectural massing,
- actual rooms,
- actual furniture,
- functional circulation,
- believable scale,
- a clear entrance,
- landscaped exterior space,
- and an interior that corresponds directly to the supplied SEU ground-floor plan.

---

# 25. FIRST IMPLEMENTATION DELIVERABLE

For the first implementation, generate a **complete compilable FreeGLUT/OpenGL C++ project suitable for Code::Blocks**.

At minimum, provide:

1. `main.cpp`
2. any additional `.cpp` files required
3. any `.h` files required
4. clear instructions for adding/linking the source files in Code::Blocks
5. required OpenGL/FreeGLUT libraries
6. keyboard controls
7. camera controls
8. collision logic
9. Stair 1 movement logic
10. a complete first-pass 3D building scene

Do not give only pseudocode.

Do not provide placeholder comments such as:

```cpp
// TODO: build cafeteria
```

for the major scene components.

Actually implement the scene.

If the complete implementation is too large for one response, split it into **coherent compilable stages**, but ensure every stage builds on the previous one and does not arbitrarily rewrite working code.

---

# 26. DEBUG MODE

Add a simple optional debug mode if practical.

Useful debug information:

- player X/Y/Z,
- current floor/level,
- whether player is on Stair 1,
- collision state,
- camera direction.

A simple toggle such as `F1` can be used.

Debug geometry may include:

- collision boxes,
- staircase bounds,
- room boundaries.

Make it easy to disable for the final presentation.

---

# 27. FINAL DEVELOPMENT PRINCIPLE

**Build the building first.**

Do not prioritize gameplay before the environment exists.

The order of importance for this stage is:

1. **Correct SEU building/floor-plan structure**
2. **Correct room placement**
3. **Correct architectural massing**
4. **Correct Stair 1 entrance and vertical transition**
5. **Basic WASD navigation**
6. **Collision**
7. **Furniture and room detail**
8. **Lighting/material polish**
9. **Future gaming interaction**

The supplied floor-plan image and the supplied SEU scene-description Markdown are the source of truth for the environment.

When making implementation decisions that are not explicitly specified, choose the simplest technically reliable solution that preserves the documented layout and leaves the project easy to extend later.

## FINAL REQUEST TO THE CODING AI

**Generate the OpenGL + FreeGLUT + C++ implementation for this project in a Code::Blocks-compatible form. Start with the complete 3D building/environment and basic navigation. Reconstruct the supplied SEU ground-floor plan faithfully. Implement only Stair 1 as a usable stair connecting the exterior entrance area to the interior. Use WASD for movement and provide basic camera control and collision. Keep all other stairs and lifts static. Do not implement the gaming mini-games yet. Make the code modular, readable, compilable, and easy to extend.**
