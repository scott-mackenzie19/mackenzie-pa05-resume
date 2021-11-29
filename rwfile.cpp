//
// Created by Scott Mackenzie on 11/14/2021.
//Below file created to parse strings and store in article vector.

#include "rwfile.h"
#include <cctype>
using namespace std;
namespace fs = std::filesystem;
using namespace rapidjson;
#include <sstream>

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
                if(strlen(itr2 -> value.GetString()) > 0) {
                    // addPeople needs a second parameter now, i changed it to work with hashmaps
                    // add for second parameter the object of the article that this person is found in. not sure how to do that
                   // string tempor = itr2->value.GetString();
                   // art1.addPeople(tempor, art1);
                }
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
        if(!is_directory(dirEntry) && dirEntry.path().string().find(".json") != string::npos){
            string filename = dirEntry.path().c_str();
            //cout << filename << endl;
            parse(filename);
        }
        if(is_directory(dirEntry)){
           // cout << dirEntry.path().c_str() << endl;
            populate_tree(dirEntry.path().c_str());
        }
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
            string temp;
            getline(ls, word, ' ');
            article temp1;
            temp1.setID(file.getID());
            temp1.setTitle(file.getTitle());
            temp1.setBody(file.getBody());
            Porter2Stemmer::trim(word);
            Porter2Stemmer::stem(word);
            unordered_map<string, article>*  ptr= &wordTree.insert(word);
            if (ptr->empty()) {
                temp1.increment();
                ptr->insert(make_pair(file.getID(), temp1));
            }
            else {
                //cout << ptr->size() << endl;
                if (ptr->find(file.getID()) == ptr->end()) {
                    //if find function returns last ID, file not found, and file appended
                    temp1.increment();
                    ptr->insert(make_pair(file.getID(), temp1));
                }
                else {
                    temp1.increment();
                }
            }

        }
    }

}

DSAvlTree<string, unordered_map<string, article>> &rwfile::getTree() {
    return this->wordTree;
}
