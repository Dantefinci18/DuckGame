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

# Include any dependencies generated for this target.
include _deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include _deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/compiler_depend.make

# Include the progress variables for this target.
include _deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/progress.make

# Include the compile flags for this target's objects.
include _deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/flags.make

_deps/yaml-cpp-build/util/yaml-cpp-sandbox_autogen/timestamp: /usr/lib/qt5/bin/moc
_deps/yaml-cpp-build/util/yaml-cpp-sandbox_autogen/timestamp: /usr/lib/qt5/bin/uic
_deps/yaml-cpp-build/util/yaml-cpp-sandbox_autogen/timestamp: _deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/echitosto/Documents/GitHub/DuckGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target yaml-cpp-sandbox"
	cd /home/echitosto/Documents/GitHub/DuckGame/build/_deps/yaml-cpp-build/util && /usr/bin/cmake -E cmake_autogen /home/echitosto/Documents/GitHub/DuckGame/build/_deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox_autogen.dir/AutogenInfo.json Debug
	cd /home/echitosto/Documents/GitHub/DuckGame/build/_deps/yaml-cpp-build/util && /usr/bin/cmake -E touch /home/echitosto/Documents/GitHub/DuckGame/build/_deps/yaml-cpp-build/util/yaml-cpp-sandbox_autogen/timestamp

_deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/yaml-cpp-sandbox_autogen/mocs_compilation.cpp.o: _deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/flags.make
_deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/yaml-cpp-sandbox_autogen/mocs_compilation.cpp.o: _deps/yaml-cpp-build/util/yaml-cpp-sandbox_autogen/mocs_compilation.cpp
_deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/yaml-cpp-sandbox_autogen/mocs_compilation.cpp.o: _deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/echitosto/Documents/GitHub/DuckGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object _deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/yaml-cpp-sandbox_autogen/mocs_compilation.cpp.o"
	cd /home/echitosto/Documents/GitHub/DuckGame/build/_deps/yaml-cpp-build/util && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT _deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/yaml-cpp-sandbox_autogen/mocs_compilation.cpp.o -MF CMakeFiles/yaml-cpp-sandbox.dir/yaml-cpp-sandbox_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/yaml-cpp-sandbox.dir/yaml-cpp-sandbox_autogen/mocs_compilation.cpp.o -c /home/echitosto/Documents/GitHub/DuckGame/build/_deps/yaml-cpp-build/util/yaml-cpp-sandbox_autogen/mocs_compilation.cpp

_deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/yaml-cpp-sandbox_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/yaml-cpp-sandbox.dir/yaml-cpp-sandbox_autogen/mocs_compilation.cpp.i"
	cd /home/echitosto/Documents/GitHub/DuckGame/build/_deps/yaml-cpp-build/util && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/echitosto/Documents/GitHub/DuckGame/build/_deps/yaml-cpp-build/util/yaml-cpp-sandbox_autogen/mocs_compilation.cpp > CMakeFiles/yaml-cpp-sandbox.dir/yaml-cpp-sandbox_autogen/mocs_compilation.cpp.i

_deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/yaml-cpp-sandbox_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/yaml-cpp-sandbox.dir/yaml-cpp-sandbox_autogen/mocs_compilation.cpp.s"
	cd /home/echitosto/Documents/GitHub/DuckGame/build/_deps/yaml-cpp-build/util && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/echitosto/Documents/GitHub/DuckGame/build/_deps/yaml-cpp-build/util/yaml-cpp-sandbox_autogen/mocs_compilation.cpp -o CMakeFiles/yaml-cpp-sandbox.dir/yaml-cpp-sandbox_autogen/mocs_compilation.cpp.s

_deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.o: _deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/flags.make
_deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.o: _deps/yaml-cpp-src/util/sandbox.cpp
_deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.o: _deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/echitosto/Documents/GitHub/DuckGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object _deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.o"
	cd /home/echitosto/Documents/GitHub/DuckGame/build/_deps/yaml-cpp-build/util && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT _deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.o -MF CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.o.d -o CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.o -c /home/echitosto/Documents/GitHub/DuckGame/build/_deps/yaml-cpp-src/util/sandbox.cpp

_deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.i"
	cd /home/echitosto/Documents/GitHub/DuckGame/build/_deps/yaml-cpp-build/util && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/echitosto/Documents/GitHub/DuckGame/build/_deps/yaml-cpp-src/util/sandbox.cpp > CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.i

_deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.s"
	cd /home/echitosto/Documents/GitHub/DuckGame/build/_deps/yaml-cpp-build/util && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/echitosto/Documents/GitHub/DuckGame/build/_deps/yaml-cpp-src/util/sandbox.cpp -o CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.s

# Object files for target yaml-cpp-sandbox
yaml__cpp__sandbox_OBJECTS = \
"CMakeFiles/yaml-cpp-sandbox.dir/yaml-cpp-sandbox_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.o"

# External object files for target yaml-cpp-sandbox
yaml__cpp__sandbox_EXTERNAL_OBJECTS =

_deps/yaml-cpp-build/util/sandbox: _deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/yaml-cpp-sandbox_autogen/mocs_compilation.cpp.o
_deps/yaml-cpp-build/util/sandbox: _deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/sandbox.cpp.o
_deps/yaml-cpp-build/util/sandbox: _deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/build.make
_deps/yaml-cpp-build/util/sandbox: _deps/yaml-cpp-build/libyaml-cppd.so.0.8.0
_deps/yaml-cpp-build/util/sandbox: _deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/echitosto/Documents/GitHub/DuckGame/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable sandbox"
	cd /home/echitosto/Documents/GitHub/DuckGame/build/_deps/yaml-cpp-build/util && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/yaml-cpp-sandbox.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
_deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/build: _deps/yaml-cpp-build/util/sandbox
.PHONY : _deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/build

_deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/clean:
	cd /home/echitosto/Documents/GitHub/DuckGame/build/_deps/yaml-cpp-build/util && $(CMAKE_COMMAND) -P CMakeFiles/yaml-cpp-sandbox.dir/cmake_clean.cmake
.PHONY : _deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/clean

_deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/depend: _deps/yaml-cpp-build/util/yaml-cpp-sandbox_autogen/timestamp
	cd /home/echitosto/Documents/GitHub/DuckGame/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/echitosto/Documents/GitHub/DuckGame /home/echitosto/Documents/GitHub/DuckGame/build/_deps/yaml-cpp-src/util /home/echitosto/Documents/GitHub/DuckGame/build /home/echitosto/Documents/GitHub/DuckGame/build/_deps/yaml-cpp-build/util /home/echitosto/Documents/GitHub/DuckGame/build/_deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : _deps/yaml-cpp-build/util/CMakeFiles/yaml-cpp-sandbox.dir/depend

