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

        data.printTree ("output.txt", data.getTree().populateVector());
//        data.printPeople ("outputPeople.txt", data.getPeople().populateVector());
//        data.printOrgs ("outputOrgs.txt", data.getOrgs().populateVector());

// set these equal to setter functions:
//        data.readTree("output.txt");
//        data.readMap("outputPeople.txt");
//        data.readMap("outputOrgs.txt");

        return 0;
    }
}

/**TO DO:
 * WHOEVER:
 * fix dshash destructor - have fontenot help office hours tmrw
 *
 * SCOTT:
 * getters for people & orgs hash maps in rwfile
 *
 * maybe make people and org hash maps to have value of vector of articles instead of just articles
 *
 * setters for tree, people, and orgs so that reading in from file can create new tree
 *
 * KATE:
 * store hash map of person and hash map of org in file (written but untested)
 *
 * reading files back into trees or hash maps - have fontenot help office hours tmrw
 *
 * functionality so user can CHOOSE to use pre parsed info or parse their own again
 *
 * menu for user interaction in a while loop (query class)
 *
 * boolean command args (this NOT that AND there)
 *
 * Doxygen Documentation, UML Class Diagram
 *
 * OFFICE HOURS:
 * debug destructor
 * help with reading files back into map/tree
 * hash func with templating in dshash
 */