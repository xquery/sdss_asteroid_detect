#include "../src/detect.hpp"
#include <gtest/gtest.h>

using namespace std;

TEST(DetectTest,TestAllDetectMethods){
    EXPECT_TRUE(ad::naive_detect("test"));
}

