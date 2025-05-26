# CLI-Battleship

![Battleship Game Screenshot](battleship.png)

A terminal-based implementation of the classic Battleship game with C++ and NCurses/PDCurses.

## Features

- Classic Battleship gameplay
- Cross-platform support (Windows/Linux)
- Terminal-based UI with color support
- PvE and PvP mode

## Prerequisites

- C++17 compatible compiler
- CMake (version 3.15 or higher)
- NCurses (Linux) or PDCurses (Windows)

## Installation

### Linux

1. Install dependencies:
   ```bash
   # Debian/Ubuntu
   sudo apt-get install build-essential cmake libncursesw5-dev

   # Fedora
   sudo dnf install gcc-c++ cmake ncurses-devel ncurses-compat-libs
   sudo ln -s /usr/lib64/libncursesw.so.6 /usr/lib64/libtinfow.so.6
   ```

2. Clone and build:
   ```bash
   git clone https://github.com/ValterGames-Coder/CLI-BattleShip.git
   cd CLI-BattleShip
   mkdir build && cd build
   cmake ..
   make
   ```

### Windows

1. Install prerequisites:
   - [Visual Studio](https://visualstudio.microsoft.com/) with C++ support
   - [vcpkg](https://vcpkg.io/) for dependencies

2. Set up vcpkg:
   ```powershell
   git clone https://github.com/microsoft/vcpkg.git
   cd vcpkg
   .\bootstrap-vcpkg.bat
   .\vcpkg install pdcurses:x64-windows
   .\vcpkg integrate install
   ```

3. Build the project (use x64 Native Tools Command Promt for VS):
   ```powershell
   git clone https://github.com/ValterGames-Coder/CLI-BattleShip.git
   cd CLI-BattleShip
   mkdir build
   cd build
   cmake -DCMAKE_TOOLCHAIN_FILE="C:\vcpkg\scripts\buildsystems\vcpkg.cmake" ..
   cmake --build . --config Release
   ```

## Running the Game

After building, run the executable:

```bash
# Linux
cd bin/
./battleship

# Windows
cd \bin\Release
battleship.exe
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
