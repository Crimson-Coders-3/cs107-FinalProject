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

# Include any dependencies generated for this target.
include core/tests/CMakeFiles/DUALTest.Unit.Test.dir/depend.make

# Include the progress variables for this target.
include core/tests/CMakeFiles/DUALTest.Unit.Test.dir/progress.make

# Include the compile flags for this target's objects.
include core/tests/CMakeFiles/DUALTest.Unit.Test.dir/flags.make

core/tests/CMakeFiles/DUALTest.Unit.Test.dir/test_main.cpp.o: core/tests/CMakeFiles/DUALTest.Unit.Test.dir/flags.make
core/tests/CMakeFiles/DUALTest.Unit.Test.dir/test_main.cpp.o: ../core/tests/test_main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object core/tests/CMakeFiles/DUALTest.Unit.Test.dir/test_main.cpp.o"
	cd /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/build/core/tests && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DUALTest.Unit.Test.dir/test_main.cpp.o -c /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/core/tests/test_main.cpp

core/tests/CMakeFiles/DUALTest.Unit.Test.dir/test_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DUALTest.Unit.Test.dir/test_main.cpp.i"
	cd /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/build/core/tests && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/core/tests/test_main.cpp > CMakeFiles/DUALTest.Unit.Test.dir/test_main.cpp.i

core/tests/CMakeFiles/DUALTest.Unit.Test.dir/test_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DUALTest.Unit.Test.dir/test_main.cpp.s"
	cd /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/build/core/tests && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/core/tests/test_main.cpp -o CMakeFiles/DUALTest.Unit.Test.dir/test_main.cpp.s

# Object files for target DUALTest.Unit.Test
DUALTest_Unit_Test_OBJECTS = \
"CMakeFiles/DUALTest.Unit.Test.dir/test_main.cpp.o"

# External object files for target DUALTest.Unit.Test
DUALTest_Unit_Test_EXTERNAL_OBJECTS =

bin/DUALTest.Unit.Test: core/tests/CMakeFiles/DUALTest.Unit.Test.dir/test_main.cpp.o
bin/DUALTest.Unit.Test: core/tests/CMakeFiles/DUALTest.Unit.Test.dir/build.make
bin/DUALTest.Unit.Test: lib/libDUALTest.dylib
bin/DUALTest.Unit.Test: lib/libDual.dylib
bin/DUALTest.Unit.Test: /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/install/3PL/googletest/lib/libgtest.a
bin/DUALTest.Unit.Test: /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/install/3PL/googletest/lib/libgtest_main.a
bin/DUALTest.Unit.Test: core/tests/CMakeFiles/DUALTest.Unit.Test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/DUALTest.Unit.Test"
	cd /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/build/core/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DUALTest.Unit.Test.dir/link.txt --verbose=$(VERBOSE)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Run DUAL Unit Tests"
	cd /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/build/core/tests && ../../bin/DUALTest.Unit.Test

# Rule to build all files generated by this target.
core/tests/CMakeFiles/DUALTest.Unit.Test.dir/build: bin/DUALTest.Unit.Test

.PHONY : core/tests/CMakeFiles/DUALTest.Unit.Test.dir/build

core/tests/CMakeFiles/DUALTest.Unit.Test.dir/clean:
	cd /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/build/core/tests && $(CMAKE_COMMAND) -P CMakeFiles/DUALTest.Unit.Test.dir/cmake_clean.cmake
.PHONY : core/tests/CMakeFiles/DUALTest.Unit.Test.dir/clean

core/tests/CMakeFiles/DUALTest.Unit.Test.dir/depend:
	cd /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/core/tests /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/build /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/build/core/tests /Users/wenlingong/Documents/GitHub/Classes/cs107/cs107-FinalProject/Dual/build/core/tests/CMakeFiles/DUALTest.Unit.Test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : core/tests/CMakeFiles/DUALTest.Unit.Test.dir/depend

