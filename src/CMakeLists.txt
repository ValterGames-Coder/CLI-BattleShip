# Executable target
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
    ${CURSES_INCLUDE_PATH}  # For curses.h
)

# Link libraries
target_link_libraries(battleship PRIVATE
    ${CURSES_LIBRARIES}
)

#-----------------------------------------------------------------------------
# Resource Handling (img folder)
#-----------------------------------------------------------------------------
# Copy img folder to build directory (cross-platform)
add_custom_command(TARGET battleship POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/img
        $<TARGET_FILE_DIR:battleship>/img
    COMMENT "Copying img folder to executable directory"
)

# Windows-specific: Copy PDCurses DLL if needed
if(WIN32 AND EXISTS "${CURSES_LIBRARY}" AND CURSES_LIBRARY MATCHES "\\.dll$")
    add_custom_command(TARGET battleship POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "${CURSES_LIBRARY}"
            $<TARGET_FILE_DIR:battleship>/
        COMMENT "Copying PDCurses DLL to executable directory"
    )
endif()

# Set output name and path
set_target_properties(battleship PROPERTIES
    OUTPUT_NAME "battleship"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/apps"
)