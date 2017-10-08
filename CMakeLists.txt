cmake_minimum_required(VERSION 3.0)

project(ratslam-python)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(PythonInterp 3 REQUIRED)
find_package(PythonLibs 3 REQUIRED)

find_package(Boost COMPONENTS python3 REQUIRED)
IF (Boost_FOUND)
    include_directories("${Boost_INCLUDE_DIR}")
    add_definitions( "-DHAS_BOOST" )
ENDIF()

file(GLOB RATSLAM_INCLUDES src/ratslam/*.h src/ratslam/*.hpp)
file(COPY ${RATSLAM_INCLUDES} DESTINATION include)

include_directories(${CMAKE_BINARY_DIR}/include ${PYTHON_INCLUDE_DIRS})
link_libraries(${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
link_directories("${Boost_LIBRARY_DIRS}")
add_definitions(-DRATSLAM_EXPORTS)

# file(GLOB RATSLAM_SOURCE src/ratslam/*.cpp)
# add_library(ratslam SHARED RATSLAM_SOURCE)
add_library(
    ratslam SHARED src/ratslam/experience_map.cpp
    src/ratslam/posecell_network.cpp
    src/ratslam/visual_odometry.cpp
    src/ratslam/local_view_match.cpp
)

set(RATSLAM_LIBS ratslam)

python_add_module(pyratslam src/pyratslam/pyratslam.cpp)

include_directories(src/ratslam src/utils src/pyratslam/wrappers)
target_link_libraries(pyratslam ${RATSLAM_LIBS})
