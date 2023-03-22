cmake_minimum_required(VERSION 3.19)

project(SFML-Chess VERSION 1.0)

include(FetchContent)

set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
	SFML
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG 2.5.1
)

set(SFML_BUILD_EXAMPLES OFF)
set(SFML_BUILD_DOC OFF)
option(SFML_BUILD_AUDIO "Build audio" OFF)
option(SFML_BUILD_NETWORK "Build network" OFF)
FetchContent_MakeAvailable(SFML)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include_directories("SFML-Chess/src")

set(SOURCE
    "SFML-Chess/src/Bishop.cpp" 
    "SFML-Chess/src/Board.cpp" 
    "SFML-Chess/src/Game.cpp" 
    "SFML-Chess/src/GameState.cpp" 
    "SFML-Chess/src/Highlights.cpp" 
    "SFML-Chess/src/King.cpp" 
    "SFML-Chess/src/Knight.cpp" 
    "SFML-Chess/src/main.cpp" 
    "SFML-Chess/src/Pawn.cpp" 
    "SFML-Chess/src/Piece.cpp" 
    "SFML-Chess/src/PiecesBuffer.cpp" 
    "SFML-Chess/src/PromoteOption.cpp" 
    "SFML-Chess/src/Queen.cpp" 
    "SFML-Chess/src/Rook.cpp" 
)

add_executable(
	${PROJECT_NAME} ${SOURCE}
)

target_link_libraries(
	${PROJECT_NAME}
	sfml-graphics
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
    "${CMAKE_CURRENT_SOURCE_DIR}\\SFML-Chess\\assets" 
    "${PROJECT_BINARY_DIR}\\$(Configuration)\\assets" 
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/SFML-Chess/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
