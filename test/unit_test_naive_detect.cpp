#include "../src/detect.hpp"
#include <gtest/gtest.h>

using namespace std;

TEST(DetectTest,TestNaiveDetectNoHits){
    EXPECT_EQ(ad::naive_detect("../data/test/positives/test.jpg"),0);
}

TEST(DetectTest,TestNaiveDetectHits){
    EXPECT_EQ(ad::naive_detect("../data/test/positives/test6-positive.jpg"),0);
}
