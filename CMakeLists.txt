cmake_minimum_required(VERSION 3.15)
project(battleship VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Platform-specific settings
if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x0601)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
elseif(UNIX)
    add_definitions(-D_POSIX_C_SOURCE=200809L)
endif()

# Build output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

#-----------------------------------------------------------------------------
# Curses/Ncurses Setup (Cross-Platform)
#-----------------------------------------------------------------------------
set(CURSES_NEED_WIDE TRUE)  # Required for waddnwstr support

if(WIN32)
    # Windows: Use PDCurses (vcpkg or manual)
    find_package(Curses REQUIRED)
    if(NOT CURSES_FOUND)
        # Fallback: Manual PDCurses path (change if needed)
        set(PDCURSES_ROOT "C:/libs/pdcurses" CACHE PATH "PDCurses root directory")
        find_library(CURSES_LIBRARY
            NAMES pdcurses curses
            PATHS ${PDCURSES_ROOT}/lib
            REQUIRED
        )
        find_path(CURSES_INCLUDE_DIR
            NAMES curses.h
            PATHS ${PDCURSES_ROOT}/include
            REQUIRED
        )
        set(CURSES_LIBRARIES ${CURSES_LIBRARY})
    endif()
else()
    # Linux/macOS: Use NCurses
    find_package(Curses REQUIRED)
endif()

#-----------------------------------------------------------------------------
# Project Structure
#-----------------------------------------------------------------------------
add_subdirectory(src)

# Install rules (optional)
install(TARGETS battleship DESTINATION bin)
install(DIRECTORY img/ DESTINATION share/battleship/img)