# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.18.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.18.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/build

# Utility rule file for NightlyConfigure.

# Include the progress variables for this target.
include core/tests/CMakeFiles/NightlyConfigure.dir/progress.make

core/tests/CMakeFiles/NightlyConfigure:
	cd /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/build/core/tests && /usr/local/Cellar/cmake/3.18.4/bin/ctest -D NightlyConfigure

NightlyConfigure: core/tests/CMakeFiles/NightlyConfigure
NightlyConfigure: core/tests/CMakeFiles/NightlyConfigure.dir/build.make

.PHONY : NightlyConfigure

# Rule to build all files generated by this target.
core/tests/CMakeFiles/NightlyConfigure.dir/build: NightlyConfigure

.PHONY : core/tests/CMakeFiles/NightlyConfigure.dir/build

core/tests/CMakeFiles/NightlyConfigure.dir/clean:
	cd /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/build/core/tests && $(CMAKE_COMMAND) -P CMakeFiles/NightlyConfigure.dir/cmake_clean.cmake
.PHONY : core/tests/CMakeFiles/NightlyConfigure.dir/clean

core/tests/CMakeFiles/NightlyConfigure.dir/depend:
	cd /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/core/tests /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/build /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/build/core/tests /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/build/core/tests/CMakeFiles/NightlyConfigure.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : core/tests/CMakeFiles/NightlyConfigure.dir/depend

