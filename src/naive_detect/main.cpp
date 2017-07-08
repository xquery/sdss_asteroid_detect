#include "../detect.hpp"

using namespace ad;
using namespace std;

// initial simple approach using hough circles and opencv pre processing

int main(int argc, char** argv ){
    LOG_S(INFO) << "asteroid naive_detect | Copyright 2017 James Fuller jim.fuller@webcomposite.com | https://github.com/xquery/asteroid_detect";

    if ( argc != 2 )
    {
        LOG_S(INFO) << "usage: naive_detect <Image_Path>";
        return -1;
    }

    naive_detect(argv[1]);

    return 0;
}