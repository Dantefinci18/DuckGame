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
CMAKE_SOURCE_DIR = /home/mati/Escritorio/tp_grupal/DuckGame/cliente

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mati/Escritorio/tp_grupal/DuckGame/cliente/build

# Include any dependencies generated for this target.
include CMakeFiles/sdldemo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/sdldemo.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/sdldemo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sdldemo.dir/flags.make

CMakeFiles/sdldemo.dir/Sdl/SdlException.cpp.o: CMakeFiles/sdldemo.dir/flags.make
CMakeFiles/sdldemo.dir/Sdl/SdlException.cpp.o: /home/mati/Escritorio/tp_grupal/DuckGame/cliente/Sdl/SdlException.cpp
CMakeFiles/sdldemo.dir/Sdl/SdlException.cpp.o: CMakeFiles/sdldemo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/mati/Escritorio/tp_grupal/DuckGame/cliente/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sdldemo.dir/Sdl/SdlException.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sdldemo.dir/Sdl/SdlException.cpp.o -MF CMakeFiles/sdldemo.dir/Sdl/SdlException.cpp.o.d -o CMakeFiles/sdldemo.dir/Sdl/SdlException.cpp.o -c /home/mati/Escritorio/tp_grupal/DuckGame/cliente/Sdl/SdlException.cpp

CMakeFiles/sdldemo.dir/Sdl/SdlException.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/sdldemo.dir/Sdl/SdlException.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mati/Escritorio/tp_grupal/DuckGame/cliente/Sdl/SdlException.cpp > CMakeFiles/sdldemo.dir/Sdl/SdlException.cpp.i

CMakeFiles/sdldemo.dir/Sdl/SdlException.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/sdldemo.dir/Sdl/SdlException.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mati/Escritorio/tp_grupal/DuckGame/cliente/Sdl/SdlException.cpp -o CMakeFiles/sdldemo.dir/Sdl/SdlException.cpp.s

CMakeFiles/sdldemo.dir/Sdl/SdlWindow.cpp.o: CMakeFiles/sdldemo.dir/flags.make
CMakeFiles/sdldemo.dir/Sdl/SdlWindow.cpp.o: /home/mati/Escritorio/tp_grupal/DuckGame/cliente/Sdl/SdlWindow.cpp
CMakeFiles/sdldemo.dir/Sdl/SdlWindow.cpp.o: CMakeFiles/sdldemo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/mati/Escritorio/tp_grupal/DuckGame/cliente/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/sdldemo.dir/Sdl/SdlWindow.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sdldemo.dir/Sdl/SdlWindow.cpp.o -MF CMakeFiles/sdldemo.dir/Sdl/SdlWindow.cpp.o.d -o CMakeFiles/sdldemo.dir/Sdl/SdlWindow.cpp.o -c /home/mati/Escritorio/tp_grupal/DuckGame/cliente/Sdl/SdlWindow.cpp

CMakeFiles/sdldemo.dir/Sdl/SdlWindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/sdldemo.dir/Sdl/SdlWindow.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mati/Escritorio/tp_grupal/DuckGame/cliente/Sdl/SdlWindow.cpp > CMakeFiles/sdldemo.dir/Sdl/SdlWindow.cpp.i

CMakeFiles/sdldemo.dir/Sdl/SdlWindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/sdldemo.dir/Sdl/SdlWindow.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mati/Escritorio/tp_grupal/DuckGame/cliente/Sdl/SdlWindow.cpp -o CMakeFiles/sdldemo.dir/Sdl/SdlWindow.cpp.s

# Object files for target sdldemo
sdldemo_OBJECTS = \
"CMakeFiles/sdldemo.dir/Sdl/SdlException.cpp.o" \
"CMakeFiles/sdldemo.dir/Sdl/SdlWindow.cpp.o"

# External object files for target sdldemo
sdldemo_EXTERNAL_OBJECTS =

libsdldemo.a: CMakeFiles/sdldemo.dir/Sdl/SdlException.cpp.o
libsdldemo.a: CMakeFiles/sdldemo.dir/Sdl/SdlWindow.cpp.o
libsdldemo.a: CMakeFiles/sdldemo.dir/build.make
libsdldemo.a: CMakeFiles/sdldemo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/mati/Escritorio/tp_grupal/DuckGame/cliente/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libsdldemo.a"
	$(CMAKE_COMMAND) -P CMakeFiles/sdldemo.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sdldemo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sdldemo.dir/build: libsdldemo.a
.PHONY : CMakeFiles/sdldemo.dir/build

CMakeFiles/sdldemo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sdldemo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sdldemo.dir/clean

CMakeFiles/sdldemo.dir/depend:
	cd /home/mati/Escritorio/tp_grupal/DuckGame/cliente/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mati/Escritorio/tp_grupal/DuckGame/cliente /home/mati/Escritorio/tp_grupal/DuckGame/cliente /home/mati/Escritorio/tp_grupal/DuckGame/cliente/build /home/mati/Escritorio/tp_grupal/DuckGame/cliente/build /home/mati/Escritorio/tp_grupal/DuckGame/cliente/build/CMakeFiles/sdldemo.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/sdldemo.dir/depend
