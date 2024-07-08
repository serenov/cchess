# cmake_minimum_required(VERSION 3.10)

# project(cchess)

# include_directories(./includes)

# # Add the source files
# set(SOURCE_FILES
#     src/interface.c
#     src/engine.c
#     src/bitboards.c
#     src/magicBoards.c
#     src/moves.c
#     src/piece.c
# )

# # Specify the executable and the source files it depends on
# add_executable(${PROJECT_NAME} ${SOURCE_FILES})

cmake_minimum_required(VERSION 3.10)
project(cchess VERSION 1.0.0)

set(SOURCE_FILES
    src/engine.c
    src/bitboards.c
    src/magicBoards.c
    src/moves.c
    src/piece.c
)

# Specify the library target
add_library(cchess SHARED ${SOURCE_FILES})

# Include directories for the library
target_include_directories(cchess PUBLIC ${PROJECT_SOURCE_DIR}/includes)

# Set the version for the library
set_target_properties(cchess PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION 1)

# Optionally specify the install locations
install(TARGETS cchess
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)


file(GLOB HEADERS
    "${PROJECT_SOURCE_DIR}/includes/*.h"
)


install(FILES ${HEADERS} DESTINATION include/cchess)