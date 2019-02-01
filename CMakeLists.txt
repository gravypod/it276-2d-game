cmake_minimum_required(VERSION 3.6)
project(gf2d)

# Custom CMake packages
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Include SDL2 (images, ttf, etc)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(
        gf2d

        # Game code
        src/game/game.c src/game/game.h

        # Game Entity
        src/game/entity/entity.c src/game/entity/entity.h
        src/game/entity/manager.c src/game/entity/manager.h


        # GF2D Libraries
        src/gf2d_draw.c
        src/gf2d_graphics.c
        src/gf2d_sprite.c
        src/gf2d_vector.c

        # Source file libraries
        src/simple_logger.c src/game/entity/definitions/cursor.c src/game/entity/definitions/cursor.h src/game/entity/definitions/background.c src/game/entity/definitions/background.h src/game/entity/definitions/player.c src/game/entity/definitions/player.h)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/include" ${SDL2_INCLUDE_DIR}
                    ${SDL2_IMAGE_INCLUDE_DIR}
                    ${SDL2_TTF_INCLUDE_DIR})
target_link_libraries(gf2d m ${SDL2_LIBRARY}
                             ${SDL2_IMAGE_LIBRARIES}
                             ${SDL2_TTF_LIBRARIES})
