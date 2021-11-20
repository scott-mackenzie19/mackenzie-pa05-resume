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
#include "catch_setup.h"
#include <iterator>
using namespace std;
namespace fs = std::filesystem;
using namespace rapidjson;

int main(int argc, char** argv) {
    if (argc == 1) runCatchTests();
    else {
        string path = argv[1];
        rwfile data;
        data.populate_tree(path);
        vector<article> ::iterator ptr;
        int count = 1;
        for (ptr = data.getTree().insert(argv[2]).begin(); ptr < data.getTree().insert(argv[2]).end(); ptr++) {
            cout << endl << "Search Result " << count << ": " << ptr->getTitle() << endl << endl;
            count++;
        }
        return 0;
    }
}