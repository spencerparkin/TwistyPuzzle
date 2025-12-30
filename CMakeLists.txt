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
    Source/Bagua.cpp
    Source/Bagua.h
    Source/BauhiniaDodecahedron.cpp
    Source/BauhiniaDodecahedron.h
    Source/Bubbloid3x3x3.cpp
    Source/Bubbloid3x3x3.h
    Source/Bubbloid4x4x5.cpp
    Source/Bubbloid4x4x5.h
    Source/Canvas.cpp
    Source/Canvas.h
    Source/CornerTurningOctahedron.cpp
    Source/CornerTurningOctahedron.h
    Source/Cuboid3x3x3.cpp
    Source/Cuboid3x3x3.h
    Source/Cuboid3x3x3Base.cpp
    Source/Cuboid3x3x3Base.h
    Source/CurvyCopter.cpp
    Source/CurvyCopter.h
    Source/CurvyCopter3.cpp
    Source/CurvyCopter3.h
    Source/CurvyCopterBase.cpp
    Source/CurvyCopterBase.h
    Source/Dogic.cpp
    Source/Dogic.h
    Source/DreidelCube.cpp
    Source/DreidelCube.h
    Source/FaceTurningOctahedron.cpp
    Source/FaceTurningOctahedron.h
    Source/FisherCube.cpp
    Source/FisherCube.h
    Source/FlowerBox.cpp
    Source/FlowerBox.h
    Source/FlowerCopter.cpp
    Source/FlowerCopter.h
    Source/Frame.cpp
    Source/Frame.h
    Source/GLRenderer.cpp
    Source/GLRenderer.h
    Source/Gem6.cpp
    Source/Gem6.h
    Source/Gem8.cpp
    Source/Gem8.h
    Source/HtmlFrame.cpp
    Source/HtmlFrame.h
    Source/IcosahedronSkewb.cpp
    Source/IcosahedronSkewb.h
    Source/LatchCube.cpp
    Source/LatchCube.h
    Source/MasterPyraminx.cpp
    Source/MasterPyraminx.h
    Source/Megaminx.cpp
    Source/Megaminx.h
    Source/MixupCube.cpp
    Source/MixupCube.h
    Source/PentacleCube.cpp
    Source/PentacleCube.h
    Source/Pyraminx.cpp
    Source/Pyraminx.h
    Source/PyraminxBase.cpp
    Source/PyraminxBase.h
    Source/Rubiks2x2x2.cpp
    Source/Rubiks2x2x2.h
    Source/Rubiks2x2x3.cpp
    Source/Rubiks2x2x3.h
    Source/Rubiks2x3x3.cpp
    Source/Rubiks2x3x3.h
    Source/Rubiks3x3x3.cpp
    Source/Rubiks3x3x3.h
    Source/ShaderProgram.cpp
    Source/ShaderProgram.h
    Source/Skewb.cpp
    Source/Skewb.h
    Source/Skewb2.cpp
    Source/Skewb2.h
    Source/SkewbDiamond.cpp
    Source/SkewbDiamond.h
    Source/SkewbUltimate.cpp
    Source/SkewbUltimate.h
    Source/SquareOne.cpp
    Source/SquareOne.h
    Source/TwistyPuzzle.cpp
    Source/TwistyPuzzle.h
    Source/wxTimeKeeper.cpp
    Source/wxTimeKeeper.h
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

target_compile_definitions(TwistyPuzzle PRIVATE LINUX)