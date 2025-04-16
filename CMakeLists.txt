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
    # Windows: First try vcpkg, then manual PDCurses
        
    if(NOT CURSES_FOUND)
        message(STATUS "PDCurses not found via vcpkg, trying manual path...")
        set(PDCURSES_ROOT "C:/libs/pdcurses" CACHE PATH "PDCurses root directory")
        find_path(CURSES_INCLUDE_DIR
            NAMES curses.h
            PATHS ${PDCURSES_ROOT}/include
                  ${PDCURSES_ROOT}
                  "C:/Program Files (x86)/PDCurses"
        )
        find_library(CURSES_LIBRARY
            NAMES pdcurses curses
            PATHS ${PDCURSES_ROOT}/lib
                  ${PDCURSES_ROOT}
                  "C:/Program Files (x86)/PDCurses"
        )
        
        if(CURSES_INCLUDE_DIR AND CURSES_LIBRARY)
            set(CURSES_FOUND TRUE)
            set(CURSES_LIBRARIES ${CURSES_LIBRARY})
            set(CURSES_INCLUDE_PATH ${CURSES_INCLUDE_DIR})
            message(STATUS "Found PDCurses manually: ${CURSES_LIBRARY}")
        else()
            message(FATAL_ERROR "PDCurses not found!\n"
                "Windows: Install via vcpkg:\n"
                "  vcpkg install pdcurses:x64-windows\n"
                "Or download PDCurses from https://pdcurses.org/ and set PDCURSES_ROOT")
        endif()
    endif()
else()
    # Linux/macOS: Use NCurses
    find_package(Curses REQUIRED)
    if(NOT CURSES_FOUND)
        message(FATAL_ERROR "NCurses not found! Install:\n"
            "  Linux: sudo apt-get install libncursesw5-dev\n"
            "  macOS: brew install ncurses")
    endif()
endif()

#-----------------------------------------------------------------------------
# Project Structure
#-----------------------------------------------------------------------------
add_subdirectory(src)

# Install rules (optional)
install(TARGETS battleship DESTINATION bin)
install(DIRECTORY img/ DESTINATION share/battleship/img)