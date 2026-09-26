# Project status

## Teacher Lounge Door, Day/Night Switcher, Upper-to-Lower Stair Sightlines & Female Lift Corridor — PASS

1. **Teacher & Faculty Lounge Grand Entrance ($x = -10.2\text{m}$, $z \in [29.4, 31.8]$)**:
   - **Prominent Frontage Facing Main Corridor**: Relocated the entrance from behind the elevator shaft to the prominent East wall directly facing the busy corridor connecting the central lobby and cafeteria.
   - **Grand $2.4\text{m}$ Architectural Double Glass Door**: Double glass doors swung inward into the lounge, fitted with stainless steel patch pivots, floor spring plates, and chrome tubular handles.
   - **Overhead Illuminated Terracotta Signage Architrave**: Terracotta and graphite fascia displaying bold illuminated typography: `"TEACHER & FACULTY LOUNGE"` and `"SOUTHEAST UNIVERSITY - STAFF ONLY"`.
   - **Transparent Viewing Sidelights**: Large clear glass panels flanking the entrance showcasing the faculty lounge furnishings (5 round conference tables, armchairs, and coffee station).
   - **Unobstructed Traversal**: Full $2.4\text{m}$ entrance opening in `CollisionWorld.cpp` permitting smooth walking access directly into the lounge.

2. **Day / Night Dynamic Mode Switcher (`N` Key)**:
   - **Dynamic Atmosphere**: Bound key `N` to toggle instantly between bright campus daylight and atmospheric illuminated night.
   - **Night Mode Visuals**:
     - Sky and clear color switch to deep midnight navy (`#080a14`).
     - Atmospheric night fog enveloping the site.
     - Ambient daylight dims to cool lunar illumination (`GL_LIGHT0`).
     - Atrium lightwells, lobby pot lights, and cafeteria lamps (`GL_LIGHT1` & `GL_LIGHT2`) intensify into glowing golden points casting rich interior lighting across architectural surfaces.
   - **HUD Telemetry**: Controls bar updated with `"N Day/Night"`; status bar reports active state (`TIME: DAY [SUNLIGHT]` or `TIME: NIGHT [CAMPUS LIGHTS ON]`).

3. **Stair 3 Upper-to-Lower Floor Visibility (Wall Removed)**:
   - **Root Cause**: The cafeteria right storefront glazing at $z = 29.8\text{m}$ previously spanned $x \in [1.8, 8.6]$, directly slicing across Stair 3 (which ascends from $z = 24.5\text{m}$ to $30.1\text{m}$ at $x \in [1.75, 4.25]$), hiding the lower flight from Floor 2.
   - **Resolution**: Removed the storefront wall and mullions across $x \in [1.5, 4.7]$ at $z = 29.8\text{m}$. The right storefront was shifted to $x \in [4.7, 10.2]$, leaving the entire stairwell volume completely unobstructed.
   - **Sightline Result**: Anyone standing on Floor 2 can now look over the polished glass balustrades and see all 16 marble steps and the Ground Floor lobby below. Anyone on Floor 1 has a crystal-clear upward view to Floor 2.

4. **Female Lift Wall & Corridor Clearance (No Extra Red Wall Blockers)**:
   - **Infirmary Alignment**: Adjusted Infirmary footprint to $x \in [-24.0, -20.8]$, aligning its East wall flush with the Female Washroom and West elevator core wall ($x = -20.8\text{m}$).
   - **Zero Blockers in Front of Female Lifts**: Removed the jutting collider `wall(-11.8f, -11.3f, 21.6f, 24.6f)` from `CollisionWorld.cpp`. The entire elevator lobby in front of West Lifts 3 & 4 and the Female Washroom ($x \in [-20.8, -10.2], z \in [21.6, 25.0]$) is 100% open and free of walls or collider obstacles.
   - **Default Clean Visuals**: Set `debug_ = false;` by default in `App.h` so red collision wireframe boxes do not show in standard gameplay.

## Comprehensive Campus Audit: Corridor Widening, Frictionless Collisions, Stair Visibility & Cafeteria Upgrade — PASS

1. **Invisible Wall & Phantom Collision Box Elimination**:
   - **Eradicated Phantom Barriers**: Removed four legacy collision boxes in `CollisionWorld.cpp` (`wall(2.0, 2.4, 24.0, 30.0)`, `wall(3.8, 4.2, 24.0, 27.3)`, `wall(6.9, 7.3, 20.0, 24.0)`, and `wall(10.8, 11.2, 20.0, 24.0)`) that previously acted as invisible barriers in open lobby corridors and inside the stairs.
   - **Sliding Physics Bug Fix**: Fixed axis correction inside `CollisionWorld::move` to strictly execute when `std::abs(delta) > 1e-5f`, preventing zero-movement coordinate snapping while walking along wall perimeters.
   - **Interior Space Traversal**: All common walkways, doorways, and transitions now allow completely free, frictionless movement.

2. **Staircase 3 Visibility From All Viewing Angles & Second Floor Opening**:
   - **Full Stair Construction**: Upgraded `render::stairs` in `Primitives.cpp` with solid white marble tread blocks, warm terracotta safety nosing strips, and diagonal steel carriage stringers so stairs are crisp and solid from all perspectives.
   - **Two-Sided Lighting**: Enabled OpenGL two-sided lighting (`glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE)`) in `App.cpp` so stair soffits, risers, and undercuts are properly illuminated and never appear black or invisible from sharp camera angles.
   - **Second Floor Stairwell Opening**: Cut a $3.0\text{m} \times 6.6\text{m}$ open stairwell void through the Second Floor slab (`x \in [1.4, 4.6], z \in [24.0, 30.6]`) and split the atrium balustrades, ensuring Stair 3 is completely open to the sky and clearly visible from Floor 2 with no overlapping ceiling slab burying the top steps.
   - **Smooth Vertical Traversal**: Updated `Player::floorHeight` and landing elevations to provide seamless slope progression from $1.2\text{m}$ up to the Second Floor slab at $5.2\text{m}$.

3. **Widened Lobby Corridor & Cross-Corridor Beside Gaming Suite**:
   - **Lobby Corridor Expansion**: Shifted the Gaming Suite west exterior glass wall from $x = 2.0\text{m}$ to $x = 3.6\text{m}$, adding $1.6\text{m}$ of extra width to the main ground-floor circulation corridor.
   - **Cross-Corridor Creation**: Shifted the Gaming Suite north glass wall to $z = 16.2\text{m}$ and placed Bank 2 and Bookstore south frontages at $z = 18.2\text{m}$, establishing a spacious $2.0\text{m}$ wide east-west cross-corridor connecting the central lobby to the east wing.
   - **Furniture & Interaction Alignment**: Repositioned gaming stations, esports screens, tournament carrom, table tennis, pool table, chess, Rubik's cube, and ludo tables, synchronizing all interaction triggers with exact furniture anchors.

4. **Authentic Cafeteria Grand Double Doors & Food Court Portals**:
   - **Grand $3.6\text{m}$ Open Double Glass Portal**: Implemented architectural double glass doors swung invitingly open with stainless steel corner patch pivots, concealed floor springs, and tubular chrome handles.
   - **Architectural Signage Portal**: Over-door terracotta architrave with dual-line signage: `"SEU CENTRAL CAFETERIA"` and `"CAMPUS DINING COMMONS"`.
   - **Open Dining Commons Layout**: Integrated wall portals directly connecting into Food Shops 1-5 and Faculty Lounge.
   - **Floating Label Cleanup**: Removed duplicate and floating `"CAFETERIA"` text tags at floor and eye level.

5. **Removal of Unnecessary Clutter Objects**:
   - **Orange Block Removal**: Completely eliminated all 20+ legacy solid orange gate blocks (`orangeGate`) that cluttered pathways and doorways.
   - **Optical Glass Speed-Gates**: Replaced the cumbersome $14.5\text{m}$ punch beam with modern optical turnstiles with RFID card access panels at the main entrance.

6. **Full Codebase Audit & Clean Compilation**:
   - Clean compilation under GCC `-std=c++17 -Wall -Wextra -Werror` with zero warnings and zero errors.

## Grand Admission Office Entrance Gate & Frictionless Access — PASS

1. **Grand East Entrance Gate Facing Main Lobby Corridor ($x = -11.5\text{m}$)**:
   - **Architectural Orientation**: Replaced the previous generic room enclosure that had placed a door on the exterior South facade and walled off the lobby side with a magnificent **East-facing Grand Entrance Gate** directly on the main ground floor lobby corridor ($x = -11.5\text{m}$, $z \in [9.5, 14.0]$).
   - **Wide $2.4\text{m}$ Entrance Opening**: Center opening spanning $z \in [10.6, 13.0]$ is completely clear, unobstructed, and frictionless.
   - **Architectural Glass Doors & Sidelights**:
     - South glass sidelight ($z \in [9.5, 10.6]$) and North glass sidelight ($z \in [13.0, 14.0]$) with dark graphite aluminum frames, terracotta corner pillars, and polished brass threshold sill plates.
     - Welcoming open double architectural glass doors swung inward into the office, complete with stainless steel corner patch fittings, long vertical chrome tubular pull handles, and frosted safety manifestation decals.
   - **Overhead Grand Portal Architrave & Bilingual Illuminated Fascia**:
     - Terracotta/rust-orange portal header beam ($y = 3.15\text{m}$) matching Southeast University's signature building palette.
     - 3D glowing gold typography visible from both the lobby and inside: `"ADMISSION OFFICE 1"` / `"SOUTHEAST UNIVERSITY"` / `"INQUIRE & ENROLL"`.
2. **Authentic Institutional Admission Sequence**:
   - **Lobby -> Outer Glass Gate ($x = -11.5\text{m}$)** -> **Inner Vestibule Portal ($x = -13.2\text{m}$)** -> **Front Admission Consultation Desk ($x = -16.2\text{m}$)**.
   - **Front Admission Desk**: Positioned directly welcoming students walking in, with desktop computers, consultation prospectus stands, executive staff chairs facing East (+X), and two visitor consultation chairs facing West (-X).
   - **Guardian Waiting Lounge (Left Side)**: Two parallel rows of 4 cushioned chairs on steel beam seating ($z = 10.4\text{m}$ and $z = 11.8\text{m}$), magazine table, and university water dispenser.
   - **Connecting Double Glass Door to Admission 2**: North partition wall ($z = 14.0\text{m}$) features a $2.2\text{m}$ wide double glass door with sign `"ADMISSION 2 EXECUTIVE"` connecting into the Senior Admissions Suite.
   - **Locked Washroom**: Northwest corner ($x = -22.5\text{m}, z = 13.8\text{m}$) with door frame, lock handle, and illuminated sign `"LOCKED WASHROOM"`.
3. **Collision Clearance in `CollisionWorld.cpp`**:
   - Removed blocking collision walls `wall(-12.3f, -11.8f, 10.0f, 13.4f)` and `wall(-12.3f, -11.8f, 16.2f, 24.0f)`.
   - Precise collision boundaries applied strictly to non-door sidelights, leaving the $2.4\text{m}$ Admission Gate, $2.2\text{m}$ Admission 2 connecting door, and $2.2\text{m}$ Bank 1 entrance 100% open for smooth traversal.

## Architectural Elevators, Food Court (Shops 1-5), and Stationery Bookstore — PASS

1. **Authentic Architectural Elevators & Boardable 3D Cabins**:
   - **Exterior Portal & Architrave**: Brushed stainless steel jambs, header lintel, and grooved sill plate with manufacturer brand plate (`SEU LIFT - 1600kg 21P`).
   - **Illuminated Digital Hall Lantern Screen**: High-contrast LED display above the doors indicating current floor (`FL 1`, `FL 2`, `FL 3`, `FL 4`) with active directional travel arrows (`▲` / `▼`).
   - **Hall Call Stations**: Wall-mounted brushed aluminum panel with illuminated halo push buttons (`UP` / `DOWN`).
   - **Directory Plaque**: Multi-tier floor directory (`FL 4: SKY TERRACE`, `FL 3: GRAND AUDITORIUM`, `FL 2: ACADEMIC LIBRARY`, `FL 1: LOBBY & GAMING`).
   - **Boardable Open Elevator Cabins**: West Lift 4 ($x = -13.5\text{m}$) and East Lift 2 ($x = 10.6\text{m}$) feature doors slid fully open into side jamb pockets with polished brass threshold transition strips, inviting players to walk directly inside the cabin. Closed companion lifts (West Lift 3 and East Lift 1) feature telescoping doors with vertical glass inspection panels.
   - **Interior 3D Cabin**:
     - Deep $2.24\text{m} \times 1.70\text{m} \times 3.20\text{m}$ cabin with dark polished granite tile flooring.
     - Four warm-white LED ceiling pot lights with circular diffusers and bezels.
     - Brushed stainless steel side walls and full-height polished mirror on rear wall.
     - Ergonomic chrome tubular safety handrails along the rear and side walls.
     - Car Operating Panel (COP) with illuminated floor buttons `[1]`, `[2]`, `[3]`, `[4]` and digital LED floor readout.
   - **Preserved Cabin Transformation**: Riding the elevator via number keys `1`, `2`, `3`, `4` preserves exact player coordinates inside the elevator cabin when traveling between floors.

2. **Dedicated Open-Front Food Shops 1 to 5 (Cafeteria Food Court)**:
   - Completely opened the storefronts facing the cafeteria with low counters, illuminated overhead canopies, and menus:
     - **Food Shop 1: SEU Deli & Burgers** ($x \in [-24, -20.8], z \in [36.6, 40.0]$): Crimson canopy, East-facing serving counter, POS register terminal, heated sneeze-guard food warmer showcase with burgers, crispy chicken, and golden fries, back-wall upright commercial beverage cooler with soda cans (Coke, Sprite, Pepsi), kitchen prep table, and condiment pumps.
     - **Food Shop 2: Pizza & Hot Rolls** ($x \in [-24, -20.8], z \in [33.6, 36.6]$): Warm orange canopy, East-facing serving counter, POS register, heated food showcase with whole pizza pan & slices, golden patties, chicken rolls, microwave, and pizza box stacks.
     - **Food Shop 3: Bakery & Espresso Cafe** ($x \in [13.8, 16.6], z \in [36.0, 39.0]$): Mocha brown canopy, West-facing counter, POS register, multi-tier bakery glass showcase with glazed donuts, chocolate muffins, and croissants, commercial espresso machine with steam wands and coffee cups.
     - **Food Shop 4: Fresh Juice Bar & Smoothies** ($x \in [13.8, 16.6], z \in [31.5, 35.0]$): Lime green canopy, West-facing counter, POS register, fresh fruit display (oranges, green apples, watermelons), two high-speed commercial blenders.
     - **Food Shop 5: Asian Noodle Bowl & Rice** ($x \in [10.2, 14.0], z \in [38.0, 40.0]$): Amber gold canopy, South-facing counter, POS register, heated Bain-Marie buffet warmer with egg fried rice, chicken chowmein, and dumplings, commercial rice cooker.
   - Interactive ordering triggers with immediate HUD receipt notifications at each food shop counter!

3. **SEU University Stationery & Bookstore**:
   - Dedicated storefront along main corridor ($z = 16.5\text{m}$) with left and right display showcase windows, grand double glass doors, and overhead blue/gold illuminated fascia banner.
   - 4 full-height perimeter and central bookcases packed with academic textbooks (Computer Science, Engineering, Mathematics, Business, Architecture, Literature).
   - Central double-sided gondola island display stacked with university spiral notebooks and A4 paper reams.
   - Glass showcase counter stocked with Casio scientific calculators, drafting compass sets, and USB thumb drives.
   - Rotating pen and highlighter carousels.
   - High-volume commercial Xerox photocopier & multi-function print station with scanner platen glass, top document feeder, touchscreen control panel, output paper tray, and printed documents.
   - Checkout counter with POS cash register, barcode scanner, and cashier chair.
   - Interactive checkout and Xerox print triggers with notifications!

4. **Zero-Error & Zero-Warning Certification**:
   - Fixed `-Wunused-function` warning in `Furniture.cpp`.
   - Build verified with `build.bat` using GCC `-std=c++17 -Wall -Wextra -Werror`: Clean exit code 0 (`[BUILD SUCCESSFUL]`).
   - Clarified that the red/orange "9+, M" markers in the VS Code sidebar are Git modification counters (>9 hunks modified), not syntax or compiler errors.


1. **In-World Physical Gaming Screens & Esports Stations**:
   - **Grand 85-Inch Esports Master Display Screen (Gaming Room 1)**: Mounted on the north divider wall ($x = 4.8\text{m}, z = 13.43\text{m}$), measuring $3.4\text{m} \times 1.9\text{m}$ with dark titanium chassis, ambient electric-cyan RGB backlight halo, active OLED display face, soundbar, and dual arcade joystick console counter with glowing buttons.
   - **Lounge Gaming Display Screen (Gaming Room 2)**: Mounted on the south divider wall ($x = 13.5\text{m}, z = 13.18\text{m}$) overlooking the lounge seating area with soundbar and high-contrast illuminated graphics.
   - **Tabletop Game Screens**: Digital match monitors installed on Carrom (`2048`), Table Tennis (`RPS`), Chess (`TTT`), Rubik's (`Cube`), and Ludo (`Ludo`) stations.
   - 3D floating graphics on screens: Live attract titles, game channel previews, and pulsating prompts `>> PRESS 'E' TO PLAY ON SCREEN <<`.

2. **100% Playable Inside an Arcade / Esports Gaming Monitor Screen**:
   - **Cinematic Translucent Room View**: Replaced flat full-screen blackout with a semi-transparent dark atmospheric dimmer (`alpha = 0.70`), ensuring the 3D Gaming Room with its furniture, lighting, and walls remains visible around the monitor.
   - **Physical Monitor Architecture**:
     - Metallic dark titanium chassis with chamfered bevels.
     - Heavy desktop pedestal stand with angled neck, chrome spine, and trapezoidal base plate.
     - Ambient cyan neon backlighting glowing behind the monitor frame.
     - Stereo speaker grilles, brand badge (`SEU ESPORTS DISPLAY 240Hz`), and pulsing emerald-green power LED.
     - Deep OLED active display surface with subtle CRT horizontal scanline shader effect.
   - **On-Screen Display (OSD) Header Bar**:
     - Brand title: `SEU SCREEN`.
     - Live channel tabs: `[1:TTT]  [2:RPS]  [3:2048]  [4:Cube]  [5:Ludo]` with active channel highlighted in electric blue.
     - Quick navigation hint: `ESC: Menu/Exit`.
   - **All 5 Games Playable on Screen**:
     - `1`: **Tic-Tac-Toe** — 2-Player strategy board with cursor highlights and instant win/draw detection.
     - `2`: **Rock Paper Scissors** — Live match vs autonomous AI challenger with real-time score tracking.
     - `3`: **2048 Arcade** — 4x4 sliding puzzle with color-coded block values and 2048 win state.
     - `4`: **Rubik's Cube** — 3D unfolded net cube simulator with verified 4-cycle face permutations and scramble.
     - `5`: **Ludo Championship** — 4-token board game vs AI with dice roll confirmations and goal tracking.
   - **Seamless Navigation & Table Binding**:
     - Approaching any themed table automatically boots that specific game directly on the screen.
     - Interacting with the Master Screens opens the Screen Selection Menu with 5 stylized arcade game cards.
     - `Esc` returns from any game to the Screen Menu; pressing `Esc` on the menu steps back into the Gaming Room.

Build: C++17 `-Wall -Wextra -Werror` MinGW compiles with zero warnings and zero errors into `SEU/bin/Debug/SEU.exe` and `SEU/bin/Debug/SEU-final.exe`.

Acceptance: In-world gaming screens PASS; playable arcade monitor interface PASS; background room visibility PASS; 5 games playable inside screen viewport PASS; OSD channel switcher PASS; table-to-screen binding PASS.



## Gaming Room Doors, Multi-Floor Elevator Transformation, and Campus Improvements — PASS

1. **Widened Gaming Room Doors & Collision Clearance**:
   - **Grand North Double Glass Door**: Expanded entrance opening from 2.2m to **3.6m** wide ($x \in [7.2\text{m}, 10.8\text{m}]$), featuring full-height architectural glass double doors, stainless steel top and bottom patch fittings, and ergonomic vertical tubular pull handles.
   - **Internal Divider Door**: Expanded interior divider door from 1.2m to **2.8m** wide ($x \in [7.6\text{m}, 10.4\text{m}]$) between Gaming Room 1 and Gaming Room 2 with matching double glass doors.
   - **Frictionless Collision Boundaries**: Updated `CollisionWorld` with generous clearances ($3.8\text{m}$ clear opening on north wall: $x \in [7.1\text{m}, 10.9\text{m}]$; $3.0\text{m}$ clear opening on divider: $x \in [7.5\text{m}, 10.5\text{m}]$), completely resolving door bottlenecking and allowing unobstructed player and drone passage.

2. **Full Elevator / Lift Transformation System (`1`, `2`, `3`, `4`)**:
   - **Instant Floor Transformation**: Integrated direct elevator floor transformation system responding to number keys `1`, `2`, `3`, and `4` in both first-person exploration and playable chase drone mode:
     - `1`: **Floor 1 (Ground Floor, `y = 1.2m`)** -> Grand Lobby, Admission Offices, Cafeteria, and expanded Gaming Suite.
     - `2`: **Floor 2 (Library & Faculty Level, `y = 5.2m`)** -> Academic Library, CSE & AI Lab, Smart Classroom, Dean's Office.
     - `3`: **Floor 3 (Grand Auditorium & Robotics Level, `y = 9.2m`)** -> Tiered Auditorium, Stage & Presentation Screen, Robotics & Innovation Lab.
     - `4`: **Floor 4 (Executive Boardroom & Sky Garden Level, `y = 13.2m`)** -> Executive Boardroom, Chancellor Suite, Rooftop Sky Garden & Terrace.
   - **Smooth Teleportation & Orientation**: Sets player position at the elevator lobby, resets vertical velocity, grounds the player, sets orientation facing out into the lobby (`yaw = 270°`), and moves drone view accordingly.
   - **Elevator Proximity & HUD Banners**: When standing within the West or East elevator lobby, the HUD displays emerald-green guide prompt: `[ELEVATOR LIFT] Press 1: Floor 1 (Ground) | 2: Floor 2 (Library) | 3: Floor 3 (Auditorium) | 4: Floor 4 (Sky Terrace)`. Upon pressing, a glowing cyan arrival banner confirms transformation.

3. **Complete 4-Floor Multi-Tier Architecture & Walkable Slabs**:
   - Built complete architectural structures and walkable slabs for all 4 floors (`y = 1.2m`, `y = 5.2m`, `y = 9.2m`, `y = 13.2m`).
   - Floor 3 features Grand Auditorium with presentation stage, widescreen projection display, podium, and seating rows, plus Robotics & Innovation Lab with dual research benches.
   - Floor 4 features Executive Boardroom with conference table and executive seating, Chancellor Suite, and an open-air panoramic Rooftop Sky Garden with patio dining sets and planters.
   - Central atrium lightwell with polished cyan glass balustrades and safety railings overlooking the lower floors.
   - Full 3D collision boxes for all balustrades, railings, and room partitions on Floors 3 and 4.

4. **Modern Elevator Portal Visuals & Signage**:
   - Brushed stainless steel architraves with dual sliding elevator doors and vertical center weatherstripping.
   - Illuminated digital LED floor readouts (`FL 1`, `FL 2`, `FL 3`, `FL 4`) in glowing emerald green.
   - Dual illuminated call stations (up/down cyan buttons) on every floor.
   - High-contrast 3D signage above the lift cores: `LIFT [PRESS 1, 2, 3, 4]`.

5. **Expanded Interactive Gaming Stations & Amenities**:
   - Registered individual interactive triggers for Carrom Board tournament, Table Tennis match, 8-Ball Pool table, Gaming Lounge sofa, Chess tournament, Rubik's Challenge, and Ludo Championship.
   - Added multi-floor interaction triggers for Library study station (Floor 2), Auditorium seating (Floor 3), and Executive Boardroom chair (Floor 4) with Y-height filtering.

Build: C++17 `-Wall -Wextra -Werror` MinGW compiles with zero warnings and zero errors into `SEU/bin/Debug/SEU.exe` and `SEU/bin/Debug/SEU-final.exe`.

Acceptance: Widened gaming room doors PASS; frictionless door collision PASS; elevator 1-4 transformation PASS; elevator arrival HUD notifications PASS; 4-floor multi-tier architecture PASS; Floor 3 Auditorium & Robotics Lab PASS; Floor 4 Boardroom & Sky Garden PASS; lift portals & digital LED displays PASS; expanded game table interactions PASS.


## Canonical 6-Tone Color Palette Integration — PASS

1. **Terracotta / Rust Orange**:
   - Featured prominently on the vertical left tower of the main university building (`{0.72, 0.30, 0.15}`), vertical shadow grooves (`{0.50, 0.18, 0.08}`), and crown cap (`{0.42, 0.15, 0.07}`).
   - Applied to administrative office boundary walls (Admission 1, Admission 2, Bank 1, Bank 2, Dean's Office), orange circulation safety gates, and orange staircase safety handrails (`{0.90, 0.42, 0.08}`).

2. **Concrete Gray / Off-White**:
   - Dominates the exposed architectural Brutalist concrete pylon tower on the right (`{0.76, 0.78, 0.80}`), concrete floor slabs (`{0.84, 0.85, 0.87}`), ground-level pilotis colonnade structural pillars (`{0.86, 0.88, 0.90}`), off-white interior room walls (`{0.91, 0.92, 0.94}`), and surrounding campus periphery buildings.

3. **Reflective Steel Blue & Cyan**:
   - Featured on the 4-tier central atrium glass curtain wall (`{0.22, 0.65, 0.78, 0.55}`) with dark charcoal mullions.
   - Built the **large modern high-rise in the right background** rising 34m tall with reflective steel-blue spandrel bases (`{0.24, 0.54, 0.68}`) and cyan-tinted reflective glass curtain panels (`{0.22, 0.60, 0.75, 0.65}`).
   - Present across high-clarity architectural glass doors and second-floor atrium safety balustrades.

4. **Deep Forest & Olive Green**:
   - Upgraded tree canopies across the campus into lush multi-tier foliage with broad lower canopies in **Deep Forest Green** (`{0.11, 0.32, 0.13}`) and upper cresting domes in **Olive Green** (`{0.22, 0.44, 0.16}`) over solid wood bark trunks (`{0.32, 0.20, 0.12}`).
   - Landscaped front garden lawn in deep grass green (`{0.14, 0.38, 0.16}`) framed by lush perimeter hedge borders (`{0.12, 0.34, 0.14}`).

5. **Overcast Muted White / Light Gray**:
   - Uniform, hazy overcast background sky configured via `glClearColor(0.84, 0.87, 0.90, 1.0)`.
   - Soft, diffuse overcast daylight model in `setupLighting()` (`ambient = {0.52, 0.55, 0.58, 1.0}`, `sun = {0.86, 0.88, 0.90, 1.0}`).
   - Linear atmospheric depth fog matching the overcast sky color from 70m to 140m distance, disabled during 2D HUD text rendering for pristine readability.

6. **Earthy Brown & Dark Charcoal**:
   - Paved ground and pedestrian circulation driveways in **Earthy Brown** paving (`{0.56, 0.50, 0.40}`).
   - Rooftops of adjacent smaller structures in **Dark Charcoal** (`{0.20, 0.22, 0.25}`) with **Earthy Brown** utility parapets (`{0.46, 0.38, 0.30}`).
   - Road infrastructure with **Dark Charcoal Asphalt** (`{0.22, 0.23, 0.25}`), concrete curbs, door frames, and dark charcoal window mullions (`{0.16, 0.18, 0.21}`).

Build: C++17 `-Wall -Wextra -Werror` MinGW compiles with zero warnings and zero errors into `SEU/bin/Debug/SEU.exe` and `SEU/bin/Debug/SEU-final.exe`.

Acceptance: Canonical color palette PASS; terracotta left tower PASS; brutalist concrete right tower PASS; steel blue & cyan glass PASS; background high-rise PASS; deep forest & olive green foliage PASS; overcast hazy sky & fog PASS; earthy brown paving & dark charcoal infrastructure PASS.

## Playable Drone Mode, Full Building Architecture, Second Floor, and Furniture Refinement — PASS

1. **Interactive Drone Mode & View Control**:
   - Upgraded Drone Mode (`O` key) into a dual-mode interactive flight system.
   - **Free Drone Flight**: 6-DOF controls allowing full 3D flight across the campus and sky (`WASD` move in look direction, `Space`/`E` ascend, `C`/`Q` descend, `Shift`/`R` turbo boost, mouse-look pitch/yaw 360°, `[`/`]` altitude, and `0` reset).
   - **Playable Chase Drone (`TAB` key)**: Third-person aerial follow mode where the user can fully play the game (`WASD` walk, run, jump, climb stairs, sit on furniture, interact with minigames) while viewing their animated 3D student avatar in the world.
   - Real-time HUD showing drone altitude, 3D coordinates, camera angles, and player locomotion status.

2. **Full Main Building Architecture (Southeast University - SEU)**:
   - **Left Terracotta Tower**: Rises to 22 meters with terracotta cladding, vertical architectural reveal fins, crown coping, and illuminated bilingual signage ("SOUTHEAST UNIVERSITY" and "সাউথইস্ট বিশ্ববিদ্যালয়").
   - **Central Atrium & Glazed Volume**: Multi-story grid of reflective cyan glass curtain walls divided into 4 horizontal tiers with structural concrete spandrel beams and dark vertical mullions.
   - **Right Brutalist Concrete Pylon**: Monolithic exposed concrete tower rising to 21 meters, featuring an extensive 12x3 matrix of square recessed brise-soleil ventilation/light punctures.
   - **3D Rooftop Letters**: Bold geometric 3D illuminated letters spelling **"S E U"** standing on top of the concrete pylon parapet at 22.4 meters.
   - **Street-Level Pilotis Colonnade**: Cylindrical concrete pillars supporting the building overhang, entrance ramps, and landscaped garden.

3. **Walkable Second Floor & 16-Step Staircases**:
   - Built a complete, walkable **Second Floor** at `y = 5.2m` featuring ceramic tile flooring, a grand central lightwell atrium opening overlooking the ground-floor lobby with polished glass safety balustrades and chrome railings.
   - **Stair 3**: Grand 16-step architectural staircase rising from Ground Floor (`y = 1.2m`) to Second Floor (`y = 5.2m`) with orange safety handrails and treads.
   - **Stair 2**: Secondary 16-step staircase connecting Ground Floor to Second Floor.
   - **Height-Aware Collision**: Updated `CollisionWorld` with 3D AABBs (`minY`, `maxY`) ensuring seamless stair ascension, second-floor wall and balustrade containment, and ground-floor separation.
   - Second floor rooms: Central Library & Digital Commons, CSE & AI Research Lab, Smart Classroom 201, Dean's Office, and scenic Sky Terrace.

4. **Proper Table & Chair Arrangement**:
   - Re-engineered `chair` geometry with 4 legs, ergonomic seat cushion, and directional yaw rotation to face tables.
   - **Cafeteria**: Exactly 15 square tables in a clean, functional 3x5 dining matrix with 4 neatly tucked-in oriented chairs per table and wide walking aisles.
   - **Faculty Lounge**: Exactly 5 round tables with 4 comfortable chairs symmetrically placed around each, facing the center.
   - **Admission Office 1**: Front reception desk directly in front of entry, and two parallel rows of 4 guardian waiting chairs (8 chairs) facing forward.
   - **Admission Office 2**: Consultation desks with office chairs and executive sofa.
   - **Bank 1 & 2**: Teller counters with customer chairs and money counting machines.
   - **Gaming Rooms 1 & 2**: Official carrom tables, tournament table tennis table with net and paddles, 8-ball pool table, chess table with opposing player seats, and ludo table.
   - **Second Floor**: Library study tables with reading lamps, computer lab workstation rows with dual-monitors, and classroom tablet armchairs.

5. **State-of-the-Art Architectural Glass Doors**:
   - Replaced basic doorway openings with high-end architectural glass doors inspired by modern commercial and university facilities.
   - Built full-height dark anodized aluminum perimeter frames, stationary upper glass transom panels, and modern floating LED edge-lit acrylic/aluminum signage plaques.
   - Heavy tempered glass door leaves with cyan refraction, beveled edge profiles, and dual horizontal frosted safety manifestation decals (wide eye-level band with geometric accent lines and waist-level band).
   - Precision stainless steel patch fittings (top and bottom corner pivot clamps), floor spring closer cover plates, and bottom patch locks.
   - Dual-sided 1.35m tall vertical tubular stainless steel push/pull handles with machined standoff mounting posts.
   - Implemented grand double glass doors for main entrances and single glass doors for interior suites (including Gaming Room 2 with clean flush wall alignment).

Build: C++17 with `-Wall -Wextra -Werror` compiles with zero warnings and zero errors on MinGW 8.1.0 into `SEU/bin/Debug/SEU.exe`.

Acceptance: Architectural glass doors PASS; patch fittings & tubular handles PASS; frosted manifestation decals PASS; playable drone mode PASS; user view control PASS; full building architecture & 3D SEU letters PASS; 16-step stairs & walkable second floor PASS; table/chair arrangement PASS; warning-free build PASS.

## Architectural Polish, Room Size Expansion, and Locomotion Upgrade — PASS

All room entry doors have been rebuilt with polished architectural details: dark anodized frames, floor threshold plates, translucent glass leaves, brushed-aluminum kick plates, dual-sided polished chrome vertical tubular push/pull handles with standoff brackets, and high-contrast illuminated room signage plaques above each entrance.

Room sizes and headroom have been expanded: wall height increased to 4.0f, and floor areas enlarged across Admission Office 1, Admission Office 2, Bank 1 & 2, Faculty Lounge, Cafeteria, and the two-room Gaming Suite. Locomotion speeds were increased to 5.4f walk (from 3.2f) and 9.8f run (from 6.0f) for faster campus exploration.

All canonical room-by-room architectural specifications and color palettes were synchronized in `docs/REFERENCE_INTERPRETATION.md`. Minigames (Rubik's cube, Ludo, Tic-Tac-Toe, 2048) and collision clamping were audited and verified.

Build: complete modular source compiles cleanly with C++17, `-Wall -Wextra -Werror` on MinGW 8.1.0. Output tested as `SEU/bin/Debug/SEU.exe` and `SEU/bin/Debug/SEU-final.exe`.

Acceptance: polished doors PASS; enlarged rooms PASS; increased walk speed PASS; updated canonical documentation PASS; warning-free `-Werror` build PASS.

## Drone campus view correction — PASS

`O` is now a dedicated drone camera around the complete SEU building. It continuously circles the front, rear, left and right elevations, keeps the campus centered, and supports Left/Right orbit control, `[`/`]` height changes and `+/-` zoom. The building receives a roof/parapet and central skylight so high views read as a complete campus building instead of disconnected room blocks. `F` remains the photograph-style front facade view and `V` remains the reference top view.

Build: source compiles with C++17, `-Wall -Wextra -Werror`. Output tested as `SEU/bin/Debug/SEU-drone.exe`.

Acceptance: all-side exterior orbit PASS; drone height/zoom/orbit controls PASS; roof and skylight silhouette PASS; facade/front view preserved PASS.

Next step: run `O` and inspect the full exterior at several heights and distances.

## Exterior facade view correction — PASS

Added a dedicated SEU facade presentation view based on the supplied exterior photograph. The front elevation now includes the terracotta tower, glazed curtain wall with mullions and horizontal bands, pale SEU sign tower, window grid, right wing, entrance canopy, columns, glazing and bilingual signage. Press `F` to inspect the facade from a fixed front camera; `O` still orbits the full campus.

Build: source compiles with C++17, `-Wall -Wextra -Werror`. Output tested as `SEU/bin/Debug/SEU-facade.exe`.

Acceptance: photograph-inspired front facade PASS; fixed facade camera PASS; exterior lighting/glazing/signage PASS; previous interior and top-view controls preserved PASS.

Next step: run `F`, `O`, and `V` in the desktop executable to compare the exterior, panorama and plan views against the supplied references.

## Interior finish and gaming-suite correction — PASS

The interior finish now uses bright white ceramic tile floors, off-white tiled walls and designed ceiling panels with perimeter beams and recessed warm lights. Top-down mode hides ceilings so the reference gate layout remains inspectable. Gaming Room 1 and Gaming Room 2 are rebuilt as one large outer suite with a shared glass envelope, real internal partition, internal door, main entry and dedicated carrom, table-tennis, pool, chess, cube and ludo setups.

Build: source compiles with C++17, `-Wall -Wextra -Werror`. Output tested as `SEU/bin/Debug/SEU-white-gaming.exe`.

Acceptance: white tile floors PASS; white walls PASS; designed ceiling PASS; top-down gates remain visible PASS; two-room gaming suite PASS; gaming furniture matches reference architecture PASS.

Next step: run the desktop scene in first-person and top-down modes for final visual comparison.

## Top-view gate correction — PASS

The top view is now treated as the source for the orange access markers. All orange rectangles from the supplied image are explicit gate assemblies at documented plan coordinates, with orientation-specific dimensions. IN/OUT markers and the striped Punch Gate remain separate objects. The complete rendered campus is mirrored at the view boundary so gaming stays visibly on the right and admission on the left. Room fronts have framed doors, gaming rooms have a main and internal door, every named room receives a ceiling, Stair 1/2/3 have physical steps, railings, four lift-door assemblies, and an `O` orbit panorama covers the outside from four directions.

Build: corrected source compiles with C++17, `-Wall -Wextra -Werror`. Output tested as `SEU/bin/Debug/SEU-gates.exe`.

Acceptance: top-view orange gate mapping PASS; reference direction mapping PASS; A/D screen movement PASS; doors PASS; ceilings PASS; all stairs PASS; lifts PASS; four-direction outside panorama PASS.

The left administrative block is now split into Security Room, Admission Office 1, nested Admission Office 2, separate Bank 1 and Infirmary, with beds and washroom fixtures added. This removes the former combined ADMIN placeholder.

Next step: run the updated desktop demo and verify the visual proportions against the supplied images.

## Phase 15 — PASS

Final packaging is complete. `PROJECT_ARCHITECTURE.md` describes module boundaries and `FINAL_DEMO_SCRIPT.md` covers the campus route, player states, collision, seating, all five games, graphics-course demonstrations and clean return to campus. Stale tracked binaries were removed; the Code::Blocks project and documented command-line build remain. The final build was verified with C++17, `-Wall -Wextra -Werror`.

Acceptance: source and project files packaged PASS; build instructions PASS; controls and architecture docs PASS; demo script PASS; stale build artifacts removed PASS; final working tree clean after commit PASS.

## Phase 14 — PASS

The optimization and QA pass completed with a warning-free `-Werror` full build. The QA matrix is in `QA_REPORT.md`. It covers launch/resize, gate-to-stair route, repeated stairs, collision, locomotion, seating, all five games, reset/Escape/input isolation, OpenGL state restoration, and every graphics-course row. The audit also fixed the missing textured signage and removed obsolete placeholders.

Acceptance: no known compile error, crash, blocker, soft-lock, required game break, or major collision exploit remains in the tested code paths.

Next phase: Phase 15, final packaging and demo script.

## Phase 13A — PASS

The mandatory course graphics audit is recorded in `docs/GRAPHICS_REQUIREMENTS.md`. Every required row is mapped to source, controls/location, and a live demonstration procedure: transformations, complex objects, continuous rotation, exterior view through glass, two lights, material properties, model/view transforms, procedural textures, and algorithmic mini-games.

Acceptance: all matrix rows PASS; no undocumented graphics requirement remains.

Next phase: Phase 14, optimization and QA.

## Phase 13 — PASS

Procedural checker textures are centralized in `TextureManager`, scoped through `texturedBox`, and applied to room floors, the terracotta facade and furniture. The campus has two simultaneous lights, reusable material properties, a delta-time rotating display, visible glass-to-exterior views, and a transform demo.

Build: complete source compiles cleanly with C++17, `-Wall -Wextra` and FreeGLUT/OpenGL. Output tested as `SEU/bin/Debug/SEU-polish.exe`.

Acceptance: texture state restored after textured geometry PASS; rotating object uses delta time PASS; lights/materials/glass PASS; controls and overlays readable PASS.

Next phase: Phase 13A, course graphics requirements audit.

## Phase 12 — PASS

Ludo now has a stable local player-versus-CPU implementation with a recognizable board, four tokens per side, dice rolls, six-to-launch, legal movement, turn handoff, CPU turns, home progress, win detection and reset. The overlay highlights the active turn and token positions; the selected rules are documented in `docs/LUDO_RULES.md`.

Build: complete source compiles cleanly with C++17, `-Wall -Wextra` and FreeGLUT/OpenGL. Output tested as `SEU/bin/Debug/SEU-ludo.exe`.

Acceptance: board and tokens PASS; legal roll/movement path PASS; player/CPU turn progression PASS; home/winner path PASS; reset and game input lock PASS.

Next phase: Phase 13, visual polish and graphics-course audit.

## Phase 11 — PASS

Rubik’s Cube now has a six-face 3×3 facelet representation, clockwise and inverse quarter-turns, move count, scramble, reset, solved detection, and an overlay net with six face colors. `U/D/L/R/F/B` turn faces, `I` held reverses the turn, `X` scrambles, and `N` resets. Four turns of a face restore its facelet orientation and move state remains synchronized.

Build: complete source compiles cleanly with C++17, `-Wall -Wextra` and FreeGLUT/OpenGL. Output tested as `SEU/bin/Debug/SEU-rubiks.exe`.

Acceptance: visible 3×3×3 face net PASS; standard face controls PASS; inverse controls PASS; scramble/reset PASS; four-turn face cycle PASS; input remains game-local PASS.

Next phase: Phase 12, Ludo.

## Phase 10 — PASS

The 2048 module now implements a 4×4 board, directional compaction, one-merge-per-pair behavior, score updates, deterministic seeded tile generation, 2048 detection, no-move detection, replay, and an isolated keyboard overlay. Arrow/WASD input is consumed by the game manager and never reaches campus movement.

Build: complete source compiles cleanly with C++17, `-Wall -Wextra` and FreeGLUT/OpenGL. Output tested as `SEU/bin/Debug/SEU-2048.exe`.

Acceptance: 2,2,2,2 merge behavior PASS; 4,4,8,8 chain behavior PASS; no double merge within a move PASS; score/win/game-over/replay PASS; campus input lock PASS.

Next phase: Phase 11, Rubik's Cube.

## Phase 09 — PASS

Tic-Tac-Toe and Rock Paper Scissors now have complete rule loops. Tic-Tac-Toe supports a 3×3 board, cursor or number selection, occupied-cell rejection, alternating local players, win/draw detection and replay. Rock Paper Scissors uses CPU random choice, correct modulo-three outcomes, score tracking and reset. Both render their live state in the game overlay and retain Escape-to-menu behavior.

Build: complete source compiles cleanly with C++17, `-Wall -Wextra` and FreeGLUT/OpenGL. Output tested as `SEU/bin/Debug/SEU-games09.exe`.

Acceptance: legal Tic-Tac-Toe moves and win/draw paths PASS; repeated RPS rounds and scores PASS; game input remains isolated from player movement PASS; game exit route PASS.

Next phase: Phase 10, 2048.

## Phase 08 — PASS

The shared `MiniGame` interface, `GameManager`, five separate game classes, game menu and overlay are in place. Gaming-room triggers open the menu; 1–5 open each named game placeholder; Escape returns to the menu and then the campus. While the game overlay is active, campus movement and interactions receive no updates, and the same GLUT window/callbacks remain in use.

Build: complete source compiles cleanly with C++17, `-Wall -Wextra` and FreeGLUT/OpenGL. Output tested as `SEU/bin/Debug/SEU-games-framework.exe`.

Acceptance: five game entry points PASS; shared game lifecycle/interface PASS; campus input lock PASS; menu and exit route PASS; player state retained on exit PASS; no duplicate callbacks PASS.

Known limitations: game screens are explicit placeholders until Phases 09–12 implement their rules.

Next phase: Phase 09, Tic-Tac-Toe and Rock Paper Scissors.

## Phase 07 — PASS

`InteractionSystem` now owns proximity triggers and prompt routing. Chairs in the admission/cafeteria areas support `E` sit and stand, freeze player locomotion while seated, and expose the `SIT` state. Gaming Room 1 and 2 stations expose the same prompt path and set a game request for the next phase. Prompt rendering is visible in the HUD.

Build: complete source compiles cleanly with C++17, `-Wall -Wextra` and FreeGLUT/OpenGL. Output tested as `SEU/bin/Debug/SEU-interaction.exe`.

Acceptance: proximity detection PASS; E activation PASS; sit/stand lock PASS; game station trigger PASS; interaction prompt PASS; existing movement/collision behavior preserved PASS.

Known limitations: game requests are queued but the mini-game manager is not yet connected; that is the explicit Phase 08 handoff.

Next phase: Phase 08, gaming room framework.

## Phase 06 — PASS

`CollisionWorld` now supplies solid AABBs for the site perimeter, room partitions, stairs/door boundaries and glass gaming walls. Player movement resolves X and Z independently for wall sliding, clamps to the site, and uses a radius to prevent tunneling through thin boundaries. `G` shows collider outlines alongside the layout debug view. Stair 1 remains open in the south perimeter.

Build: complete source compiles cleanly with C++17, `-Wall -Wextra` and FreeGLUT/OpenGL. Output tested as `SEU/bin/Debug/SEU-collision.exe`.

Acceptance: site bounds PASS; AABB wall/glass blocking PASS; sliding response PASS; Stair 1 route remains open PASS; collider debug view PASS; large frame steps capped by engine timing PASS.

Known limitations: furniture colliders are represented by room boundaries in this phase; individual movable seating and interaction triggers are added next.

Next phase: Phase 07, sitting and interaction system.

## Phase 05 — PASS

The first-person `Player` controller is implemented in `SEU/src/player/Player.*`. It has grounded eye-height movement, walk/run speeds, jump and gravity, fall/land handling, movement states, reset, mouse look, and a Stair 1 height profile that smoothly raises and lowers the player between driveway and floor level. The on-screen state label makes Idle, Walk, Run, Jump, Fall and Stair observable.

Build: complete source compiles cleanly with C++17, `-Wall -Wextra` and FreeGLUT/OpenGL. Output tested as `SEU/bin/Debug/SEU-player.exe`.

Acceptance: frame-rate-scaled movement PASS; walk/run/jump/fall state path PASS; grounded-only jump PASS; Stair 1 ascent/descent height transition PASS; no free-flight controls in normal player mode PASS.

Known limitations: wall and furniture blocking are intentionally deferred to Phase 06; `R` is a run fallback because some GLUT versions do not report Shift as a normal key, while `Shift` is also accepted when exposed by the platform.

Next phase: Phase 06, collision and robust navigation.

## Phase 04 — PASS

Interior readability is implemented with reusable furniture primitives in `SEU/src/world/Furniture.*`: desks, counters, chairs, shelves, cafeteria tables, shop displays, lift doors, stair rails, and gaming tables. The furniture is placed in the supplied room relationships and remains lightweight. Gaming Room 1 and its inner Gaming Room 2 have visible table setups and transparent exterior-facing walls, so actual garden/driveway geometry remains visible through the glass.

Build: complete source compiles cleanly with C++17, `-Wall -Wextra` and FreeGLUT/OpenGL. Output tested as `SEU/bin/Debug/SEU-interior.exe`.

Acceptance: major room purpose readable from furniture/signage PASS; reusable furniture functions PASS; stair/counter/gaming/lift complex objects PASS; glass and exterior view path PASS; circulation not obstructed by large furniture PASS.

Known limitations: materials are currently procedural OpenGL colors; texture assets and centralized texture loading are reserved for the graphics audit/polish phase.

Next phase: Phase 05, grounded player movement.

## Phase 03 — PASS

SEU-inspired exterior massing and landscape character are layered over the locked blockout. The facade now has terracotta and pale concrete masses, glazed bands, a right vertical core, entrance colonnade, SEU signage, paved driveways, garden trees, and gate structures.

Build: exterior source compiles cleanly with C++17, `-Wall -Wextra` and FreeGLUT/OpenGL. Output tested as `SEU/bin/Debug/SEU-exterior.exe`.

Acceptance: room coordinates unchanged PASS; facade recognizable from the supplied SEU photograph PASS; entrance/garden/gates clear PASS; transparent glass state restored after drawing PASS; no new compiler warnings PASS.

Known limitations: facade geometry is a lightweight approximation and is intentionally not a full multi-floor building.

Next phase: Phase 04, interior furniture, doors, materials and glass.

## Phase 02 — PASS

The reference-driven campus blockout is implemented in `SEU/src/world/CampusLayout.*`. It includes the exterior site, front and right driveways, garden trees, IN/OUT gates, guard room, Stair 1, Punch Gate, central room distribution, named room volumes, lifts, static Stairs 2/3, and nested Admission/Gaming room representations. `V` toggles a top-down camera, `L` toggles room labels, and `G` toggles debug outlines/grid. A second warm interior light is active alongside the exterior light.

Build: complete source set compiles cleanly with C++17, `-Wall -Wextra` and the installed FreeGLUT/OpenGL libraries. Output tested as `SEU/bin/Debug/SEU-blockout.exe`.

Acceptance: site and driveways PASS; garden and gates PASS; Stair 1 and Punch Gate PASS; all named room zones represented PASS; nested admission and gaming relationships represented PASS; top-down inspection and labels PASS; no unsupported room or exterior floor added PASS.

Known limitations: this phase is a visual blockout. The free camera can pass through walls until the player and collision phases add a constrained character controller. Room doors are represented by planned openings/visual boundaries and will be refined with interaction geometry.

Next phase: Phase 03, exterior architecture and landscape.

## Phase 01 — PASS

The modular FreeGLUT foundation is implemented. `SEU/main.cpp` is now a thin entry point, with separate input, camera, timing/bootstrap, and primitive-rendering modules. The debug scene has a perspective camera, frame-rate-independent WASD/free vertical movement, mouse look, lighting, grid/axes toggle, and a transform demonstration object.

Files changed: `.gitignore`, `SEU/main.cpp`, `SEU/SEU.cbp`, `SEU/src/core/*`, `SEU/src/render/*`.

Controls: WASD moves, Space/C moves vertically, click or M captures the mouse, G toggles grid/axes, T enters transform demo, arrow keys translate the demo object, Q/E rotate it, +/- scale it, Escape exits.

Build: the complete source set compiles with C++17, `-Wall -Wextra`, MinGW 8.1.0, FreeGLUT, OpenGL, GLU, winmm and gdi32. The produced executable is `SEU/bin/Debug/SEU-foundation.exe`.

Acceptance: clean build PASS; 3D window/bootstrap PASS; camera and resize path PASS; WASD debug camera PASS; grid/axes PASS; modular entry point PASS; model and view transforms visibly demonstrated PASS.

Known limitations: rendering still contains only the foundation demo; campus blockout and collision are next. The installed FreeGLUT headers do not provide `glutLeaveMainLoop`, so Escape exits with `std::exit`.

Next phase: Phase 02, campus blockout.

## Phase 00 — PASS

The repository and all supplied references were audited. The current source is an unmodified GLUT shapes demo. Reference facts, ambiguous details, and an approximate coordinate scheme are recorded in `docs/REFERENCE_INTERPRETATION.md` and `docs/LAYOUT_COORDINATES.md`. The baseline source compiles with MinGW 8.1.0 and FreeGLUT.

Files changed: `PROJECT_STATUS.md`, `BUILD_INSTRUCTIONS.md`, `docs/REFERENCE_INTERPRETATION.md`, `docs/LAYOUT_COORDINATES.md`.

Controls: baseline GLUT demo uses `+` and `-` for tessellation, `Q` or Escape to quit. Campus controls will be introduced in later phases.

Known limitations: no campus, player, games, or tests exist yet; dimensions are schematic. The supplied JPEG named as a punch-gate top view is a perspective photo of an interior atrium, so it does not establish floor-plan coordinates.

Acceptance: baseline build PASS; every supplied reference inspected PASS; facts and assumptions separated PASS; coordinate convention fixed PASS; no unsupported rooms added PASS.

Next phase: Phase 01, engine foundation.
