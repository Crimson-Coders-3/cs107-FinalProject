enable_testing()
include(CTest)

include_directories(${gtest_dir}/include)
link_directories(${gtest_dir}/lib)

file(GLOB TEST_H *.h *.hpp)

set(TEST_SRC
    test_ROOTS.cpp
)

add_library(ROOTSTest SHARED ${TEST_SRC} ${TEST_H})
if(APPLE)
  target_link_libraries(ROOTSTest gtest gtest_main)
endif()
