#include "../detect.hpp"
#include <iostream>

using namespace ad;
using namespace std;

int main(int argc, char** argv ){
    if ( argc != 2 )
    {
        printf("usage: detect <Image_Path>\n");
        return -1;
    }

    naive_detect(argv[1]);

    cout << "asteroid detect | Jim Fuller https://github.com/xquery/asteroid_detect @2017" << endl;
    return 0;
}