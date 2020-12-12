enable_testing()
include(CTest)

include_directories(${gtest_dir}/include)
link_directories(${gtest_dir}/lib)

file(GLOB TEST_H *.h *.hpp)

set(TEST_SRC
    test_ADF_unit.cpp 
    test_ADF_names.cpp
    test_ADF_nested.cpp
    test_ADFV_unit.cpp
)

add_library(ADTest SHARED ${TEST_SRC} ${TEST_H})
if(APPLE)
  target_link_libraries(ADTest gtest gtest_main)
endif()