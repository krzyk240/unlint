# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kwazar/unlint/unlint

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kwazar/unlint/unlint/build

# Include any dependencies generated for this target.
include CMakeFiles/unlint.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/unlint.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/unlint.dir/flags.make

CMakeFiles/unlint.dir/main.o: CMakeFiles/unlint.dir/flags.make
CMakeFiles/unlint.dir/main.o: ../main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/kwazar/unlint/unlint/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/unlint.dir/main.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/unlint.dir/main.o -c /home/kwazar/unlint/unlint/main.cpp

CMakeFiles/unlint.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/unlint.dir/main.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/kwazar/unlint/unlint/main.cpp > CMakeFiles/unlint.dir/main.i

CMakeFiles/unlint.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/unlint.dir/main.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/kwazar/unlint/unlint/main.cpp -o CMakeFiles/unlint.dir/main.s

CMakeFiles/unlint.dir/main.o.requires:
.PHONY : CMakeFiles/unlint.dir/main.o.requires

CMakeFiles/unlint.dir/main.o.provides: CMakeFiles/unlint.dir/main.o.requires
	$(MAKE) -f CMakeFiles/unlint.dir/build.make CMakeFiles/unlint.dir/main.o.provides.build
.PHONY : CMakeFiles/unlint.dir/main.o.provides

CMakeFiles/unlint.dir/main.o.provides.build: CMakeFiles/unlint.dir/main.o

# Object files for target unlint
unlint_OBJECTS = \
"CMakeFiles/unlint.dir/main.o"

# External object files for target unlint
unlint_EXTERNAL_OBJECTS =

unlint: CMakeFiles/unlint.dir/main.o
unlint: CMakeFiles/unlint.dir/build.make
unlint: CMakeFiles/unlint.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable unlint"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/unlint.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/unlint.dir/build: unlint
.PHONY : CMakeFiles/unlint.dir/build

CMakeFiles/unlint.dir/requires: CMakeFiles/unlint.dir/main.o.requires
.PHONY : CMakeFiles/unlint.dir/requires

CMakeFiles/unlint.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/unlint.dir/cmake_clean.cmake
.PHONY : CMakeFiles/unlint.dir/clean

CMakeFiles/unlint.dir/depend:
	cd /home/kwazar/unlint/unlint/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kwazar/unlint/unlint /home/kwazar/unlint/unlint /home/kwazar/unlint/unlint/build /home/kwazar/unlint/unlint/build /home/kwazar/unlint/unlint/build/CMakeFiles/unlint.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/unlint.dir/depend

