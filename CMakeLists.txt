cmake_minimum_required(VERSION 2.8)

project(scalc)

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -Wextra -g -std=c++14 -pedantic -pedantic-errors")
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Wextra -std=c++14 -pedantic -pedantic-errors -O3")

# build directories
set(CMAKE_BINARY_DIR build)
set(EXECUTABLE_OUTPUT_PATH bin)

# include and link directories
include_directories(include)

file(GLOB SOURCES src/*.cc)

#add_executable(test_parser test/test_parser.cc ${SOURCES})
#add_executable(test_popoperand test/test_popoperand.cc src/operand.cc)
add_executable(test_monomial test/test_monomial.cc src/monomial.cc)
#add_executable(scalc src/main/scalc.cc ${SOURCES})

#if (UNIX)
#    target_link_libraries(test_parser m)
#    target_link_libraries(scalc m)
#endif (UNIX)
