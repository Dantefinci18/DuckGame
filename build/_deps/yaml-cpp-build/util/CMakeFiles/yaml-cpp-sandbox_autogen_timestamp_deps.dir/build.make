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
CMAKE_SOURCE_DIR = /home/echitosto/Documents/GitHub/DuckGame

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/echitosto/Documents/GitHub/DuckGame/build

# Utility rule file for yaml-cpp-sandbox_autogen_timestamp_deps.

# Include any custom commands dependencies for this target.
include _deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox_autogen_timestamp_deps.dir/compiler_depend.make

# Include the progress variables for this target.
include _deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox_autogen_timestamp_deps.dir/progress.make

_deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox_autogen_timestamp_deps: /usr/lib/qt5/bin/moc
_deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox_autogen_timestamp_deps: /usr/lib/qt5/bin/uic
_deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox_autogen_timestamp_deps: _deps/yaml-cpp-build/libyaml-cppd.a

yaml-cpp-sandbox_autogen_timestamp_deps: _deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox_autogen_timestamp_deps
yaml-cpp-sandbox_autogen_timestamp_deps: _deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox_autogen_timestamp_deps.dir/build.make
.PHONY : yaml-cpp-sandbox_autogen_timestamp_deps

# Rule to build all files generated by this target.
_deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox_autogen_timestamp_deps.dir/build: yaml-cpp-sandbox_autogen_timestamp_deps
.PHONY : _deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox_autogen_timestamp_deps.dir/build

_deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox_autogen_timestamp_deps.dir/clean:
	cd /home/echitosto/Documents/GitHub/DuckGame/build/_deps/yaml-cpp-build/util && $(CMAKE_COMMAND) -P CMakeFiles/yaml-cpp-sandbox_autogen_timestamp_deps.dir/cmake_clean.cmake
.PHONY : _deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox_autogen_timestamp_deps.dir/clean

_deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox_autogen_timestamp_deps.dir/depend:
	cd /home/echitosto/Documents/GitHub/DuckGame/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/echitosto/Documents/GitHub/DuckGame /home/echitosto/Documents/GitHub/DuckGame/build/_deps/yaml-cpp-src/util /home/echitosto/Documents/GitHub/DuckGame/build /home/echitosto/Documents/GitHub/DuckGame/build/_deps/yaml-cpp-build/util /home/echitosto/Documents/GitHub/DuckGame/build/_deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox_autogen_timestamp_deps.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : _deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox_autogen_timestamp_deps.dir/depend

