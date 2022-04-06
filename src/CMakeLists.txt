cmake_minimum_required (VERSION 3.8)

add_executable (4_16_Arcanoid "main.c"  "defines.h" "game.c"  "game.h"   "ball.h" "ball.c" "player.h" "player.c" "LevelMenu.c" "LevelMenu.h" "Font.h" "Font.c")

target_compile_definitions(4_16_Arcanoid PRIVATE VME_VERSION=${VME_VERSION})

target_include_directories(4_16_Arcanoid PRIVATE ../${SDL2_INCLUDE_DIR} PRIVATE ../${SDL2_IMG_INCLUDE_DIR})
target_link_directories(4_16_Arcanoid PRIVATE ../${SDL2_LIB_DIR} PRIVATE ../${SDL2_IMG_LIB_DIR})
target_link_libraries(4_16_Arcanoid PRIVATE ${SDL2_LIBS}) 

message("а кто: " ${PROJECT_NAME})
message("sdl2 а где: " ${SDL2_INCLUDE_DIR})



add_custom_command(TARGET 4_16_Arcanoid POST_BUILD# Adds a post-build event to 4_16_Arcanoid
    COMMAND ${CMAKE_COMMAND} -E copy_if_different# which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/SDL2-2.0.20/lib/${EXE_BITS}/SDL2.dll"# <--this is in-file
        $<TARGET_FILE_DIR:4_16_Arcanoid># <--this is out-file path
    COMMAND ${CMAKE_COMMAND} -E copy_if_different# which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/SDL2_image-2.0.5/lib/${EXE_BITS}/zlib1.dll"# <--this is in-file
        $<TARGET_FILE_DIR:4_16_Arcanoid># <--this is out-file path
    COMMAND ${CMAKE_COMMAND} -E copy_if_different# which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/SDL2_image-2.0.5/lib/${EXE_BITS}/SDL2_image.dll"# <--this is in-file
        $<TARGET_FILE_DIR:4_16_Arcanoid>)# <--this is out-file path