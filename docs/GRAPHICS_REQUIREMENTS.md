# Graphics requirements matrix

| Requirement | Implemented | Source | Controls/location | Demonstration | Status |
|---|---|---|---|---|---|
| Translation | Yes | `core/App.cpp` transform branch | T + arrows | Move orange demo object | PASS |
| Rotation | Yes | `core/App.cpp` | T + Q/E | Rotate demo object | PASS |
| Scaling | Yes | `core/App.cpp` | T + +/- | Scale demo object | PASS |
| Complex objects | Yes | `world/Furniture.cpp`, `CampusLayout.cpp` | Campus | Stairs, gates, counters, games | PASS |
| Continuous rotation | Yes | `core/App.cpp` | Campus | Gold rotating display above cafeteria | PASS |
| Exterior through glass | Yes | `CampusLayout.cpp` | Gaming rooms | View garden/driveway through glass fronts | PASS |
| Two active lights | Yes | `core/App.cpp` | Campus | Directional exterior + warm interior point | PASS |
| Ambient/diffuse/specular/shininess | Yes | `render/Primitives.cpp` | All materials | Compare concrete, wood, glass | PASS |
| Model transformation | Yes | `render/Primitives.cpp`, `App.cpp` | Campus/demo | Push/pop, translate/rotate/scale | PASS |
| View transformation | Yes | `render/Camera.cpp` | WASD/mouse/V | Move and look; top view | PASS |
| Floor texture | Yes | `render/TextureManager.cpp`, `CampusLayout.cpp` | Room floors | Checker tile surfaces | PASS |
| Wall texture | Yes | `TextureManager.cpp`, `CampusLayout.cpp` | Facade | Brick-like generated pattern | PASS |
| Furniture texture | Yes | `TextureManager.cpp`, `Furniture.cpp` | Tables | Wood-like generated pattern | PASS |
| Sign/logo text | Yes | `Primitives.cpp`, `CampusLayout.cpp` | Facade/rooms | SEU and room signage | PASS |
| Algorithmic games | Yes | `games/*.cpp` | Gaming menu | Play all five rule systems | PASS |
