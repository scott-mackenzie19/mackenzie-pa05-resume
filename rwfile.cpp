//
// Created by Scott Mackenzie on 11/14/2021.
//Below file created to parse strings and store in article vector.

#include "rwfile.h"
#include <cctype>
using namespace std;
namespace fs = std::filesystem;
using namespace rapidjson;
#include <sstream>
#include <fstream>

void rwfile::parse(const string& filename) {
    ///
    ///used TA Christian's reference
    ///

    FILE * fp = fopen(filename.c_str(), "rb");
    char buffer [35540];
    FileReadStream ifss(fp, buffer, sizeof(buffer));
    Document document;
    document.ParseStream(ifss);
    if (!document.IsObject()) {
        return;
    }
    article art1; //article object created
    string paperID = document["uuid"].GetString();
    string titleName = document["title"].GetString();
    string body_text = document["text"].GetString();
    art1.setID(paperID); //ID set in article object
    art1.setTitle(titleName); //title set in article object
    art1.setBody(body_text); //body set in article object
    const rapidjson::Value& attributes = document["entities"]["persons"];
    const rapidjson::Value& holder = document["entities"]["organizations"];
    int counter = 1;
    for (rapidjson::Value::ConstValueIterator itr = attributes.Begin(); itr != attributes.End(); ++itr) {
        const rapidjson::Value& attribute = *itr;
       // cout<<"Author "<<counter<<endl;
        for (rapidjson::Value::ConstMemberIterator itr2 = attribute.MemberBegin(); itr2 != attribute.MemberEnd(); ++itr2) {
            if(itr2->name.IsString() && itr2->value.IsString()){
                if(strlen(itr2 -> value.GetString()) > 0) {
                    // addPeople needs a second parameter now, i changed it to work with hashmaps
                    // add for second parameter the object of the article that this person is found in. not sure how to do that
                    //make a copy
                    // string tempor = itr2->value.GetString();
                   // art1.addPeople(tempor, art1);
                }
            }
        }
        counter ++;
    }
    tokenize_file(art1);
    fclose(fp);
}
string holder;
void rwfile::populate_tree(const string& path) { //first custom
    int num = 0;
    int count = 0;
    holder = path;
    for (const auto& dirEntry : fs::recursive_directory_iterator(path)){
        if(!is_directory(dirEntry) && holder.find(dirEntry.path().c_str()) == string::npos){
            string filename = dirEntry.path().c_str();
            parse(filename);
            num ++;
            cout << num << endl;
            count = 1;
        }
        if (count == 1) {
            holder.append(dirEntry.path().c_str());
        }
        else if (is_directory(dirEntry)) { //if file is a folder and not already searched, function repeats
            holder.append(dirEntry.path().c_str());
            cout << "first" << endl;
            populate_tree(dirEntry.path().c_str());
        }
    }
}



void rwfile::tokenize_file(article& file) {
    stringstream ss(file.getBody());
   LOOP: while (ss.good()) {
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
            for (int i = 0; i < stopWords.size(); i++) {
                //cout << stopWords[i] << endl;
                if (stopWords[i] == word) {
                    goto LOOP;
                }
            }
            Porter2Stemmer::stem(word);
            unordered_map<string, article>*  ptr= &wordTree.insert(word);
            if (ptr->empty()) { //if map empty,
                int num = 0;
                temp1.setNum(num);
                temp1.increment();
                ptr->insert(make_pair(file.getID(), temp1));
            }
            else { //if map not empty
                if (ptr->find(file.getID()) == ptr->end()) {
                    int num = 0;
                    temp1.setNum(num);
                    //if find function returns last ID, file not found, and file appended
                    temp1.increment();
                    ptr->insert(make_pair(file.getID(), temp1));
                }
                else { //if file found
                    ptr->find(file.getID())->second.increment();
                    //cout << ptr->find(file.getID())->second.getNumOccurences() << endl;
                }
            }
        }
    }

}

DSAvlTree<string, unordered_map<string, article>> &rwfile::getTree() {
    return this->wordTree;
}

void rwfile::printTree (string arg, vector<pair<string, unordered_map<string, article>>> vec) {
    ofstream output (arg);
    if(!output) exit (EXIT_FAILURE);
    for (int i = 0; i < vec.size(); i++) {
        output << vec[i].first << ";";
        auto it = vec[i].second.begin();
        while (it != vec[i].second.end()) {
            output << it->second.getID() << ":";
            ++it;
        }
        output << endl;
    }
    output.close();
}

void rwfile::printPeople (string arg, vector<pair<string, vector<article>>> vec) {
    ofstream output (arg);
    if(!output) exit (EXIT_FAILURE);
    for (int i = 0; i < vec.size(); i++) {
        output << vec[i].first << ";";
        auto it = vec[i].second.begin();
        while (it != vec[i].second.end()) {
            output << it->getID() << ":";
            ++it;
        }
        output << endl;
    }
    output.close();
}

void rwfile::printOrgs (string arg, vector<pair<string, vector<article>>> vec) {
    ofstream output (arg);
    if(!output) exit (EXIT_FAILURE);
    for (int i = 0; i < vec.size(); i++) {
        output << vec[i].first << ";";
        auto it = vec[i].second.begin();
        while (it != vec[i].second.end()) {
            output << it->getID() << ":";
            it++;
        }
        output << endl;
    }
    output.close();
}

void rwfile::set_tree(DSAvlTree<string, unordered_map<string, article>>& table) {
    this->wordTree = table;
}

void rwfile::loadStopWords(const string &fileName) {
    ifstream ifs;
    ifs.open(fileName);
    while (ifs.good()) {
        string word;
        getline(ifs, word);
        Porter2Stemmer::trim(word);
        stopWords.emplace_back(word);
    }
    ifs.close();
}



/**
  * below was throwing errors so it's commented out so we can fix other problems before coming back to it
  */

DSAvlTree<string, unordered_map<string, article>> rwfile::readTree(string arg) {
    ifstream input (arg);
    if (!input) exit (EXIT_FAILURE);
    DSAvlTree<string, unordered_map<string, article>> index_me;
    string str;
    while (getline (input, str)) {
        stringstream ss(str);
        string temp;
        getline(ss, temp, ';');
        index_me.insert(temp);
        string temp2;
        while (getline(ss, temp2, ':')) {
            // scott: insert values here
        }
    }
}

DSHash <string, vector<article>> rwfile::readPeople(string arg) {
    ifstream input (arg);
    if (!input) exit (EXIT_FAILURE);
    DSHash <string, vector<article>> index_me;
    vector<article> vec;
    string str;
    while (getline(input, str)) {
        stringstream ss(str);
        string temp;
        getline (ss, temp, ';');
        // temp is key
        string temp2;
        while (getline (ss, temp2, ':')) {
            // temp2 is article ID. push back article associated with this ID into the vector
        }
        index_me.put(temp, vec);
    }
}

DSHash <string, vector<article>> rwfile::readOrgs(string arg) {
    ifstream input (arg);
    if (!input) exit (EXIT_FAILURE);
    DSHash <string, vector<article>> index_me;
    vector<article> vec;
    string str;
    while (getline(input, str)) {
        stringstream ss(str);
        string temp;
        getline (ss, temp, ';');
        // temp is key
        string temp2;
        while (getline (ss, temp2, ':')) {
            // temp2 is article ID. push back article associated with this ID into the vector
        }
        index_me.put(temp, vec);
    }
}