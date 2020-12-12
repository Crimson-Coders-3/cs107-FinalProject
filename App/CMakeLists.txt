CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(App)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)

# ======================================== #
# Include all shared libraries for GNU
if(NOT APPLE)
  set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-as-needed")
else()
  set(CMAKE_MACOSX_RPATH ON)
endif()
# ======================================= #

# ======================================= #
# Library paths
set(gtest_dir   "" CACHE PATH "GTest install directory location")
#set(autodiff_dir "" CACHE PATH "AutoDiff path e.g. <autodiff_dir>/<autodiff_so>")
set(autodiff_dir ${PROJECT_SOURCE_DIR}/../AutoDiff/)
#set(autodiff_so AutoDiff CACHE STRING "AutoDiff shared object name")
set(autodiff_so AutoDiff)
set(rootfinder_dir ${PROJECT_SOURCE_DIR}/../Roots/)
set(rootfinder_so Roots) #CACHE STRING "Roots shared object name")
set(EIGEN_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/../install/3PL/eigen/include/eigen3)
# ======================================= #

# ======================================= #
# Library header files to be included
include_directories(${autodiff_dir}/include
                    ./include
                    ${rootfinder_dir}/include
                    ${EIGEN_INCLUDE_DIR})

# Libraries to be linked
find_library(autodiff_lb NAMES ${autodiff_so} PATHS ${autodiff_dir}/install/lib)
find_library(roots_lb NAMES ${rootfinder_so} PATHS ${rootfinder_dir}/install/lib)
# ======================================= #

# ======================================= #
# Source directories for this project
set(src_path src)
add_subdirectory(${src_path})
# ======================================= #

# ======================================= #
# Unit Testing Option - uses Google Test
OPTION(UNIT_TEST "Enable unit testing" OFF)
if(UNIT_TEST)
  include_directories(${src_path})
  add_subdirectory(tests)
endif()
# ======================================= #
