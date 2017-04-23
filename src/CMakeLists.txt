set(PROJECT cmd_exec)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE SOURCES
        "*.h"
        "*.cpp"
        )
add_executable(${PROJECT} ${SOURCES})