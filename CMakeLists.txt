cmake_minimum_required(VERSION 3.15)

project(nebrix)

set(CMAKE_CXX_STANDARD 20)

# List of source files for each target
set(NEBRIX_SOURCE_FILES
    src/main.cpp
    src/common.cpp
    src/lexer/lexer.cpp
    src/lexer/tokens.cpp
    # src/compiler/compiler.cpp
    # src/compiler/precedence.cpp
    # src/compiler/stmt/stmt.cpp
    # src/generation/gen.cpp
)

add_executable(nebrix ${NEBRIX_SOURCE_FILES})