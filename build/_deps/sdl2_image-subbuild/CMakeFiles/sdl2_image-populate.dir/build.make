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
CMAKE_SOURCE_DIR = /home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-subbuild

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-subbuild

# Utility rule file for sdl2_image-populate.

# Include any custom commands dependencies for this target.
include CMakeFiles/sdl2_image-populate.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/sdl2_image-populate.dir/progress.make

CMakeFiles/sdl2_image-populate: CMakeFiles/sdl2_image-populate-complete

CMakeFiles/sdl2_image-populate-complete: sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-install
CMakeFiles/sdl2_image-populate-complete: sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-mkdir
CMakeFiles/sdl2_image-populate-complete: sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-download
CMakeFiles/sdl2_image-populate-complete: sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-update
CMakeFiles/sdl2_image-populate-complete: sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-patch
CMakeFiles/sdl2_image-populate-complete: sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-configure
CMakeFiles/sdl2_image-populate-complete: sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-build
CMakeFiles/sdl2_image-populate-complete: sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-install
CMakeFiles/sdl2_image-populate-complete: sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-test
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'sdl2_image-populate'"
	/usr/bin/cmake -E make_directory /home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-subbuild/CMakeFiles
	/usr/bin/cmake -E touch /home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-subbuild/CMakeFiles/sdl2_image-populate-complete
	/usr/bin/cmake -E touch /home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-subbuild/sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-done

sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-update:
.PHONY : sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-update

sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-build: sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "No build step for 'sdl2_image-populate'"
	cd /home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-build && /usr/bin/cmake -E echo_append
	cd /home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-build && /usr/bin/cmake -E touch /home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-subbuild/sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-build

sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-configure: sdl2_image-populate-prefix/tmp/sdl2_image-populate-cfgcmd.txt
sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-configure: sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "No configure step for 'sdl2_image-populate'"
	cd /home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-build && /usr/bin/cmake -E echo_append
	cd /home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-build && /usr/bin/cmake -E touch /home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-subbuild/sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-configure

sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-download: sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-gitinfo.txt
sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-download: sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Performing download step (git clone) for 'sdl2_image-populate'"
	cd /home/echitosto/Documents/GitHub/DuckGame/build/_deps && /usr/bin/cmake -P /home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-subbuild/sdl2_image-populate-prefix/tmp/sdl2_image-populate-gitclone.cmake
	cd /home/echitosto/Documents/GitHub/DuckGame/build/_deps && /usr/bin/cmake -E touch /home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-subbuild/sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-download

sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-install: sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-build
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "No install step for 'sdl2_image-populate'"
	cd /home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-build && /usr/bin/cmake -E echo_append
	cd /home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-build && /usr/bin/cmake -E touch /home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-subbuild/sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-install

sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Creating directories for 'sdl2_image-populate'"
	/usr/bin/cmake -Dcfgdir= -P /home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-subbuild/sdl2_image-populate-prefix/tmp/sdl2_image-populate-mkdirs.cmake
	/usr/bin/cmake -E touch /home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-subbuild/sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-mkdir

sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-patch: sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-patch-info.txt
sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-patch: sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-update
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "No patch step for 'sdl2_image-populate'"
	/usr/bin/cmake -E echo_append
	/usr/bin/cmake -E touch /home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-subbuild/sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-patch

sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-update:
.PHONY : sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-update

sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-test: sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-install
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "No test step for 'sdl2_image-populate'"
	cd /home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-build && /usr/bin/cmake -E echo_append
	cd /home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-build && /usr/bin/cmake -E touch /home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-subbuild/sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-test

sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-update: sdl2_image-populate-prefix/tmp/sdl2_image-populate-gitupdate.cmake
sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-update: sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-update-info.txt
sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-update: sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-download
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Performing update step for 'sdl2_image-populate'"
	cd /home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-src && /usr/bin/cmake -Dcan_fetch=YES -P /home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-subbuild/sdl2_image-populate-prefix/tmp/sdl2_image-populate-gitupdate.cmake

sdl2_image-populate: CMakeFiles/sdl2_image-populate
sdl2_image-populate: CMakeFiles/sdl2_image-populate-complete
sdl2_image-populate: sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-build
sdl2_image-populate: sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-configure
sdl2_image-populate: sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-download
sdl2_image-populate: sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-install
sdl2_image-populate: sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-mkdir
sdl2_image-populate: sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-patch
sdl2_image-populate: sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-test
sdl2_image-populate: sdl2_image-populate-prefix/src/sdl2_image-populate-stamp/sdl2_image-populate-update
sdl2_image-populate: CMakeFiles/sdl2_image-populate.dir/build.make
.PHONY : sdl2_image-populate

# Rule to build all files generated by this target.
CMakeFiles/sdl2_image-populate.dir/build: sdl2_image-populate
.PHONY : CMakeFiles/sdl2_image-populate.dir/build

CMakeFiles/sdl2_image-populate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sdl2_image-populate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sdl2_image-populate.dir/clean

CMakeFiles/sdl2_image-populate.dir/depend:
	cd /home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-subbuild && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-subbuild /home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-subbuild /home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-subbuild /home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-subbuild /home/echitosto/Documents/GitHub/DuckGame/build/_deps/sdl2_image-subbuild/CMakeFiles/sdl2_image-populate.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/sdl2_image-populate.dir/depend

