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
CMAKE_SOURCE_DIR = /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/AutoDiff

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/AutoDiff/build

# Utility rule file for NightlyMemCheck.

# Include the progress variables for this target.
include core/tests/CMakeFiles/NightlyMemCheck.dir/progress.make

core/tests/CMakeFiles/NightlyMemCheck:
	cd /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/AutoDiff/build/core/tests && /usr/local/Cellar/cmake/3.19.1/bin/ctest -D NightlyMemCheck

NightlyMemCheck: core/tests/CMakeFiles/NightlyMemCheck
NightlyMemCheck: core/tests/CMakeFiles/NightlyMemCheck.dir/build.make

.PHONY : NightlyMemCheck

# Rule to build all files generated by this target.
core/tests/CMakeFiles/NightlyMemCheck.dir/build: NightlyMemCheck

.PHONY : core/tests/CMakeFiles/NightlyMemCheck.dir/build

core/tests/CMakeFiles/NightlyMemCheck.dir/clean:
	cd /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/AutoDiff/build/core/tests && $(CMAKE_COMMAND) -P CMakeFiles/NightlyMemCheck.dir/cmake_clean.cmake
.PHONY : core/tests/CMakeFiles/NightlyMemCheck.dir/clean

core/tests/CMakeFiles/NightlyMemCheck.dir/depend:
	cd /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/AutoDiff/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/AutoDiff /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/AutoDiff/core/tests /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/AutoDiff/build /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/AutoDiff/build/core/tests /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/AutoDiff/build/core/tests/CMakeFiles/NightlyMemCheck.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : core/tests/CMakeFiles/NightlyMemCheck.dir/depend

