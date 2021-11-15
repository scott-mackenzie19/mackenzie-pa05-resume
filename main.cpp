#include <iostream>
#include "include/rapidjson/document.h"
#include "include/rapidjson/istreamwrapper.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/Writer.h"
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <filesystem>
#include <string>
#include "rwfile.h"
using namespace std;
namespace fs = std::filesystem;
using namespace rapidjson;

int main() {
    string path = "arch";
    std::cout << "Hello, World!" << std::endl;
    rwfile fileList;
    fileList.print_filenames(path);
    return 0;
}
