#define LOGURU_IMPLEMENTATION 1
#define LOGURU_WITH_STREAMS 1
#define LOGURU_FILENAME_WIDTH 16
#define LOGURU_REDEFINE_ASSERT 1

#include <loguru.hpp>

using namespace std;

int check_file_exists(string file){
    ifstream image_file(file);
    LOG_S(INFO) << image_file.good();
    if (image_file.good()){
        return 0;
    }else{
        return -1;
    }
}
