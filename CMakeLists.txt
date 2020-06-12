#[[
cmake_minimum_required(VERSION 3.6)

set(PROJECT_NAME game)
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp)

set(SFML_DIR "${PROJECT_SOURCE_DIR}/SFML-2.5.1/lib/cmake/SFML")
set(CMAKE_MODULE_PATH "${SFML_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 COMPONENTS system window graphics audio network REQUIRED)

include_directories(${SFML_INCLUDE_DIR})
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
]]

cmake_minimum_required(VERSION 3.1)

set (PROJECT_NAME game)
project(${PROJECT_NAME})
## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "${PROJECT_SOURCE_DIR}/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics audio network REQUIRED)
add_executable(${PROJECT_NAME} source/main.cpp source/autosimulator.cpp source/autosimulator.h source/controller/inputController.cpp source/controller/inputController.h source/models.cpp source/models.h source/controller/manipulatorData.h)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio sfml-network)

set(GCC_COVERAGE_COMPILE_FLAGS "-g -Wall -Wextra -Weffc++ -Wc++0x-compat -Wc++11-compat \
 -Wc++14-compat -Waggressive-loop-optimizations -Walloc-zero -Walloca -Walloca-larger-than=8192\
 -Warray-bounds -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion\
 -Wctor-dtor-privacy -Wdangling-else -Wduplicated-branches -Wempty-body -Wfloat-equal -Wformat-nonliteral\
 -Wformat-security -Wformat-signedness -Wformat=2 -Wformat-overflow=2 -Wformat-truncation=2 -Winline\
 -Wlarger-than=8192 -Wvla-larger-than=8192 -Wlogical-op -Wmissing-declarations -Wnon-virtual-dtor -Wopenmp-simd\
 -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wrestrict -Wshadow -Wsign-promo -Wstack-usage=8192\
 -Wstrict-null-sentinel -Wstrict-overflow=2 -Wstringop-overflow=4 -Wsuggest-attribute=noreturn -Wsuggest-final-types\
 -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wvariadic-macros\
 -Wno-literal-suffix -Wno-missing-field-initializers -Wnarrowing -Wno-old-style-cast -Wvarargs -fcheck-new\
 -fsized-deallocation -fstack-check -fstrict-overflow -fchkp-first-field-has-own-bounds\
 -fchkp-narrow-to-innermost-array -flto-odr-type-merging")