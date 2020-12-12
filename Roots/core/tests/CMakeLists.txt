enable_testing()
include(CTest)

include_directories(${gtest_dir}/include)
link_directories(${gtest_dir}/lib)

find_library(gtest      NAMES gtest      gtestd      HINTS "${gtest_dir}/lib")
find_library(gtest_main NAMES gtest_main gtest_maind HINTS "${gtest_dir}/lib")

set(autodiff_dir ${PROJECT_SOURCE_DIR}/../AutoDiff/)
set(EIGEN_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/../install/3PL/eigen/include/eigen3)
set(TEST_EXE ROOTSTest.Unit.Test)
set(TEST_SRC_PATH src)

find_library(autodiff_lb NAMES AutoDiff PATHS ${autodiff_dir}/install/lib)

# include test headers
include_directories(src)

# include AutoDiff and Eigen libraries
include_directories(${sutodiff_dir}/include
    ${EIGEN_INCLUDE_DIR}
)

set(libs
    ${gtest} ${gtest_main} ${autodiff_lb}
    ${CMAKE_THREAD_LIBS_INIT}
)

add_subdirectory(${TEST_SRC_PATH})

add_executable(${TEST_EXE} test_main.cpp)
target_link_libraries(${TEST_EXE} ROOTSTest Roots ${libs})
target_link_libraries(${TEST_EXE} pthread)

add_test(NAME ${TEST_EXE}
         COMMAND $<TARGET_FILE:${TEST_EXE}>)

add_custom_command(
   TARGET ${TEST_EXE}
   COMMENT "Run ROOTS Unit Tests"
   POST_BUILD
   COMMAND ${TEST_EXE}
)
