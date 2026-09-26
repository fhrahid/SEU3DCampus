# Controls

## Campus & Navigation

- `WASD`: Walk forward, backward, strafe left, strafe right.
- `R` or `Shift`: Run / sprint (high-speed traversal).
- `Space`: Jump.
- `N`: **Toggle Day / Night Mode** (switches dynamically between bright sunlight daytime and atmospheric illuminated night with celestial moon, glowing atrium lightwells, interior lamps, and night haze).
- `1`, `2`, `3`, `4`: **Elevator Lift Transformation** (instantly transforms/teleports to Floor 1, Floor 2, Floor 3, or Floor 4 with on-screen arrival notification).
- `M` or Left Click: Capture mouse for smooth 360° mouse-look.
- `0`: Reset player spawn to the front entrance facing Stair 1.
- `E`: Context interaction (sit / stand at chairs and desks; launch tournaments at gaming tables).
- `F`: Exterior facade view showcasing the Southeast University architecture.
- `O`: Drone Mode (toggle free-flight inspection drone / playable third-person aerial camera).
- `V`: Top-down orthographic campus plan view.
- `L`: Toggle 3D floating room labels and directional signage.
- `G`: Toggle collision wireframes and spatial grid debug visuals.
- `T`: Transformation demo object.
- `Esc`: Quit campus application.

## Multi-Floor Architecture & Elevator Traversal (Floors 1, 2, 3, 4)

- **Elevator / Lift System & Boardable 3D Cabins (`1`, `2`, `3`, `4`)**:
  - `1`: **Floor 1 (Ground Floor, `y = 1.2m`)**: Grand entrance lobby, Admission Office 1 & 2 (featuring the 2.4m Grand East Entrance Gate facing the lobby), Cafeteria & Food Court (Food Shops 1-5), SEU Bookstore & Stationery, and the expanded Gaming & Recreation Suite.
  - `2`: **Floor 2 (Academic & Library Level, `y = 5.2m`)**: Central Library & Digital Commons, CSE & AI Research Lab, Smart Classroom 201, Dean's Office, and open central atrium with glass safety balustrades.
  - `3`: **Floor 3 (Grand Auditorium & Robotics Level, `y = 9.2m`)**: Tiered seating auditorium, presentation stage & projection screen, Robotics & Innovation Lab workstations, and atrium glass balustrades.
  - `4`: **Floor 4 (Executive Boardroom & Sky Garden Level, `y = 13.2m`)**: Executive conference boardroom, Chancellor Suite, and open-air Rooftop Sky Garden & Terrace with panoramic glass safety balustrades overlooking the campus.
- **Ground Floor Highlights**:
  - **Admission Office 1 Grand Entrance Gate ($x = -11.5\text{m}$)**: A wide $2.4\text{m}$ grand architectural glass entrance gate facing the main lobby corridor, with double glass doors, terracotta architrave, illuminated bilingual signage, front consultation desk (`E`), guardian waiting lounge (`E`), and connecting door into Admission Office 2.
- **Architectural Elevator Features**:
  - **Boardable 3D Cabins**: West Lift 4 ($x = -13.5\text{m}$) and East Lift 2 ($x = 10.6\text{m}$) feature doors retracted into side wall pockets and brass threshold sill plates, allowing players to walk directly inside the cabin.
  - **Cabin Interior**: Dark polished granite tile floor, 4 warm LED ceiling downlights, brushed stainless steel side walls, full-height rear mirror, chrome safety handrails, and a Car Operating Panel (COP) with buttons `[1]`, `[2]`, `[3]`, `[4]` and digital LED floor display.
  - **Exterior Portal**: Stainless steel architrave, digital hall lantern screen (`FL 1-4` with directional travel arrows `▲`/`▼`), and dual illuminated call stations.
  - **Preserved Coordinates**: When riding the lift via number keys `1`, `2`, `3`, or `4`, your position inside the elevator cabin is preserved across floors.
- **Cafeteria Food Court (Food Shops 1-5)**:
  - Approach any of the 5 open serving counters around the cafeteria and press `E` to order:
    - **Shop 1 (SEU Deli & Burgers)**: Burgers, crispy chicken, fries, soda cooler.
    - **Shop 2 (Pizza & Hot Rolls)**: Pizza slices, golden patties, chicken rolls.
    - **Shop 3 (Bakery & Espresso Cafe)**: Glazed donuts, muffins, croissants, espresso machine.
    - **Shop 4 (Fresh Juice Bar & Smoothies)**: Fresh tropical fruit bowls, fruit blenders.
    - **Shop 5 (Asian Noodle Bowl & Rice)**: Buffet warmer with chowmein, fried rice, dumplings.
- **SEU University Stationery & Bookstore**:
  - Enter through the grand double glass doors at $z = 16.5\text{m}$:
    - **Textbook Bookcases**: Computer Science, Engineering, Mathematics, Business, Architecture, and Literature.
    - **Central Gondola**: Spiral notebooks and A4 paper reams.
    - **Showcase**: Casio scientific calculators, drafting compass sets, USB drives, pen carousels.
    - **Xerox Station (`E`)**: High-volume commercial photocopier with scanner platen and document feeder.
    - **Checkout Counter (`E`)**: POS cash register with barcode scanner.
- **Physical Staircases**:
  - **Stair 1**: Exterior entrance ramp from outdoor ground level up to Floor 1 lobby.
  - **Stair 3**: Central 16-step architectural staircase with orange handrails leading from Floor 1 directly up to Floor 2 (`y = 5.2m`).
  - **Stair 2**: Secondary 16-step staircase connecting Floor 1 to Floor 2.

## Drone Mode (Free Flight & Playable Chase)

Press `O` to enter Drone Mode. Press `TAB` to switch between modes:

### 1. Free Drone Flight Mode
- `WASD`: Fly drone forward, backward, strafe left, strafe right along camera heading in full 3D.
- `Space` or `E`: Ascend (fly straight up, +Y).
- `C` or `Q`: Descend (fly straight down, -Y).
- `Shift` or `R`: Turbo thrusters (fast flight across the campus and sky).
- Mouse Look & Arrow Keys: Pitch (look up/down) and Yaw (turn left/right) 360°.
- `[` / `]`: Rapid height adjust.
- `0`: Reset drone camera to the full-campus overview vantage point.

### 2. Playable Chase Drone Mode (Third-Person View)
- The campus is 100% playable from an aerial chase camera!
- `WASD`: Move the player character (walk/run through rooms, climb stairs to 2nd floor).
- `Shift` / `R`: Sprint.
- `Space`: Jump.
- `E`: Sit on chairs or enter minigames.
- Mouse Look & Arrow Keys: Orbit the chase drone around the player.
- `[` / `]`: Adjust chase camera elevation height.
- `+` / `-`: Adjust chase camera distance (zoom in/out).
- The 3D student avatar is visible walking, running, and sitting throughout the campus.

## Transformation Demo

Press `T`, then use arrow keys to translate, `Q/E` to rotate, and `+/-` to scale. Press `T` again to return to normal mode.

## Gaming Room Interactive Screens & Minigames

The games are 100% playable inside an authentic **Arcade / Esports Gaming Monitor Screen** within the Gaming Room:

### 1. In-World Physical Gaming Screens & Stations
- **Master Esports Video Screen 1 (Gaming Room 1)**: Mounted on the north divider wall ($x = 4.8\text{m}$) with a dual-stick arcade console counter, soundbar, and glowing channel attract display.
- **Lounge Gaming Screen 2 (Gaming Room 2)**: Mounted on the south divider wall ($x = 13.5\text{m}$) overlooking the lounge seating area.
- **Tabletop Game Screens**: Digital match monitors positioned at Carrom (`2048`), Table Tennis (`RPS`), Chess (`TTT`), Rubik's (`Cube`), and Ludo (`Ludo`).
- Press `E` near any screen or gaming station to activate the **Gaming Screen**.

### 2. Playing on the Gaming Screen
- When active, the game is framed inside a dedicated **240Hz Esports Display Monitor** featuring:
  - Translucent background dimmer keeping the 3D Gaming Room visible around the screen.
  - Ambient neon RGB backlighting, titanium bezel, desktop pedestal stand, and status LEDs.
  - Top OSD status bar showing live channel pills (`1:TTT`, `2:RPS`, `3:2048`, `4:Cube`, `5:Ludo`).
  - Subtle CRT scanline shader effect for authentic arcade gameplay.
- **Available Games on Screen**:
  - `1`: **Tic-Tac-Toe** — 2-Player strategy board (`WASD` or `1`-`9` select, `Space`/`Enter` place, `N` new).
  - `2`: **Rock Paper Scissors** — Fast-action AI challenger (`1` Rock, `2` Paper, `3` Scissors, `N` reset).
  - `3`: **2048 Arcade** — Tile sliding merge puzzle (`WASD`/`Arrows` slide tiles, `N` new).
  - `4`: **Rubik's Cube** — Unfolded 3D net cube simulator (`U/D/L/R/F/B` turn, hold `I` inverse, `X` scramble, `N` reset).
  - `5`: **Ludo Championship** — 4-token board game vs AI (`Space`/`R` roll dice, `1`-`4` select token, `N` new).
- **Controls & Navigation**:
  - `Esc`: Return from any active game to the Screen Channel Menu; press `Esc` on the menu to step back into the Gaming Room.
  - `N`: Start a new game / reset score.
  - Directly approaching any themed table automatically boots that specific game on the screen.
