# Reference Interpretation & Canonical SEU Campus Specification

## 1. Main Building Architecture (Southeast University - SEU)

- **Architectural Style**: Modernist/Brutalist-influenced institutional design featuring a multi-tiered concrete skeleton with large curtain-wall glazed sections.
- **Left Vertical Tower**: A tall, slender vertical shaft with an exterior finished in terracotta cladding rising to 22 meters, bearing illuminated bilingual signage ("SOUTHEAST UNIVERSITY" / "সাউথইস্ট বিশ্ববিদ্যালয়").
- **Central Atrium & Glazed Volume**: A multi-story grid of glass curtain walls divided into 4 horizontal tiers, with recessed balconies and open voids breaking up the facade.
- **Right Vertical Core / Pylon**: A monolithic exposed concrete tower rising to 21 meters featuring a perforated matrix of small square recessed openings (brise-soleil or ventilation/light punctures), topped with large 3D rooftop letters spelling "SEU".
- **Ground & Base Level**: Open colonnade/pilotis structure at street level, flanked by paved entrance ramps and small landscaped patches.

---

## 2. Color Palette & Materials

- **Terracotta / Rust Orange**: Featured prominently on the vertical left tower of the main university building (`{0.72, 0.30, 0.15}`), fluted vertical shadow reveals (`{0.50, 0.18, 0.08}`), administrative office perimeter walls (Admission 1, Admission 2, Bank 1, Bank 2, Dean's Office), orange safety circulation gates, and staircase handrails (`{0.90, 0.42, 0.08}`).
- **Concrete Gray / Off-White**: Dominates the exposed architectural concrete tower on the right (`{0.76, 0.78, 0.80}`), horizontal floor slabs (`{0.84, 0.85, 0.87}`), ground pilotis colonnade structural pillars (`{0.86, 0.88, 0.90}`), off-white interior walls (`{0.91, 0.92, 0.94}`), and surrounding campus periphery buildings.
- **Reflective Steel Blue & Cyan**: Present in the 4-tier glass curtain wall of the central building (`{0.22, 0.65, 0.78, 0.55}`), transparent architectural glass doors, atrium lightwell safety balustrades, and the large modern high-rise in the right background (`{0.24, 0.54, 0.68}` and `{0.22, 0.60, 0.75, 0.65}`).
- **Deep Forest & Olive Green**: Found across the lush multi-tiered tree canopy in the foreground (lower broad canopy `{0.11, 0.32, 0.13}`, upper cresting dome `{0.22, 0.44, 0.16}`) and surrounding ground-level foliage (garden lawn `{0.14, 0.38, 0.16}` and perimeter hedge borders `{0.12, 0.34, 0.14}`).
- **Overcast Muted White / Light Gray**: Fills the uniform, hazy sky across the entire background (`glClearColor(0.84, 0.87, 0.90, 1.0)` with matching atmospheric depth fog `glFogfv(0.84, 0.87, 0.90, 1.0)` and diffuse overcast ambient daylighting).
- **Earthy Brown & Dark Charcoal**: Visible along the paved ground and driveways (`{0.56, 0.50, 0.40}`), rooftops of adjacent smaller structures (`{0.46, 0.38, 0.30}` and `{0.20, 0.22, 0.25}`), door frames, window mullions, and road infrastructure (dark charcoal asphalt `{0.22, 0.23, 0.25}`).

---

## 3. Room-by-Room Canonical Specifications

### ADMISSION OFFICE 1
- **Location**: Lower-left central area, below Admission Office 2 and near the punch-gate/stair-side zone.
- **Visual Identity**: All walls orange; floor off-white / light gray; entry style: glass door after glass door.
- **Required Sequence & Elements**:
  - Outer transparent glass door.
  - Another transparent glass door.
  - Inside front area: admission desk directly in front.
  - Left side: two parallel rows of guardian waiting chairs facing the office center.
  - Interior door leading to a locked washroom with clear signage.
- **Atmosphere**: Formal, front-facing administrative first-contact office.

### ADMISSION OFFICE 2
- **Location**: Above Admission Office 1, on the left-middle side.
- **Visual Identity**: All walls orange; formal, staff/consultation workspace.
- **Required Elements**: Multiple desks, sofa seating, organized consultation office setup, transparent access door.

### BANK 1
- **Location**: Adjacent to Admission Office 2 in the left-middle area.
- **Required Elements**: Front desk, customer/teller chair, money counting machine with indicator display.
- **Visual Feel**: Compact, secure institutional banking corner.

### BANK 2
- **Location**: Right-middle area, near Stationery and Gaming Room 1.
- **Required Elements**: Front desk, chair, money counting machine.
- **Visual Feel**: Compact public bank transaction counter.

### CAFETERIA
- **Location**: Large top-central area; the largest zone in the campus layout.
- **Wall / Surface Identity**: White backgrounded walls, bright, clean, open student-friendly dining zone.
- **Required Furniture & Seating**:
  - Exactly 15 square tables arranged in a clean, functional 3x5 dining matrix.
  - 4 chairs per table, neatly tucked in and properly oriented toward the table.
  - Clear aisles between rows and columns for pedestrian circulation.
  - Visually connected to neighboring food shops.

### FACULTY LOUNGE
- **Location**: Upper-left, below the top food shops and beside the cafeteria zone.
- **Wall Identity**: White walls; calmer, reserved discussion atmosphere.
- **Required Furniture**: Exactly 5 round tables with 4 comfortable chairs symmetrically arranged around each, facing the table center.

### FEMALE WASHROOM
- **Location**: Upper-left middle, beside Lift 4 / Lift 3.
- **Identity**: Clearly labeled signage, simple discreet exterior presentation, restricted private feel.

### FOOD SHOPS 1 TO 5
- **Food Shop 1**: Top-left edge; visible food display counter.
- **Food Shop 2**: Below Food Shop 1 at top-left side; visible food display.
- **Food Shop 3**: Top-right side near the right driveway; visible food display counter.
- **Food Shop 4**: Below Food Shop 3 on the right side; compact visible serving counter.
- **Food Shop 5**: Upper-right area beside cafeteria; active food service display.

### GAMING ROOM 1
- **Location**: Right-middle lower area, above Gaming Room 2.
- **Exterior Wall Rule**: All outside walls are transparent glass walls.
- **Interior Elements**: Carrom table with corner stools, tournament table tennis table with net and paddles, 8-ball pool table with cues and billiard balls.
- **Visual Feel**: Youthful, active indoor student recreation suite.

### GAMING ROOM 2
- **Location**: Right-middle lower area, below Gaming Room 1.
- **Exterior Wall Rule**: All outside walls are transparent glass walls.
- **Interior Elements**: Carrom table, lounge sofa sitting area, Chess table with player seats, Rubik's Cube display, Ludo table.
- **Access Rule**: Accessed exclusively via Gaming Room 1 internal door.

### GARDEN
- **Location**: Bottom-center large green area between IN and OUT Gate zones.
- **Elements**: Soft landscaped grass patch with trees, visually separated from driveways.

### GUARD ROOM
- **Location**: Bottom-left near IN Gate.
- **Wall Identity**: White walls; compact security monitoring post.

### IN GATE
- **Location**: Bottom-left entrance point for inbound pedestrian and vehicle access.

### INFIRMARY
- **Location**: Left-middle upper side, above Admission Office 2.
- **Visual Feel**: Medical support room, quiet and institutional medical identity, clear signage, patient beds/screens.

### LIFTS 1, 2, 3, 4
- **Lifts 1 & 2**: Upper-right cluster, side-by-side.
- **Lifts 3 & 4**: Upper-left cluster, side-by-side.
- **Material Rule**: Reflective steel finish, split elevator doors, modern public look.

### MALE WASHROOM
- **Location**: Upper-right side beside Lift 2.
- **Visual Feel**: Standard restricted washroom with clear signage.

### OUT GATE
- **Location**: Bottom-right exit point connecting to the driveway.

### PUNCH GATE
- **Location**: Middle-lower central strip between admission zone and central circulation.
- **Visual Feel**: Controlled security checkpoint barrier.

### SECURITY ROOM
- **Location**: Lower-left side, above Guard Room and near Admission Office 1.
- **Visual Feel**: Operational security support room.

### STAIRS 1, 2, 3
- **Stair 1**: Exterior front-central stair ascending from street level (Y=0) to Ground Floor lobby (Y=1.2m); concrete gray steps with orange safety handrails.
- **Stair 3**: Central 16-step grand staircase connecting Ground Floor (Y=1.2m) to Second Floor (Y=5.2m), complete with continuous orange safety handrails and treads.
- **Stair 2**: Secondary 16-step staircase connecting Ground Floor (Y=1.2m) to Second Floor (Y=5.2m).

### STATIONERY
- **Location**: Right-middle side, beside Bank 2 and above Gaming Room 1.
- **Visual Content**: Fully stocked with notebooks, pens, school supplies, and stacked display shelves.

---

## 4. Second Floor Specifications (Floor Level: Y = 5.2m)

- **Central Atrium Void**: Open double-height lightwell overlooking the Ground Floor punch gate and lobby, enclosed with polished safety glass balustrades and brushed chrome railings.
- **Central Library & Digital Commons**: Study carrels, mahogany reading tables with desk lamps, bookshelves with books, digital search terminals.
- **CSE & AI Research Lab**: Rows of workstation desks with dual-monitors, keyboards, computer chairs, server rack cabinet with indicator lights.
- **Smart Classroom 201**: Instructor podium, whiteboard, and 4 rows of student desk-chairs.
- **Dean's Office**: Executive consultation desk, leather office chair, and visitor sofa suite.
- **Sky Terrace**: Scenic outdoor balcony on the south facade with glass balustrades, outdoor lounge tables, and panoramic views of the campus grounds.

---

## 5. Drone Mode Specifications

- **Free Flight Drone Mode**: Allows the user to pilot a free-flying inspection drone anywhere in 3D space (`WASD` fly, `Space`/`E` ascend, `C`/`Q` descend, `Shift` turbo, mouse look/pitch/yaw).
- **Playable Chase Drone Mode**: Puts the camera into a third-person aerial follow mode where the user can fully play the game (walk, run, jump, climb stairs to 2nd floor, sit, play minigames) while viewing their 3D student avatar.
- **HUD & Telemetry**: Real-time on-screen telemetry showing drone altitude, 3D coordinates, camera yaw/pitch, and player locomotion state.

---

## 6. Common Object & Material Rules

1. **Architectural Glass Doors**: Every room entrance features a state-of-the-art commercial architectural glass door:
   - **Structural Profile**: Dark bronze / graphite anodized aluminum frame with transom header bar, ceiling channel, and brushed stainless steel threshold plate.
   - **Glazed Transom & Signage**: Stationary upper glass transom panel with a floating edge-lit acrylic/aluminum blade plaque bearing warm amber/gold LED glowing room typography.
   - **Tempered Glass Leaf**: High-clarity safety glass with cyan refraction tint and polished beveled edge profiles.
   - **Safety Manifestation**: Dual horizontal frosted manifestation decals (wide eye-level band with geometric accent pinstripes, and sleek waist-level band) ensuring visibility and architectural realism.
   - **Stainless Steel Hardware**: Precision top and bottom corner patch pivot fittings, concealed floor closer cover plate, and bottom patch lock.
   - **Tubular Push/Pull Handles**: Iconic 1.35-meter tall vertical tubular stainless steel handles mounted on both exterior and interior faces with machined standoff mounting posts through the glass.
   - **Double & Single Configurations**: Grand double glass doors for primary entrances (Gaming Entry, Cafeteria, Admission 1, Central Library, CSE Lab) and single glass doors for interior suites (Gaming Room 2, Offices, Classrooms).
2. **Glass Walls**: Large floor-to-ceiling glass walls for Gaming Rooms 1 & 2 and facade atriums, framed with aluminum base/ceiling channels and continuous frosted manifestation bands.
3. **Reflective Lift Finish**: Steel reflective elevator doors for all four lifts.
4. **Floor Base**: Continuous off-white ceramic tile with checker texture throughout interior circulation and rooms.
5. **Collision Boundaries**: Solid walls block player movement; multi-floor height checks ensure smooth traversal across stairs and upper floor slabs.
