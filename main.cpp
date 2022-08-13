#include <iostream>
#include "include/rapidjson/document.h"
#include "porter2_stemmer.h"
#include <string>
#include "rwfile.h"
#include "catch_setup.h"
#include <iterator>
#include <algorithm>
#include "query.h"
using namespace std;
namespace fs = std::filesystem;
using namespace rapidjson;

int main(int argc, char** argv) {
    if (argc == 1) {
        query q;
        q.menu();
    }

//        rwfile data;
//        unordered_map<string, article> ::iterator ptr;
//        string word = argv[2];
//        Porter2Stemmer::trim(word);
//        Porter2Stemmer::stem(word);
//        if (!data.getTree().contains(word)) {
//            cout << "no docum1ents" << endl;
//            return 1;
//        }
//        data.printTree ("output.txt", data.getTree().populateVector());
//        data.printPeople ("outputPeople.txt", data.getPeopleHash().populateVector());
//        data.printOrgs ("outputOrgs.txt", data.getOrganizationsHash().populateVector());
//
//        unordered_map<string, article> temp = data.getTree().find(word);
//        vector<article> results;
//        int count = 1;
//        for (ptr = temp.begin(); ptr != temp.end(); ptr++) {
//            FILE* fp = fopen(ptr->second.getPath().c_str(), "rb");
//            char buffer [35540];
//            if (fp == nullptr) {
//                cout << ptr->second.getPath() << endl;
//                continue;
//            }
//            FileReadStream ifss(fp, buffer, sizeof(buffer));
//            Document document;
//            document.ParseStream(ifss);
//            article art1; //article object created
//            string paperID = document["uuid"].GetString();
//            string titleName = document["title"].GetString();
//            string body_text = document["text"].GetString();
//            art1.setID(paperID); //ID set in article object
//            art1.setTitle(titleName); //title set in article object
//            art1.setBody(body_text); //body set in article object
//            art1.setNum(ptr->second.getNumOccurences());
//            cout << endl << "Search Result " << count << ": " << art1.getTitle() << endl << endl;
//            results.emplace_back(art1);
//            count++;
//            fclose(fp);
//        }
//        sort(results.begin(),results.end());
//
//        data.printTree ("output.txt", data.getTree().populateVector());
//        data.printPeople ("outputPeople.txt", data.getPeopleHash().populateVector());
//        data.printOrgs ("outputOrgs.txt", data.getOrganizationsHash().populateVector());
//
//        data.readTree("output.txt");
//        data.readPeople("outputPeople.txt");
//        data.readOrgs("outputOrgs.txt");

        return 0;
    }
