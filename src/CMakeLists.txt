# Main executable
add_executable(battleship
    battleship.cpp
    game.cpp
    
    # Base
    base/ascii.cpp
    
    # Animation
    animation/animator.cpp
    
    # Logic
    logic/board.cpp
    logic/bot.cpp
    logic/cursor.cpp
    logic/ship.cpp
    logic/ship_builder.cpp
    logic/shooter.cpp
    
    # Scenes
    scenes/game_scene.cpp
    scenes/main_menu_scene.cpp
    scenes/rules_scene.cpp
    scenes/scene.cpp
    
    # UI
    ui/dialog.cpp
    ui/panel.cpp
)

# Include directories
target_include_directories(battleship PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/animation
    ${CMAKE_SOURCE_DIR}/include/base
    ${CMAKE_SOURCE_DIR}/include/logic
    ${CMAKE_SOURCE_DIR}/include/scenes
    ${CMAKE_SOURCE_DIR}/include/ui
)

# Link libraries - use both curses and ncursesw if available
target_link_libraries(battleship PRIVATE
    ${CURSES_LIBRARIES}
)

# On Linux, try to explicitly link against ncursesw if available
if(UNIX AND NOT APPLE)
    find_library(NCURSESW_LIB ncursesw)
    if(NCURSESW_LIB)
        target_link_libraries(battleship PRIVATE ${NCURSESW_LIB})
    endif()
endif()

if(WIN32)
    # Manually specify PDCurses paths (if not using vcpkg)
    set(PDCURSES_ROOT "C:/libs/pdcurses")  # Change to your path
    find_library(CURSES_LIBRARY
        NAMES pdcurses curses
        PATHS ${PDCURSES_ROOT}/lib
    )
    find_path(CURSES_INCLUDE_DIR
        NAMES curses.h
        PATHS ${PDCURSES_ROOT}/include
    )

    if(CURSES_LIBRARY AND CURSES_INCLUDE_DIR)
        target_include_directories(battleship PRIVATE ${CURSES_INCLUDE_DIR})
        target_link_libraries(battleship PRIVATE ${CURSES_LIBRARY})
    else()
        message(FATAL_ERROR "PDCurses not found! Install it or set PDCURSES_ROOT.")
    endif()
endif()

# For Windows, add the PDCurses import library if needed
if(WIN32)
    target_link_libraries(battleship PRIVATE pdcurses)
endif()

# Set output name and properties
set_target_properties(battleship PROPERTIES
    OUTPUT_NAME "battleship"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

add_custom_command(
    TARGET battleship POST_BUILD  # Runs after building the executable
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/img"  # Source folder (in your project root)
        "$<TARGET_FILE_DIR:battleship>/img"  # Destination (next to executable)
    COMMENT "Copying 'img' folder to executable directory"
)