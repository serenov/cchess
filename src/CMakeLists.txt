cmake_minimum_required(VERSION 3.10)
enable_testing()

project(cchess)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../includes)

# Add the source files
set(SOURCE_FILES
    interface.c
    engine.c
    bitboards.c
    magicBoards.c
    moves.c
    piece.c
)

# Specify the executable and the source files it depends on
add_executable(${PROJECT_NAME} ${SOURCE_FILES})