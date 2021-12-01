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
        Porter2Stemmer::trim(word);
        Porter2Stemmer::stem(word);
        unordered_map<string, article> temp = data.getTree().insert(word);
        int count = 1;
        for (ptr = temp.begin(); ptr != temp.end(); ptr++) {
            cout << endl << "Search Result " << count << ": " << ptr->second.getNumOccurences() << endl << endl;
            count++;
        }

        data.printTree (argv[3], data.getTree().populateVector());


        return 0;
    }
}

/**TO DO:
 * add copy constructor & overloaded assignment operator to dshash
 * store hash map of person and hash map of org
 * functionality so user can CHOOSE to use pre parsed info or parse their own again
 * boolean command args (this NOT that AND there)
 * Doxygen Documentation, UML Class Diagram
 */