CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(Dual)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# I commented the line below because it raised an error
# even though this line is in the GitHub repo
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)

# force GNU linker to include all shared libraries
if(NOT APPLE)
  set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-as-needed")
else()
  set(CMAKE_MACOSX_RPATH ON)
endif()


# Enable coverage profiling
OPTION(COVERAGE "Enable Code Coverage Settings" OFF)
if(COVERAGE)
  # Original code in course repo has line 27 and line 30, 
  # I commented them out. Otherwise, it wouldn't work for MacOS
  # if(CMAKE_C_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "-g -O0 --coverage -fprofile-arcs -ftest-coverage --coverage -fno-inline -fno-inline-small-functions -fno-default-inline")
    # set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
  # endif()
endif()

# ======================== #
# location of header files
# ======================== #
include_directories(include)

# ========================================================= #
# location of directory to search for next "CmakeLists.txt"
# ========================================================= #
add_subdirectory(core)
