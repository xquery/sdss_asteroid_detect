#include "../detect.hpp"

using namespace ad;
using namespace std;

int main(int argc, char** argv ){
    LOG_S(INFO) << "asteroid naive_detect | Copyright 2017 James Fuller jim.fuller@webcomposite.com | https://github.com/xquery/asteroid_detect";

    if ( argc != 2 )
    {
        LOG_S(INFO) << "usage: naive_detect <Image_Path>";
        return -1;
    }

    return 0;
}