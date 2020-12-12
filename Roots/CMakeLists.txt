CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(Roots)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)

# force GNU linker to include all shared libraries
if(NOT APPLE)
  set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-as-needed")
else()
  set(CMAKE_MACOSX_RPATH ON)
endif()

#set(autodiff_dir "" CACHE PATH "AutoDiff path e.g. <autodiff_dir>/<autodiff_so>")
set(autodiff_so AutoDiff CACHE STRING "AutoDiff shared object name")
set(autodiff_dir ${PROJECT_SOURCE_DIR}/../AutoDiff/)
set(EIGEN_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/../install/3PL/eigen/include/eigen3)

# Enable coverage profiling
OPTION(COVERAGE "Enable Code Coverage Settings" OFF)
if(COVERAGE)
    set(CMAKE_CXX_FLAGS "-g -O0 --coverage -fprofile-arcs -ftest-coverage --coverage -fno-inline -fno-inline-small-functions -fno-default-inline")
endif()

# ======================== #
# location of header files
# ======================== #
include_directories(${autodiff_dir}/include
    ./include
    ${EIGEN_INCLUDE_DIR}
)

# Libraries to be linked
find_library(autodiff_lb NAMES ${autodiff_so} PATHS ${autodiff_dir}/lib)

# ========================================================= #
# location of directory to search for next "CmakeLists.txt"
# ========================================================= #
add_subdirectory(core)
