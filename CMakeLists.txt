cmake_minimum_required(VERSION 2.8)

project(ratslam)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(PythonInterp 3 REQUIRED)
find_package(PythonLibs 3 REQUIRED)

find_package(Boost COMPONENTS serialization date_time python3 REQUIRED)
IF (Boost_FOUND)
    include_directories("${Boost_INCLUDE_DIR}")
    add_definitions( "-DHAS_BOOST" )
ENDIF()
# find_package(OpenCV REQUIRED)
# find_package(Irrlicht REQUIRED)

file(GLOB RATSLAM_INCLUDES src/ratslam/*.h src/ratslam/*.hpp)
# file(GLOB RATSLAM_GRAPHICS_INCLUDES src/graphics/*.h src/graphics/*.hpp)
file(GLOB GRI_INCLUDES src/gri/*.h src/gri/*.hpp)
# file(COPY ${RATSLAM_INCLUDES};${RATSLAM_GRAPHICS_INCLUDES};${GRI_INCLUDES} DESTINATION include)
file(COPY ${RATSLAM_INCLUDES};${GRI_INCLUDES} DESTINATION include)

# include_directories("${IRRLICHT_INCLUDE_DIR}" "${Boost_INCLUDE_DIRS}" "${CMAKE_BINARY_DIR}/include")
include_directories(${CMAKE_BINARY_DIR}/include ${PYTHON_INCLUDE_DIRS})
link_libraries(${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
# link_directories("${IRRLICHT_LIBRARY}" "${Boost_LIBRARY_DIRS}")
link_directories("${Boost_LIBRARY_DIRS}")
# add_definitions(-DRATSLAM_EXPORTS -DRATSLAM_GRAPHICS_EXPORTS)
add_definitions(-DRATSLAM_EXPORTS)
add_library(ratslam SHARED src/ratslam/Experience_Map.cpp src/ratslam/Pose_Cell_Network.cpp src/ratslam/Visual_Template_Match.cpp src/ratslam/Ratslam.cpp)
target_link_libraries(ratslam ${Boost_DATE_TIME_LIBRARY})
# add_library(ratslam_graphics SHARED src/graphics/RatslamGraphics.cpp)
# target_link_libraries(ratslam_graphics Irrlicht ${OpenCV_LIBS})

# message(STATUS "opencv libs ${OpenCV_LIBS}")
# target_link_libraries(${OpenCV_LIBS})
# file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/include)
# file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# add_definitions("-Wall")

# message(STATUS "headers include ${RATSLAM_INCLUDES};${RATSLAM_GRAPHICS_INCLUDES}")
message(STATUS "headers include ${RATSLAM_INCLUDES}")
# set(RATSLAM_LIBS ratslam ratslam_graphics)
set(RATSLAM_LIBS ratslam)
# add_subdirectory(examples)

python_add_module(pyratslam src/pyratslam/pyratslam.cpp)

include_directories(src/ratslam src/gri)
target_link_libraries(pyratslam ${RATSLAM_LIBS})
