# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.9.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.9.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Woz4tetra/Documents/Code/ratslam

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Woz4tetra/Documents/Code/ratslam/build

# Include any dependencies generated for this target.
include CMakeFiles/pyratslam.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pyratslam.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pyratslam.dir/flags.make

CMakeFiles/pyratslam.dir/src/pyratslam/pyratslam.cpp.o: CMakeFiles/pyratslam.dir/flags.make
CMakeFiles/pyratslam.dir/src/pyratslam/pyratslam.cpp.o: ../src/pyratslam/pyratslam.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Woz4tetra/Documents/Code/ratslam/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pyratslam.dir/src/pyratslam/pyratslam.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pyratslam.dir/src/pyratslam/pyratslam.cpp.o -c /Users/Woz4tetra/Documents/Code/ratslam/src/pyratslam/pyratslam.cpp

CMakeFiles/pyratslam.dir/src/pyratslam/pyratslam.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pyratslam.dir/src/pyratslam/pyratslam.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Woz4tetra/Documents/Code/ratslam/src/pyratslam/pyratslam.cpp > CMakeFiles/pyratslam.dir/src/pyratslam/pyratslam.cpp.i

CMakeFiles/pyratslam.dir/src/pyratslam/pyratslam.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pyratslam.dir/src/pyratslam/pyratslam.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Woz4tetra/Documents/Code/ratslam/src/pyratslam/pyratslam.cpp -o CMakeFiles/pyratslam.dir/src/pyratslam/pyratslam.cpp.s

CMakeFiles/pyratslam.dir/src/pyratslam/pyratslam.cpp.o.requires:

.PHONY : CMakeFiles/pyratslam.dir/src/pyratslam/pyratslam.cpp.o.requires

CMakeFiles/pyratslam.dir/src/pyratslam/pyratslam.cpp.o.provides: CMakeFiles/pyratslam.dir/src/pyratslam/pyratslam.cpp.o.requires
	$(MAKE) -f CMakeFiles/pyratslam.dir/build.make CMakeFiles/pyratslam.dir/src/pyratslam/pyratslam.cpp.o.provides.build
.PHONY : CMakeFiles/pyratslam.dir/src/pyratslam/pyratslam.cpp.o.provides

CMakeFiles/pyratslam.dir/src/pyratslam/pyratslam.cpp.o.provides.build: CMakeFiles/pyratslam.dir/src/pyratslam/pyratslam.cpp.o


# Object files for target pyratslam
pyratslam_OBJECTS = \
"CMakeFiles/pyratslam.dir/src/pyratslam/pyratslam.cpp.o"

# External object files for target pyratslam
pyratslam_EXTERNAL_OBJECTS =

pyratslam.so: CMakeFiles/pyratslam.dir/src/pyratslam/pyratslam.cpp.o
pyratslam.so: CMakeFiles/pyratslam.dir/build.make
pyratslam.so: /usr/local/lib/libboost_serialization-mt.dylib
pyratslam.so: /usr/local/lib/libboost_date_time-mt.dylib
pyratslam.so: /usr/local/lib/libboost_python3-mt.dylib
pyratslam.so: /usr/local/Frameworks/Python.framework/Versions/3.6/lib/libpython3.6m.dylib
pyratslam.so: libratslam.dylib
pyratslam.so: /usr/local/lib/libboost_serialization-mt.dylib
pyratslam.so: /usr/local/lib/libboost_date_time-mt.dylib
pyratslam.so: /usr/local/lib/libboost_python3-mt.dylib
pyratslam.so: /usr/local/Frameworks/Python.framework/Versions/3.6/lib/libpython3.6m.dylib
pyratslam.so: CMakeFiles/pyratslam.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Woz4tetra/Documents/Code/ratslam/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared module pyratslam.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pyratslam.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pyratslam.dir/build: pyratslam.so

.PHONY : CMakeFiles/pyratslam.dir/build

CMakeFiles/pyratslam.dir/requires: CMakeFiles/pyratslam.dir/src/pyratslam/pyratslam.cpp.o.requires

.PHONY : CMakeFiles/pyratslam.dir/requires

CMakeFiles/pyratslam.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pyratslam.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pyratslam.dir/clean

CMakeFiles/pyratslam.dir/depend:
	cd /Users/Woz4tetra/Documents/Code/ratslam/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Woz4tetra/Documents/Code/ratslam /Users/Woz4tetra/Documents/Code/ratslam /Users/Woz4tetra/Documents/Code/ratslam/build /Users/Woz4tetra/Documents/Code/ratslam/build /Users/Woz4tetra/Documents/Code/ratslam/build/CMakeFiles/pyratslam.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pyratslam.dir/depend

