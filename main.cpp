#include <iostream>
#include "include/rapidjson/document.h"
#include "include/rapidjson/istreamwrapper.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/Writer.h"
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <filesystem>
#include "porter2_stemmer.h"
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
        // we don't want boolean inquiries ('AND', 'NOT') to be put to lower which i think this function does?
        //Porter2Stemmer::trim(word);
        Porter2Stemmer::stem(word);
        int count = 1;
        for (ptr = data.getTree().insert(word).begin(); ptr < data.getTree().insert(word).end(); ptr++) {
            cout << endl << "Search Result " << count << ": " << ptr->getID() << endl << endl;
            count++;
        }
        return 0;
    }
}

/**TO DO:
 *add a word count property to the object so when a word is found in doc the parser keeps going to count how many times
 *
 *change path so it can also accept folders of folders
 *
 * change avl tree value from vector to hash map where key is object id and value is full object. also maybe
 * try to return by reference in some places and see if that speeds things up
 *
 * figure out how to store parsed tree so that it doesn't have to be parsed again. note on this:
 * we need functionality so user can CHOOSE to use pre parsed tree or parse their own again
 *
 * putting person and orgs into hash maps
 *
 * boolean command args
 *
 * Doxygen Documentation, UML Class Diagram
 */