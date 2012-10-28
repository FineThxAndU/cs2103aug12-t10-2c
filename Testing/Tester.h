#include "gtest/gtest.h" //include to use Google Unit test's stuff

using namespace std ;
/************************************************************************/

/* We write test cases here */ /************************************************************************/

TEST(basic_test, add_simple_route) { 

	ASSERT_EQ(1, 1);
}

 
void runTest(int argument_count, char** argument_vars) { 

	testing::InitGoogleTest(&argument_count, argument_vars); //initialize GTest
	
	RUN_ALL_TESTS();
	
	std::getchar(); //pause the program after all the testing 
}