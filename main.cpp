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
        string output;
        rwfile data;
        data.loadStopWords();
        output = argv[3];
      //  data.populate_tree(path);
      //  data.printTree ("output.txt", data.getTree().populateVector());
        data.readTree(output);
        //string person = "guthrie";
        //cout << data.getPeopleHash().at(person).at(0).getTitle() << endl;
        unordered_map<string, article> ::iterator ptr;
        string word = argv[2];
        Porter2Stemmer::trim(word);
        Porter2Stemmer::stem(word);
        if (!data.getTree().contains(word)) {
            cout << "no documents" << endl;
            return 1;
        }
        unordered_map<string, article> temp = data.getTree().find(word);
        vector<article> results;
        int count = 1;
        for (ptr = temp.begin(); ptr != temp.end(); ptr++) {
            FILE* fp = fopen(ptr->second.getPath().c_str(), "rb");
            char buffer [35540];
            if (fp == nullptr) {
                cout << ptr->second.getPath() << endl;
                continue;
            }
            FileReadStream ifss(fp, buffer, sizeof(buffer));
            Document document;
            document.ParseStream(ifss);
            article art1; //article object created
            string paperID = document["uuid"].GetString();
            string titleName = document["title"].GetString();
            string body_text = document["text"].GetString();
            art1.setID(paperID); //ID set in article object
            art1.setTitle(titleName); //title set in article object
            art1.setBody(body_text); //body set in article object
            art1.setNum(ptr->second.getNumOccurences());
            cout << endl << "Search Result " << count << ": " << art1.getTitle() << endl << endl;
            results.emplace_back(art1);
            count++;
            fclose(fp);
        }
        return 0;
    }
}

/**TO DO:
 *
 * avl tree of words and article IDs as strings
 * unordered map of articles with that ID as the key and object as value
 *
 * SCOTT:
 * move people & org hash maps from article to rwfile, basically populate them like you did the tree
 *
 * make people and org hash maps to have value of vector of articles instead of just articles
 *
 * store article pathway in article.cpp along with all the other values
 *
 * when printing tree back can you look at my comment and add functionality like how you did populate_tree?
 * i'm not really sure how you added keys + values back into tree.
 *
 * also when printing maps back look at my comment, how can we parse again using article pathway
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