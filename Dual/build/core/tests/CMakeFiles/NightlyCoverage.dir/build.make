# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.19.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.19.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/build

# Utility rule file for NightlyCoverage.

# Include the progress variables for this target.
include core/tests/CMakeFiles/NightlyCoverage.dir/progress.make

core/tests/CMakeFiles/NightlyCoverage:
	cd /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/build/core/tests && /usr/local/Cellar/cmake/3.19.1/bin/ctest -D NightlyCoverage

NightlyCoverage: core/tests/CMakeFiles/NightlyCoverage
NightlyCoverage: core/tests/CMakeFiles/NightlyCoverage.dir/build.make

.PHONY : NightlyCoverage

# Rule to build all files generated by this target.
core/tests/CMakeFiles/NightlyCoverage.dir/build: NightlyCoverage

.PHONY : core/tests/CMakeFiles/NightlyCoverage.dir/build

core/tests/CMakeFiles/NightlyCoverage.dir/clean:
	cd /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/build/core/tests && $(CMAKE_COMMAND) -P CMakeFiles/NightlyCoverage.dir/cmake_clean.cmake
.PHONY : core/tests/CMakeFiles/NightlyCoverage.dir/clean

core/tests/CMakeFiles/NightlyCoverage.dir/depend:
	cd /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/core/tests /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/build /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/build/core/tests /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/build/core/tests/CMakeFiles/NightlyCoverage.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : core/tests/CMakeFiles/NightlyCoverage.dir/depend

