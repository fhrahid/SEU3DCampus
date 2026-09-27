# Proposed layout coordinates

All coordinates are **approximate design units**, not surveyed metres. The source image is roughly 960 × 810 pixels. One unit is about 20 image pixels, with image x≈500 mapped to world X=0 and image bottom≈800 mapped to Z=0. Thus plan right is +X and top is +Z. Y=0 is outside ground and the interior floor is provisionally Y=1.2. Centralized constants in source should own final values.

| Zone | X bounds | Z bounds | Relationship |
|---|---:|---:|---|
| Site | -24 to 24 | 0 to 40 | Overall schematic footprint |
| Garden | -16.6 to 16.8 | 0 to 4.7 | Outdoors, between gates |
| IN Gate / guard | -20.3 / -24 to -21 | 0 to 3 / 6 to 9.3 | Front left |
| OUT Gate | 18 to 22 | 0 to 2 | Front right |
| Front driveway | -12 to 2.8 | 8.2 to 9.9 | Stair approach strip |
| Right driveway | 16.5 to 24 | 5 to 40 | Outdoor strip |
| Ground-floor building | -24 to 16.5 | 9.5 to 40 | Excludes right driveway |
| Stair 1 | -12 to 2.8 | 8.2 to 9.9 | Long lower-central entry |
| Security Checkpoint | -11.8 to 2.8 | 11.7 to 12.5 | Sleek optical turnstiles with card access |
| Main Lobby Corridor | -11.5 to 3.6 | 12.5 to 29.8 | Generous wide central distributor |
| Cross-Corridor (beside Gaming) | 3.6 to 16.5 | 16.2 to 18.2 | 2.0m wide open cross-corridor |
| Security Room | -24 to -21 | 6 to 9.3 | Front-left building service room |
| Admission Office 1 | -24 to -11.5 | 9.5 to 14.0 | East-facing grand glass gate |
| Admission Office 2 | -24 to -16.2 | 14.0 to 21.6 | Upper staff / consultation office |
| Bank 1 | -16.2 to -11.5 | 14.0 to 21.6 | Separate from Admission Office 2 |
| Infirmary | -24 to -16.2 | 21.6 to 24.6 | Left middle |
| Female washroom | -24 to -20.8 | 24.6 to 28.2 | Left, beside lifts |
| Lift 4 / Lift 3 | -20.8 to -10.2 | 25 to 28 | Side by side (West Core) |
| Faculty Lounge | -24 to -9.8 | 28.2 to 33.6 | Upper left |
| Food Shop 1 / 2 | -24 to -20.8 | 36.6 to 40.0 / 33.6 to 36.6 | Upper left edge facing Cafeteria |
| Cafeteria | -10.2 to 10.2 | 29.8 to 40.0 | Grand 3.6m open double glass entrance |
| Food Shop 5 | 10.2 to 14.0 | 38.0 to 40.0 | Cafeteria upper-right edge |
| Food Shop 3 / 4 | 13.8 to 16.5 | 36.0 to 39.0 / 31.5 to 35.0 | Right food court edge facing Cafeteria |
| Stair 3 | 1.4 to 4.6 | 24.4 to 30.6 | Primary staircase with Floor 2 stairwell opening |
| Stair 2 | 9.5 to 15.5 | 26.5 to 30.5 | Secondary staircase |
| Lift 1 / Lift 2 | 5.4 to 12.0 | 25.0 to 27.4 | Side by side (East Core) |
| Male washroom | 13.4 to 16.6 | 25.0 to 28.1 | Beside Lift 2 |
| Bank 2 | 7.4 to 12.0 | 18.2 to 22.2 | Separate right-middle room with corridor frontage |
| Bookstore & Stationery | 12.0 to 16.6 | 18.2 to 22.2 | Beside Bank 2 |
| Gaming Room 1 | 3.6 to 16.6 | 12.9 to 16.2 | Outer esports arena, widened lobby corridor |
| Gaming Room 2 | 3.6 to 16.6 | 9.5 to 12.9 | Board games lounge, internal entry |

## Optical Turnstiles and Clean Floor Clearance

The legacy 2D floorplan markers (`orangeGate` blocks) and solid punch beam have been completely removed from walking paths. Access control is modeled using modern optical glass speed-gates with RFID badge readers at the main lobby entrance (`x in [-7.5, -2.5], z = 11.5`), ensuring high aesthetic fidelity and unobstructed movement across all rooms and corridors.
