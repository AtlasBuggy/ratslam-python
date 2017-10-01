cmake_minimum_required(VERSION 2.8)

project(pyratslam)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(PythonInterp 3.5 REQUIRED)
find_package(PythonLibs 3.5 REQUIRED)

find_package(Boost COMPONENTS python3 REQUIRED)
IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_definitions( "-DHAS_BOOST" )
ENDIF()

set(RATSLAM_DIR, "../../../build")
include_directories("${RATSLAM_DIR}")

message(STATUS "ratslam \"${RATSLAM_DIR}\"")

include_directories(${Boost_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
link_libraries(${Boost_LIBRARIES} ${PYTHON_LIBRARIES})

python_add_module(pyratslam pyratslam.cpp)

include_directories(src/ratslam src/gri)
target_link_libraries(pyratslam ratslam)
