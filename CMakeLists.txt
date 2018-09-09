cmake_minimum_required ( VERSION 3.1 )
set (FG_PROJECT_NAME FarmerGame)

project(${FG_PROJECT_NAME})

set(CMAKE_BUILD_TYPE "Release" CACHE STRING "")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_GENERATOR_PLATFORM x64)

set(allegro false CACHE BOOL "Link to allegro")
if (allegro)
    set(allegincludedir "" CACHE STRING "The directory of allegro includes")
    set(alleglibdir "" CACHE STRING "The directories of allegro's libraries")
    if (UNIX)
        set(alleglib "liballegro.a" CACHE STRING "The path of the main allegro library relative to allegdir")
        set(ttflib "liballegro_ttf.a" CACHE STRING "The path of the ttf allegro extension relative to allegdir")
        set(imglib "liballegro_image.a" CACHE STRING "The path of the img allegro extension relative to allegdir")
        set(primlib "liballegro_primitives.a" CACHE STRING "The path of the primtive allegro extension relative to allegdir")
        set(fontlib "liballegro_font.a" CACHE STRING "The path of the font allegro extension relative to allegdir")
    else()
        set(alleglib "allegro-static.lib" CACHE STRING "The path of the main allegro library relative to allegdir")
        set(ttflib "allegro_ttf-static.lib" CACHE STRING "The path of the ttf allegro extension relative to allegdir")
        set(imglib "allegro_image-static.lib" CACHE STRING "The path of the img allegro extension relative to allegdir")
        set(primlib "allegro_primitives-static.lib" CACHE STRING "The path of the primtive allegro extension relative to allegdir")
        set(fontlib "allegro_font-static.lib" CACHE STRING "The path of the font allegro extension relative to allegdir")
    endif()
endif()

set(boxincludedir "" CACHE STRING "Include directory of Box2D")
set(boxlibdir "" CACHE STRING "Directory of Box2D libraries")
if (UNIX)
    set(boxlib "Box2D.a" CACHE STRING "Name of Box2D library")
else()
    set(boxlib "Box2D.lib" CACHE STRING "Name of Box2D library")
endif()

set(allegextbuild true CACHE BOOL "Add AllegroExt as subproject")
set(allegextincludedir "${CMAKE_CURRENT_SOURCE_DIR}/AllegroExt/allegroext" CACHE STRING "Include directory of AllegroExt")
set(allegextlibdir "" CACHE STRING "Directory of AllegroExt")
set(allegextlib "AllegroExt" CACHE STRING "Name of AllegroExt library")

set(lightbuild true CACHE BOOL "Add Lighting4 as subproject")
set(lightincludedir "${CMAKE_CURRENT_SOURCE_DIR}/Lighting4/Lighting4" CACHE STRING "Include directory of Lighting4")
set(lightlibdir "" CACHE STRING "Directory of Lighting4 libraries")
set(lightlib "Lighting4" CACHE STRING "Name of Lighting4 library")

set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/farmergame)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(HEADERS
	${HEADER_DIR}/AniJoint.h
    ${HEADER_DIR}/AniPart.h
    ${HEADER_DIR}/BackgroundManager.h
    ${HEADER_DIR}/Bullet.h
    ${HEADER_DIR}/ContactListener.h
    ${HEADER_DIR}/DebugDrawer.h
    ${HEADER_DIR}/DigSite.h
    ${HEADER_DIR}/Elevator.h
    ${HEADER_DIR}/Farmer.h
    ${HEADER_DIR}/GameCore.h
    ${HEADER_DIR}/Gun.h
    ${HEADER_DIR}/HUD.h
    ${HEADER_DIR}/Item.h
    ${HEADER_DIR}/MedKit.h
    ${HEADER_DIR}/MedShot.h
    ${HEADER_DIR}/Mover.h
    ${HEADER_DIR}/PhysicsBody.h
    ${HEADER_DIR}/PhysicsJoint.h
    ${HEADER_DIR}/PhysicsRectangle.h
    ${HEADER_DIR}/Platform.h
    ${HEADER_DIR}/PlatLight.h
    ${HEADER_DIR}/PotatoMan.h
    ${HEADER_DIR}/RayCaster.h
    ${HEADER_DIR}/World.h)


set(SOURCES
	${SOURCE_DIR}/AniJoint.cpp
    ${SOURCE_DIR}/AniPart.cpp
    ${SOURCE_DIR}/BackgroundManager.cpp
    ${SOURCE_DIR}/Bullet.cpp
    ${SOURCE_DIR}/ContactListener.cpp
    ${SOURCE_DIR}/DebugDrawer.cpp
    ${SOURCE_DIR}/DigSite.cpp
    ${SOURCE_DIR}/Elevator.cpp
    ${SOURCE_DIR}/Farmer.cpp
    ${SOURCE_DIR}/GameCore.cpp
    ${SOURCE_DIR}/Gun.cpp
    ${SOURCE_DIR}/HUD.cpp
    ${SOURCE_DIR}/Item.cpp
    ${SOURCE_DIR}/MedKit.cpp
    ${SOURCE_DIR}/MedShot.cpp
    ${SOURCE_DIR}/Mover.cpp
    ${SOURCE_DIR}/PhysicsBody.cpp
    ${SOURCE_DIR}/PhysicsJoint.cpp
    ${SOURCE_DIR}/PhysicsRectangle.cpp
    ${SOURCE_DIR}/Platform.cpp
    ${SOURCE_DIR}/PlatLight.cpp
    ${SOURCE_DIR}/PotatoMan.cpp
    ${SOURCE_DIR}/RayCaster.cpp
    ${SOURCE_DIR}/Source.cpp
    ${SOURCE_DIR}/World.cpp)

include_directories(
    ${HEADER_DIR})

if (allegextbuild)
    add_subdirectory(AllegroExt)
endif()
if (lightbuild)
    add_subdirectory(Lighting4)
endif()

include_directories(
    ${allegincludedir}
    ${boxincludedir}
    ${allegextincludedir}
    ${lightincludedir})

add_executable(${FG_PROJECT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${FG_PROJECT_NAME}
    ${Boost_LIBRARIES}
    ${Protobuf_LIBRARIES}
    ${alleglibdir}${alleglib}
    ${alleglibdir}${ttflib}
    ${alleglibdir}${imglib}
    ${alleglibdir}${primlib}
    ${alleglibdir}${fontlib}
    ${boxlibdir}${boxlib}
    ${allegextlibdir}${allegextlib}
    ${lightlibdir}${lightlib})

set_property(TARGET ${FG_PROJECT_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${FG_PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED 11)

add_custom_command(TARGET ${FG_PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_CURRENT_SOURCE_DIR}/wdir ${CMAKE_CURRENT_BINARY_DIR})