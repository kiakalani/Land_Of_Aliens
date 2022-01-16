cmake_minimum_required(VERSION 2.6)

# Name of project
set(PROJ_NAME FinalProject)
project(${PROJ_NAME} C CXX)

# Specify project files: header files and source files
set(HDRS
    ../Camera/Camera.hh 
    ../Display/GameDisplay.hh
    ../Entity/Entity.hh
    ../Entity/Geometry.hh
    ../Entity/Geometries/QuadGeometry.hxx
    ../Shader/Shader.hh
    ../Texture/Texture.hh
    ../World/GameWorld.hh
    ../includes.hxx
    ../World/BasicWorld.hxx
    ../Entity/Label.hh
    ../Entity/ProgressBar.hxx
    ../Entity/HierarchyEntity.hh
    ../Game/Entity/Tank.hxx
    ../Entity/Geometries/CylinderGeometry.hxx
    ../Entity/Geometries/SphereGeometry.hxx
    ../Entity/Geometries/MyTerrainGeometry.hxx
    ../Entity/Entities/Terrain.hxx
    ../Game/Entity/Star.hxx
    ../Shader/LoadedShaders.hxx
    ../Entity/Geometries/Geometries.hxx
    ../Game/Entity/SupremeLeader.hxx
    ../Game/Entity/Tree.hxx
    ../Texture/LoadedTextures.hxx
    ../Game/Entity/GasStation.hxx
    ../Game/Entity/SpaceStoneMonster.hxx
    ../Game/Entity/SpaceSnail.hxx
    ../Game/Entity/SpaceJet.hxx
    ../Game/Entity/SpaceDragon.hxx
    ../Game/Entity/Weapons/Bullet.hxx
    ../Game/Entity/Supply.hxx
    ../World/MainMenu.hxx
    ../World/Pause.hxx
    ../World/GamePage.hxx
    ../Game/Entity/Save.hxx
    ../World/GameOver.hxx
    ../World/Instructions.hxx
    ../Entity/Entities/Atom.hxx
    ../Entity/Entities/SphereExplosion.hxx
)
 
set(SRCS
    ../Camera/Camera.cc
    ../Display/GameDisplay.cc
    ../Entity/Entity.cc
    ../Entity/Geometry.cc
    ../Entity/Geometries/QuadGeometry.cxx
    ../Shader/Shader.cc
    ../Texture/Texture.cc
    ../World/GameWorld.cc
    ../Main/Main.cc
    ../World/BasicWorld.cxx
    ../Entity/Label.cc
    ../Entity/ProgressBar.cxx
    ../Entity/HierarchyEntity.cc
    ../Game/Entity/Tank.cxx
    ../Entity/Geometries/CylinderGeometry.cxx
    ../Entity/Geometries/SphereGeometry.cxx
    ../Entity/Geometries/MyTerrainGeometry.cxx
    ../Entity/Entities/Terrain.cxx
    ../Game/Entity/Star.cxx
    ../Shader/LoadedShader.cxx
    ../Entity/Geometries/Geometries.cxx
    ../Game/Entity/SupremeLeader.cxx
    ../Game/Entity/Tree.cxx
    ../Texture/LoadedTextures.cxx
    ../Game/Entity/GasStation.cxx
    ../Game/Entity/SpaceStoneMonster.cxx
    ../Game/Entity/SpaceSnail.cxx
    ../Game/Entity/SpaceJet.cxx
    ../Game/Entity/SpaceDragon.cxx
    ../Game/Entity/Weapons/Bullet.cxx
    ../Game/Entity/Supply.cxx
    ../World/MainMenu.cxx
    ../World/Pause.cxx
    ../World/GamePage.cxx
    ../Game/Entity/Save.cxx
    ../World/GameOver.cxx
    ../World/Instructions.cxx
    ../Entity/Entities/Atom.cxx
    ../Entity/Entities/SphereExplosion.cxx
)



# Add executable based on the source files
add_executable(${PROJ_NAME} ${HDRS} ${SRCS})

# Require OpenGL library
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJ_NAME} ${OPENGL_gl_LIBRARY})

# Other libraries needed
set(LIBRARY_PATH C:/Program\ Files/Libraries/Libraries)
include_directories(${LIBRARY_PATH}/include)
if(NOT WIN32)
    find_library(GLEW_LIBRARY GLEW)
    find_library(GLFW_LIBRARY glfw)
    find_library(SOIL_LIBRARY SOIL)
elseif(WIN32)
    find_library(GLEW_LIBRARY glew32s HINTS ${LIBRARY_PATH}/lib)
    find_library(GLFW_LIBRARY glfw3 HINTS ${LIBRARY_PATH}/lib)
    find_library(SOIL_LIBRARY SOIL HINTS ${LIBRARY_PATH}/lib)
endif(NOT WIN32)
target_link_libraries(${PROJ_NAME} ${GLEW_LIBRARY})
target_link_libraries(${PROJ_NAME} ${GLFW_LIBRARY})
target_link_libraries(${PROJ_NAME} ${SOIL_LIBRARY})

# The rules here are specific to Windows Systems
if(WIN32)
    # Avoid ZERO_CHECK target in Visual Studio
    set(CMAKE_SUPPRESS_REGENERATION TRUE)
 
    # This will use the proper libraries in debug mode in Visual Studio
    set_target_properties(${PROJ_NAME} PROPERTIES DEBUG_POSTFIX _d)
endif(WIN32)
