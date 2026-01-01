# CMakeLists.txt for TwistyPuzzle project.

cmake_minimum_required(VERSION 3.27)

project(TwistyPuzzle)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Bin)

add_subdirectory(ThirdParty/3DMath)
add_subdirectory(ThirdParty/FontSystem)
add_subdirectory(ThirdParty/PermutationGroup)

find_package(Freetype REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(wxWidgets REQUIRED COMPONENTS core base xml html gl)

if(wxWidgets_USE_FILE)
    include(${wxWidgets_USE_FILE})
endif()

set(TWISTY_PUZZLE_SOURCES
    Source/Application.cpp
    Source/Application.h
    Source/Canvas.cpp
    Source/Canvas.h
    Source/Frame.cpp
    Source/Frame.h
    Source/HtmlFrame.cpp
    Source/HtmlFrame.h
    Source/ShaderProgram.cpp
    Source/ShaderProgram.h
    Source/TwistyPuzzle.cpp
    Source/TwistyPuzzle.h
    Source/wxTimeKeeper.cpp
    Source/wxTimeKeeper.h
    Source/GLRenderer.cpp
    Source/GLRenderer.h
    Source/Puzzles/Bagua.cpp
    Source/Puzzles/Bagua.h
    Source/Puzzles/BauhiniaDodecahedron.cpp
    Source/Puzzles/BauhiniaDodecahedron.h
    Source/Puzzles/Bubbloid3x3x3.cpp
    Source/Puzzles/Bubbloid3x3x3.h
    Source/Puzzles/Bubbloid4x4x5.cpp
    Source/Puzzles/Bubbloid4x4x5.h
    Source/Puzzles/CornerTurningOctahedron.cpp
    Source/Puzzles/CornerTurningOctahedron.h
    Source/Puzzles/Cuboid3x3x3.cpp
    Source/Puzzles/Cuboid3x3x3.h
    Source/Puzzles/Cuboid3x3x3Base.cpp
    Source/Puzzles/Cuboid3x3x3Base.h
    Source/Puzzles/CurvyCopter.cpp
    Source/Puzzles/CurvyCopter.h
    Source/Puzzles/CurvyCopter3.cpp
    Source/Puzzles/CurvyCopter3.h
    Source/Puzzles/CurvyCopterBase.cpp
    Source/Puzzles/CurvyCopterBase.h
    Source/Puzzles/Dogic.cpp
    Source/Puzzles/Dogic.h
    Source/Puzzles/DreidelCube.cpp
    Source/Puzzles/DreidelCube.h
    Source/Puzzles/FaceTurningOctahedron.cpp
    Source/Puzzles/FaceTurningOctahedron.h
    Source/Puzzles/FisherCube.cpp
    Source/Puzzles/FisherCube.h
    Source/Puzzles/FlowerBox.cpp
    Source/Puzzles/FlowerBox.h
    Source/Puzzles/FlowerCopter.cpp
    Source/Puzzles/FlowerCopter.h
    Source/Puzzles/Gem6.cpp
    Source/Puzzles/Gem6.h
    Source/Puzzles/Gem8.cpp
    Source/Puzzles/Gem8.h
    Source/Puzzles/IcosahedronSkewb.cpp
    Source/Puzzles/IcosahedronSkewb.h
    Source/Puzzles/LatchCube.cpp
    Source/Puzzles/LatchCube.h
    Source/Puzzles/MasterPyraminx.cpp
    Source/Puzzles/MasterPyraminx.h
    Source/Puzzles/Megaminx.cpp
    Source/Puzzles/Megaminx.h
    Source/Puzzles/MixupCube.cpp
    Source/Puzzles/MixupCube.h
    Source/Puzzles/PentacleCube.cpp
    Source/Puzzles/PentacleCube.h
    Source/Puzzles/Pyraminx.cpp
    Source/Puzzles/Pyraminx.h
    Source/Puzzles/PyraminxBase.cpp
    Source/Puzzles/PyraminxBase.h
    Source/Puzzles/Rubiks2x2x2.cpp
    Source/Puzzles/Rubiks2x2x2.h
    Source/Puzzles/Rubiks2x2x3.cpp
    Source/Puzzles/Rubiks2x2x3.h
    Source/Puzzles/Rubiks2x3x3.cpp
    Source/Puzzles/Rubiks2x3x3.h
    Source/Puzzles/Rubiks3x3x3.cpp
    Source/Puzzles/Rubiks3x3x3.h
    Source/Puzzles/Skewb.cpp
    Source/Puzzles/Skewb.h
    Source/Puzzles/Skewb2.cpp
    Source/Puzzles/Skewb2.h
    Source/Puzzles/SkewbDiamond.cpp
    Source/Puzzles/SkewbDiamond.h
    Source/Puzzles/SkewbUltimate.cpp
    Source/Puzzles/SkewbUltimate.h
    Source/Puzzles/SquareOne.cpp
    Source/Puzzles/SquareOne.h
)

add_executable(TwistyPuzzle ${TWISTY_PUZZLE_SOURCES})

target_link_libraries(TwistyPuzzle PRIVATE
    ${wxWidgets_LIBRARIES}
    Freetype::Freetype
    OpenGL::GL
    OpenGL::GLU
    GLEW::GLEW
    PermGroup
    FontSystem
    3DMathLibrary
)

target_include_directories(TwistyPuzzle PRIVATE Source)

target_compile_definitions(TwistyPuzzle PRIVATE LINUX)