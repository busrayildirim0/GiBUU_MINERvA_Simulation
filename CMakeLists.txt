cmake_minimum_required(VERSION 3.16)
project(MixedSim)

find_package(Geant4 REQUIRED)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${Geant4_INCLUDE_DIRS}
)

file(GLOB sources src/*.cc)

add_executable(MixedSim ${sources})
target_link_libraries(MixedSim PRIVATE ${Geant4_LIBRARIES})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
