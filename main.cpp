#include <iostream>
#include "include/rapidjson/document.h"
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
        unordered_map<string, article> ::iterator ptr;
        string word = argv[2];
        // we don't want boolean inquiries ('AND', 'NOT') to be put to lower which i think this function does?
        Porter2Stemmer::trim(word);
        Porter2Stemmer::stem(word);
        unordered_map<string, article> temp = data.getTree().insert(word);
        int count = 1;
        for (ptr = temp.begin(); ptr != temp.end(); ptr++) {
            cout << endl << "Search Result " << count << ": " << ptr->second.getNumOccurences() << endl << endl;
            count++;
        }
        return 0;
    }
}

/**TO DO:
 * SCOTT - check my note rwfile.cpp line 37
 * also main.cpp 27, let me know if commenting out that line fixes it or how else we could get rid of toLower in search query, because if user types all caps
 * we need to keep that for boolean command args
 *
 * add a word count property to the object so when a word is found in doc the parser keeps going to count how many times.
 * scott (because it has to do with parse function)
 *
 *change path so it can also accept folders of folders
 * scott (because it has to do with parse function)
 *
 * change avl tree value from vector to hash map where key is object id and value is full object. also maybe
 * try to return by reference in some places and see if that speeds things up
 * scott (because it has to do with parse function)
 *
 * figure out how to store parsed tree so that it doesn't have to be parsed again.
 * kate
 *
 * we need functionality so user can CHOOSE to use pre parsed tree or parse their own again
 * kate
 *
 * putting person and orgs into hash maps
 * scott (because you populated avl tree and i'm guessing it's pretty similar logic)
 *
 * boolean command args (this NOT that AND there)
 * kate
 *
 * Doxygen Documentation, UML Class Diagram
 * kate
 */