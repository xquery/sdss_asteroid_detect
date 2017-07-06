#include "../src/detect.hpp"
#include <gtest/gtest.h>

using namespace std;

TEST(DetectTest,TestNaiveDetectNonExistentImageFile){
    EXPECT_EQ(ad::naive_detect("adfasdfadfadfnon-existent-image-file.jpg"),-1);
}

TEST(DetectTest,TestNaiveDetectNoHits){
    EXPECT_EQ(ad::naive_detect("../data/test/test3.jpg"),0);
}

TEST(DetectTest,TestNaiveDetectHits){
    EXPECT_EQ(ad::naive_detect("../data/test/test.jpg"),0);
}
