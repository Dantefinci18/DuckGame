# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mati/Escritorio/tp_grupal/DuckGame

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mati/Escritorio/tp_grupal/DuckGame/build

# Utility rule file for ContinuousConfigure.

# Include any custom commands dependencies for this target.
include _deps/yaml-cpp-build/CMakeFiles/ContinuousConfigure.dir/compiler_depend.make

# Include the progress variables for this target.
include _deps/yaml-cpp-build/CMakeFiles/ContinuousConfigure.dir/progress.make

_deps/yaml-cpp-build/CMakeFiles/ContinuousConfigure:
	cd /home/mati/Escritorio/tp_grupal/DuckGame/build/_deps/yaml-cpp-build && /usr/bin/ctest -D ContinuousConfigure

ContinuousConfigure: _deps/yaml-cpp-build/CMakeFiles/ContinuousConfigure
ContinuousConfigure: _deps/yaml-cpp-build/CMakeFiles/ContinuousConfigure.dir/build.make
.PHONY : ContinuousConfigure

# Rule to build all files generated by this target.
_deps/yaml-cpp-build/CMakeFiles/ContinuousConfigure.dir/build: ContinuousConfigure
.PHONY : _deps/yaml-cpp-build/CMakeFiles/ContinuousConfigure.dir/build

_deps/yaml-cpp-build/CMakeFiles/ContinuousConfigure.dir/clean:
	cd /home/mati/Escritorio/tp_grupal/DuckGame/build/_deps/yaml-cpp-build && $(CMAKE_COMMAND) -P CMakeFiles/ContinuousConfigure.dir/cmake_clean.cmake
.PHONY : _deps/yaml-cpp-build/CMakeFiles/ContinuousConfigure.dir/clean

_deps/yaml-cpp-build/CMakeFiles/ContinuousConfigure.dir/depend:
	cd /home/mati/Escritorio/tp_grupal/DuckGame/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mati/Escritorio/tp_grupal/DuckGame /home/mati/Escritorio/tp_grupal/DuckGame/build/_deps/yaml-cpp-src /home/mati/Escritorio/tp_grupal/DuckGame/build /home/mati/Escritorio/tp_grupal/DuckGame/build/_deps/yaml-cpp-build /home/mati/Escritorio/tp_grupal/DuckGame/build/_deps/yaml-cpp-build/CMakeFiles/ContinuousConfigure.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : _deps/yaml-cpp-build/CMakeFiles/ContinuousConfigure.dir/depend

