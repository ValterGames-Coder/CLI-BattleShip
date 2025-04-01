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

# Build output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Find NCurses library - prefer wide-character version
find_package(Curses REQUIRED)
set(CURSES_NEED_WIDE TRUE)  # Request wide-character support
include_directories(${CURSES_INCLUDE_DIRS})

# Add subdirectories
add_subdirectory(src)

install(TARGETS battleship DESTINATION bin)

# Install the 'img' folder to a system directory (e.g., /usr/share/battleship/img)
install(DIRECTORY img/ DESTINATION share/battleship/img)