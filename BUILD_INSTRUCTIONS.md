# Build instructions

The project targets C++17, desktop OpenGL and FreeGLUT. The checked-in Code::Blocks project is `SEU/SEU.cbp`.

## Windows / Code::Blocks MinGW

Install Code::Blocks with a 64-bit MinGW toolchain and FreeGLUT headers and libraries. Open `SEU/SEU.cbp`, select Debug or Release, then Build and Run. The project currently uses the toolchain under `C:\Program Files\CodeBlocks\MinGW`.

For a command-line build in PowerShell, put the compiler's `bin` directory on `PATH` so GCC can load its helper DLLs:

```powershell
$env:Path = 'C:\Program Files\CodeBlocks\MinGW\bin;' + $env:Path
& 'C:\Program Files\CodeBlocks\MinGW\bin\g++.exe' -std=c++17 -Wall -Wextra SEU\main.cpp -o SEU\bin\Debug\SEU.exe -lfreeglut -lopengl32 -lglu32 -lwinmm -lgdi32
```

Run `SEU\bin\Debug\SEU.exe`. This command is the baseline Phase 00 build; it will be updated as modules are added.

## Baseline audit

The original `main.cpp` compiles on the installed MinGW 8.1.0 toolchain. It is only the Code::Blocks GLUT shapes demo, not campus code. GCC reports two unused callback parameters. The tracked `SEU.exe` and object file are stale build artifacts and should not be treated as source.
