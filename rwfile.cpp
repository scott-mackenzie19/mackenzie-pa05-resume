//
// Created by Scott Mackenzie on 11/14/2021.
//Below file created to parse strings and store in article vector.

#include "rwfile.h"
#include <cctype>
#include <bits/stdc++.h>
using namespace std;
namespace fs = std::filesystem;
using namespace rapidjson;

void rwfile::parse(string filename) {
    article art1;
    ifstream ifss(filename);
    IStreamWrapper isw(ifss);
    Document document;
    document.ParseStream(isw);
    string paperID = document["uuid"].GetString();
    string titleName = document["title"].GetString();
    string body_text = document["text"].GetString();
    transform(body_text.begin(), body_text.end(), body_text.begin(), ::tolower);
    cout << body_text << endl;
    art1.setID(paperID);
    art1.setTitle(titleName);
    art1.setBody(body_text);
    const rapidjson::Value& attributes = document["entities"]["persons"];
    int counter = 1;
    for (rapidjson::Value::ConstValueIterator itr = attributes.Begin(); itr != attributes.End(); ++itr) {
        const rapidjson::Value& attribute = *itr;
       // cout<<"Author "<<counter<<endl;
        for (rapidjson::Value::ConstMemberIterator itr2 = attribute.MemberBegin(); itr2 != attribute.MemberEnd(); ++itr2) {
            if(itr2->name.IsString() && itr2->value.IsString()){
                if(strlen(itr2 -> value.GetString()) > 0)
                    art1.addPeople(itr2->value.GetString());
            }
        }
        counter ++;
    }
    articles.push_back(art1);
}

void rwfile::print_filenames(string path) {
    for (const auto& dirEntry : fs::recursive_directory_iterator(path)){
        if(!is_directory(dirEntry)){
            string filename = dirEntry.path().c_str();
            parse(filename);
        }
    }
    cout << articles.size() << endl;
}
