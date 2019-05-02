cmake_minimum_required(VERSION 3.6)
project(gf2d)

# Custom CMake packages
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Include SDL2 (images, ttf, etc)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_custom_command(
        OUTPUT ${CMAKE_SOURCE_DIR}/sounds/coconuts-silver_lights.mp3
        COMMAND youtube-dl -x --audio-format mp3 "https://www.youtube.com/watch?v=CcMz3aAZDv4" -o "./coconuts-silver_lights.%(ext)s"
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/sounds/"
        COMMENT "Downloading Coconuts - Silver Lights from youtube"
        VERBATIM
)

add_custom_command(
        OUTPUT ${CMAKE_SOURCE_DIR}/sounds/health-we_are_water.mp3
        COMMAND youtube-dl -x --audio-format mp3 "https://www.youtube.com/watch?v=toG4bHjPLEU" -o "./health-we_are_water.%(ext)s"
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/sounds/"
        COMMENT "Downloading HEALTH - We are Water from youtube"
        VERBATIM
)

add_custom_target(
        sound-files
        DEPENDS ${CMAKE_SOURCE_DIR}/sounds/health-we_are_water.mp3 ${CMAKE_SOURCE_DIR}/sounds/coconuts-silver_lights.mp3
)

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
        src/simple_logger.c

        src/game/entity/definitions/cursor.c src/game/entity/definitions/cursor.h
        src/game/entity/definitions/background.c src/game/entity/definitions/background.h
        src/game/entity/definitions/player.c src/game/entity/definitions/player.h
        src/game/entity/definitions/world.c src/game/entity/definitions/world.h
        src/game/collision/bbox.c src/game/collision/bbox.h
        src/game/entity/definitions/bug.c src/game/entity/definitions/bug.h
        src/game/entity/definitions/youdied.c src/game/entity/definitions/youdied.h
        src/game/states/manager.c src/game/states/manager.h src/game/collision/point.c
        src/game/collision/point.h src/game/collision/raytrace.c src/game/collision/raytrace.h

        src/game/states/save/world.c src/game/states/save/world.h
        src/game/states/save/save.h src/game/states/save/em.c src/game/states/save/em.h src/game/graphics/animation.c src/game/graphics/animation.h src/game/entity/definitions/healthbar.c src/game/entity/definitions/healthbar.h src/game/entity/definitions/equiptment.c src/game/entity/definitions/equiptment.h src/game/entity/definitions/pickup.c src/game/entity/definitions/pickup.h src/game/entity/definitions/throwing.c src/game/entity/definitions/throwing.h src/game/entity/definitions/plop.c src/game/entity/definitions/plop.h src/game/entity/definitions/egg.c src/game/entity/definitions/egg.h src/game/kennynl.h src/game/entity/definitions/door.c src/game/entity/definitions/door.h src/game/states/world.c src/game/states/world.h)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/include" ${SDL2_INCLUDE_DIR}
                    ${SDL2_IMAGE_INCLUDE_DIR}
                    ${SDL2_TTF_INCLUDE_DIR})
target_link_libraries(gf2d m ${SDL2_LIBRARY}
                             ${SDL2_IMAGE_LIBRARIES}
                             ${SDL2_TTF_LIBRARIES})
add_dependencies(gf2d sound-files)