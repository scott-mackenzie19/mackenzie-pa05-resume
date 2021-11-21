//
// Created by Scott Mackenzie on 11/14/2021.
//Below file created to parse strings and store in article vector.

#include "rwfile.h"
#include <cctype>
#include <sstream>
using namespace std;
namespace fs = std::filesystem;
using namespace rapidjson;

void rwfile::parse(const string& filename) {
    ///
    ///used TA Christian's reference
    ///
    FILE * fp = fopen(filename.c_str(), "rb");
    char buffer [63540];
    FileReadStream ifss(fp, buffer, sizeof(buffer));
    Document document;
    document.ParseStream(ifss);
    article art1; //article object created
    string paperID = document["uuid"].GetString();
    string titleName = document["title"].GetString();
    string body_text = document["text"].GetString();
    transform(body_text.begin(), body_text.end(), body_text.begin(), ::tolower);
    art1.setID(paperID); //ID set in article object
    art1.setTitle(titleName); //title set in article object
    art1.setBody(body_text); //body set in article object
    const rapidjson::Value& attributes = document["entities"]["persons"];
    const rapidjson::Value& holder = document["organizations"];
    int counter = 1;
    for (rapidjson::Value::ConstValueIterator itr = attributes.Begin(); itr != attributes.End(); ++itr) {
        const rapidjson::Value& attribute = *itr;
       // cout<<"Author "<<counter<<endl;
        for (rapidjson::Value::ConstMemberIterator itr2 = attribute.MemberBegin(); itr2 != attribute.MemberEnd(); ++itr2) {
            if(itr2->name.IsString() && itr2->value.IsString()){
                if(strlen(itr2 -> value.GetString()) > 0)
                    art1.addPeople( itr2->value.GetString());
            }
        }
        counter ++;
    }
    articles.push_back(art1);
    tokenize_file(art1);
    fclose(fp);
}

void rwfile::populate_tree(const string& path) {
    for (const auto& dirEntry : fs::recursive_directory_iterator(path)){
        if(!is_directory(dirEntry)){
            string filename = dirEntry.path().c_str();
            parse(filename);
        }
    }
    if (wordTree.contains("beech")) {
        cout << "good" << endl;
    }
}

void rwfile::tokenize_file(article& file) {
    stringstream ss(file.getBody());
    while (ss.good()) {
        string line;
        getline(ss, line);
        stringstream ls(line);
        while (ls.good()) {
            string word;
            getline(ls, word, ' ');
            Porter2Stemmer::trim(word);
            Porter2Stemmer::stem(word);
            vector<article> * ptr= &wordTree.insert(word);
            if (ptr->empty()) {
                ptr->emplace_back(file);
            }
            else {
               // cout << ptr->size() << endl;
                if (std::find(ptr->begin(), ptr->end(), file) == ptr->end()) {
                    //if find function returns last ID, file not found, and file appended
                    ptr->emplace_back(file);
                }
            }

        }
    }
}

DSAvlTree<string, vector<article>> &rwfile::getTree() {
    return this->wordTree;
}
