//
// Created by dalla on 11/14/2021.
//

#include "rwfile.h"
#include "string"
#include "include/rapidjson/document.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include "include/rapidjson/document.h"
#include "include/rapidjson/istreamwrapper.h"
#include "include/rapidjson/stringbuffer.h"
using namespace std;
namespace fs = std::filesystem;
using namespace rapidjson;

void parse(string filename) {
    ifstream ifss(filename);
    IStreamWrapper isw(ifss);
    Document document;
    document.ParseStream(isw);
    string paperID = document["uuid"].GetString();
    string titleName = document["title"].GetString();
    //cout << "Paper id: " << paperID << endl;
    //cout << "Title name: "<< titleName << endl;
    string body_text = document["text"].GetString();
    const rapidjson::Value& attributes = document["entities"]["persons"];
    int counter = 1;
    for (rapidjson::Value::ConstValueIterator itr = attributes.Begin(); itr != attributes.End(); ++itr) {
        const rapidjson::Value& attribute = *itr;
        cout<<"Author "<<counter<<endl;
        for (rapidjson::Value::ConstMemberIterator itr2 = attribute.MemberBegin(); itr2 != attribute.MemberEnd(); ++itr2) {
            if(itr2->name.IsString() && itr2->value.IsString()){
                if(strlen(itr2 -> value.GetString()) > 0)
                    cout << "  "<<itr2->name.GetString() << " : " << itr2->value.GetString() << endl;
            }
        }
        counter ++;
    }
    //cout << endl << body_text << endl;
}

void rwfile::print_filenames(string path) {
    for (const auto& dirEntry : fs::recursive_directory_iterator(path)){
        if(!is_directory(dirEntry)){
            string filename = dirEntry.path().c_str();
            parse(filename);
        }
    }
}
