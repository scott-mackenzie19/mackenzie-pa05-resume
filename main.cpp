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
        string word = argv[2];
        Porter2Stemmer::trim(word);
        Porter2Stemmer::stem(word);
        int count = 1;
        for (ptr = data.getTree().insert(word).begin(); ptr < data.getTree().insert(word).end(); ptr++) {
            cout << endl << "Search Result " << count << ": " << ptr->getTitle() << endl << endl;
            count++;
        }
        return 0;
    }
}

/**TO DO:
 * relevancy ranking algorithm: term-frequency/inverse document frequency
 * hash maps
 * putting person and orgs into hash maps
 * boolean command args
 * Doxygen Documentation, UML Class Diagram
 */