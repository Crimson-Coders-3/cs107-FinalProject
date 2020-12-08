/* header files */
#include "gtest/gtest.h"
#include "test_vars.h"


int main(int argc,char **argv){
    /* Initialize Google Test */
    ::testing::InitGoogleTest(&argc,argv);

    /* this forces the testing library to link */
    ADLibrary_unittest();
    ADLibrary_nametest();
    ADLibrary_nestedtest();
    ADLibrary_vectortest();

    /* Run Tests */
    return RUN_ALL_TESTS();
}