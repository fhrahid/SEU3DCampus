@echo off
set "PATH=C:\Program Files\CodeBlocks\MinGW\bin;%PATH%"
set "SOURCES=SEU\main.cpp SEU\src\core\App.cpp SEU\src\core\Input.cpp SEU\src\chat\SEUGPTChat.cpp SEU\src\games\Game2048.cpp SEU\src\games\GameManager.cpp SEU\src\games\Ludo.cpp SEU\src\games\RockPaperScissors.cpp SEU\src\games\RubiksCube.cpp SEU\src\games\TicTacToe.cpp SEU\src\interaction\InteractionSystem.cpp SEU\src\physics\CollisionWorld.cpp SEU\src\player\Player.cpp SEU\src\render\Camera.cpp SEU\src\render\Primitives.cpp SEU\src\render\TextureManager.cpp SEU\src\world\CampusLayout.cpp SEU\src\world\Furniture.cpp"

"C:\Program Files\CodeBlocks\MinGW\bin\g++.exe" -std=c++17 -Wall -Wextra -Werror -I SEU %SOURCES% -o SEU\bin\Debug\SEU.exe -lfreeglut -lopengl32 -lglu32 -lwinmm -lgdi32 -lwinhttp

if %ERRORLEVEL% equ 0 (
    echo [BUILD SUCCESSFUL]
    copy /Y SEU\bin\Debug\SEU.exe SEU\bin\Debug\SEU-final.exe >nul
) else (
    echo [BUILD FAILED] with error %ERRORLEVEL%
)
exit /b %ERRORLEVEL%
