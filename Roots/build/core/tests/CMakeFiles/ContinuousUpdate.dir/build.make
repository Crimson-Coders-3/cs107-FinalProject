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
CMAKE_COMMAND = /home/morrisreeves/anaconda3/lib/python3.8/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/morrisreeves/anaconda3/lib/python3.8/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/morrisreeves/Documents/coding/cs107/cs107-FinalProject/Roots

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/morrisreeves/Documents/coding/cs107/cs107-FinalProject/Roots/build

# Utility rule file for ContinuousUpdate.

# Include the progress variables for this target.
include core/tests/CMakeFiles/ContinuousUpdate.dir/progress.make

core/tests/CMakeFiles/ContinuousUpdate:
	cd /home/morrisreeves/Documents/coding/cs107/cs107-FinalProject/Roots/build/core/tests && /home/morrisreeves/anaconda3/lib/python3.8/site-packages/cmake/data/bin/ctest -D ContinuousUpdate

ContinuousUpdate: core/tests/CMakeFiles/ContinuousUpdate
ContinuousUpdate: core/tests/CMakeFiles/ContinuousUpdate.dir/build.make

.PHONY : ContinuousUpdate

# Rule to build all files generated by this target.
core/tests/CMakeFiles/ContinuousUpdate.dir/build: ContinuousUpdate

.PHONY : core/tests/CMakeFiles/ContinuousUpdate.dir/build

core/tests/CMakeFiles/ContinuousUpdate.dir/clean:
	cd /home/morrisreeves/Documents/coding/cs107/cs107-FinalProject/Roots/build/core/tests && $(CMAKE_COMMAND) -P CMakeFiles/ContinuousUpdate.dir/cmake_clean.cmake
.PHONY : core/tests/CMakeFiles/ContinuousUpdate.dir/clean

core/tests/CMakeFiles/ContinuousUpdate.dir/depend:
	cd /home/morrisreeves/Documents/coding/cs107/cs107-FinalProject/Roots/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/morrisreeves/Documents/coding/cs107/cs107-FinalProject/Roots /home/morrisreeves/Documents/coding/cs107/cs107-FinalProject/Roots/core/tests /home/morrisreeves/Documents/coding/cs107/cs107-FinalProject/Roots/build /home/morrisreeves/Documents/coding/cs107/cs107-FinalProject/Roots/build/core/tests /home/morrisreeves/Documents/coding/cs107/cs107-FinalProject/Roots/build/core/tests/CMakeFiles/ContinuousUpdate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : core/tests/CMakeFiles/ContinuousUpdate.dir/depend

