#define LOGURU_IMPLEMENTATION 1
#define LOGURU_WITH_STREAMS 1
#define LOGURU_FILENAME_WIDTH 16
#define LOGURU_REDEFINE_ASSERT 1

#include <loguru.hpp>

#define OK 0;

using namespace std;

int check_file_exists(string file){
    ifstream image_file(file);
    CHECK_S(image_file.good()) << "image file not found, loaded or corruptf.";
    return OK;
}
