# Proposed layout coordinates

All coordinates are **approximate design units**, not surveyed metres. The source image is roughly 960 × 810 pixels. One unit is about 20 image pixels, with image x≈500 mapped to world X=0 and image bottom≈800 mapped to Z=0. Thus plan right is +X and top is +Z. Y=0 is outside ground and the interior floor is provisionally Y=1.2. Centralized constants in source should own final values.

| Zone | X bounds | Z bounds | Relationship |
|---|---:|---:|---|
| Site | -24 to 24 | 0 to 40 | Overall schematic footprint |
| Garden | -16.5 to 15.5 | 0.5 to 5 | Outdoors, between gates |
| IN Gate / guard | -21 to -17 / -24 to -21 | 0 to 2 / 0 to 5 | Front left |
| OUT Gate | 17 to 22 | 0 to 2 | Front right |
| Front driveway | -24 to 24 | 5 to 10 | Below building, above garden |
| Right driveway | 16 to 24 | 5 to 40 | Outdoor strip |
| Ground-floor building | -24 to 16 | 10 to 40 | Excludes right driveway |
| Stair 1 | -11 to 1.5 | 10 to 14 | Outdoor entry to raised floor |
| Punch Gate | -11 to 1.5 | 13.5 to 16.5 | Across central entry |
| Central circulation | -11 to 7 | 16 to 30 | Open distributor |
| Security Room | -24 to -21 | 7 to 10 | Front left |
| Admission Office 1 | -24 to -12 | 10 to 21 | Outer administrative suite |
| Admission Office 2 | -24 to -17 | 13.5 to 21 | Nested in Admission Office 1 |
| Bank 1 | -17 to -12 | 13.5 to 21 | Separate from Bank 2 |
| Infirmary | -24 to -17 | 21 to 24 | Left middle |
| Female washroom | -24 to -21 | 24 to 28 | Left, beside lifts |
| Lift 4 / Lift 3 | -21 to -17 / -17 to -12 | 24 to 28 | Side by side |
| Faculty Lounge | -24 to -11 | 28 to 33 | Upper left |
| Food Shop 1 / 2 | -24 to -21 | 36 to 40 / 33 to 36 | Upper left edge |
| Cafeteria | -11 to 13 | 30 to 40 | Large rear zone |
| Food Shop 5 | 9 to 13 | 37 to 40 | Cafeteria upper-right edge |
| Food Shop 3 / 4 | 13 to 16 | 35 to 40 / 30 to 35 | Right driveway edge |
| Stair 3 | 1 to 4 | 25 to 30 | Internal, static |
| Stair 2 | 9 to 16 | 27 to 30 | Internal, static |
| Lift 1 / Lift 2 | 4 to 9 / 9 to 12 | 24 to 27 | Side by side |
| Male washroom | 12 to 16 | 24 to 27 | Beside Lift 2 |
| Bank 2 | 7 to 11 | 20 to 24 | Separate right-middle room |
| Stationery | 11 to 16 | 17 to 24 | Beside Bank 2 |
| Gaming Room 1 | 3 to 16 | 10 to 17 | Outer gaming room |
| Gaming Room 2 | 3 to 16 | 10 to 13.5 | Nested lower partition, only internal entry |

Room bounds overlap at schematic edges where walls/door gaps will be resolved during blockout. An in-game top view and collision walkthrough must validate the final geometry against the annotated image.

## Orange gate markers

The orange rectangles in `PROMPT/08_ORIGINAL_REFERENCES/seu3dcampus.png` are modeled as separate low gate assemblies, rather than inferred only from room centers. Their world centers are: `(-18.6,31.7)`, `(-6.85,30)`, `(0.05,30)`, `(5.9,24.65)`, `(10,24.65)`, `(13.55,24.65)`, `(-15.1,24.35)`, `(-12.75,24.35)`, `(-18.45,23.15)`, `(-14.6,21.25)`, `(-7.75,21.05)`, `(-1.5,21.05)`, `(10.2,21.35)`, `(11.1,18.25)`, `(8.8,16.3)`, `(8.75,13.2)`, `(-16.6,17.25)`, `(-21,13.35)`, `(-14.5,9.95)`, and `(-21,8.25)`. The larger orange markers at `(-18.6,.35)` and `(18.5,.35)` are the IN and OUT gate markers. The Punch Gate is modeled separately as the striped central barrier.
