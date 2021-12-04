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


// /Users/katebouis/Desktop/arch beech
int main(int argc, char** argv) {
    if (argc == 1) runCatchTests();
    else {
        string path = argv[1];
        rwfile data;
        //data.loadStopWords();
        //data.populate_tree(path);
        string pathius = argv[3];
        data.readFromPersistence(pathius);
        unordered_map<string, article> ::iterator ptr;
        string word = argv[2];
        Porter2Stemmer::trim(word);
        Porter2Stemmer::stem(word);
        unordered_map<string, article> temp = data.getTree().insert(word);
        int count = 1;
        for (ptr = temp.begin(); ptr != temp.end(); ptr++) {
            cout << endl << "Search Result " << count << ": " << ptr->second.getTitle() << endl << endl;
            count++;
        }
       // data.printTree (argv[3], data.getTree().populateVector());
//        data.printPeople ("outputPeople.txt", data.getPeople().populateVector());
//        data.printOrgs ("outputOrgs.txt", data.getOrgs().populateVector());

//        data.readTree("output.txt");
//        data.readPeople("outputPeople.txt");
//        data.readOrgs("outputOrgs.txt");

        return 0;
    }
}

/**TO DO:
 *
 * SCOTT:
 * move people & org hash maps from article to rwfile, basically parse them like you did the tree
 *
 * make people and org hash maps to have value of vector of articles instead of just articles
 *
 * speed hashing
 *
 * when printing tree back can you look at my comment and add functionality like how you did populate_tree?
 * i'm not really sure how you added keys + values back into tree. also values in file are IDs but we need
 * way to store pathway to these so users can read article after seeing title
 *
 * also when printing maps back look at my comment, how can we access article associated with ID and push
 * that full article back?
 *
 * need to store pathway to files in persistency index
 *
 * KATE:
 * store hash map of person and hash map of org in file
 *
 * reading files back into trees or hash maps
 *
 * functionality so user can CHOOSE to use pre parsed info or parse their own again
 *
 * menu for user interaction in a while loop (query class)
 *
 * boolean command args (this NOT that AND there)
 *
 * Doxygen Documentation, UML Class Diagram]
 */