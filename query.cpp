//
// Created by Kate Bouis on 12/1/21.
//

#include "query.h"

void query::menu() {
    cout << "Welcome to our search engine! Please choose an option to get started: " << endl;
    cout << "1. Load Data" << endl;
    cout << "2. Execute Query" << endl;
    cout << "3. Show Stats" << endl;
    cout << "4. Write Persistence File" << endl;
    cout << "5. Exit" << endl;
    int choice;
    cin >> choice;
    if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5) {
        cout << "Invalid Choice. Try Again.";
        menu();
    }
    else if (choice == 1) {
        load();
        menu();
    } else if (choice == 2) {
        handleBool();
        menu();
    } else if (choice == 3) {
        stats();
        menu();
    } else if (choice == 4) {
        write();
        menu();
    } else if (choice == 5) {
        cout << "Bye! Have a good day.";
    }
}

void query::handleBool() {
    cout << "Enter your search term.";
    rwfile data;
    string query;
    vector <article> artv;
    while (cin >> query) {
        Porter2Stemmer::trim(query);
        Porter2Stemmer::stem(query);
        if (query == "and") {
            string and1;
            string and2;
            cin >> and1;
            cin >> and2;
            Porter2Stemmer::trim(and1);
            Porter2Stemmer::stem(and2);
            Porter2Stemmer::trim(and1);
            Porter2Stemmer::stem(and2);

            unordered_map<string, article> temp1 = data.getTree().find(and1);
            unordered_map<string, article> temp2 = data.getTree().find(and2);
            unordered_map<string, article> ::iterator ptr;

            if (!data.getTree().contains(and1) || !data.getTree().contains(and2)) {
                cout << "no documents" << endl;
                menu();
            }
            vector <article> results1;
            vector <article> results2;
            for (ptr = temp1.begin(); ptr != temp1.end(); ptr++) {
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
                results1.emplace_back(art1);
                fclose(fp);
            }
            for (ptr = temp2.begin(); ptr!= temp2.end(); ptr++) {
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
                results2.emplace_back(art1);
                fclose(fp);
            }
            for (int i = 0; i < results1.size(); i++) {
                for (int j = 0; j < results2.size(); i++) {
                    if (results1[i] == results2 [j]) artv.emplace_back(results1[i]);
                }
            }

        } else if (query == "or") {
            string or1;
            string or2;
            cin >> or1;
            cin >> or2;
            unordered_map<string, article> temp1 = data.getTree().find(or1);
            unordered_map<string, article> temp2 = data.getTree().find(or2);
            unordered_map<string, article> ::iterator ptr;

            if (!data.getTree().contains(or1) && !data.getTree().contains(or2)) {
                cout << "no documents" << endl;
                menu();
            }
            vector <article> results1;
            vector <article> results2;
            for (ptr = temp1.begin(); ptr != temp1.end(); ptr++) {
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
                results1.emplace_back(art1);
                fclose(fp);
            }
            for (ptr = temp2.begin(); ptr!= temp2.end(); ptr++) {
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
                results2.emplace_back(art1);
                fclose(fp);
            }
            for (int i = 0; i < results1.size(); i++) {
                for (int j = 0; j < results2.size(); j++)
                    if (results1[i] == results2[j]) results2.erase(results2.begin() + (j - 1));
            }
            for (int i = 0; i < results1.size(); i++) artv.emplace_back(results1[i]);
            for (int i = 0; i < results2.size(); i++) artv.emplace_back(results2[i]);

        } else if (query == "person") {

        } else if (query == "org") {

        } else if (query == "not") {

        } else {

        }
    }
}
void query::stats() {
    rwfile stat1;
    cout << "We have " << stat1.getLines() << " files loaded into the engine." << endl;
    int numNodes = 0;
    ifstream input("output.txt");
    if (!input) exit(EXIT_FAILURE);
    string str;
    while (getline(input, str)) {
        numNodes++;
    }
    cout << "The Avl Tree is handling " << numNodes << " nodes." << endl;
    int numAuthors = 0;
    ifstream input2("outputPeople.txt");
    if (!input2) exit(EXIT_FAILURE);
    while (getline(input2, str)) {
        numAuthors++;
    }
    int numOrgs = 0;
    ifstream input3("outputOrgs.txt");
    if (!input3) exit (EXIT_FAILURE);
    while (getline(input3, str)) {
        numOrgs++;
    }
    cout << "We have files from "  << numAuthors << " authors and " << numOrgs << " organizations." << endl;
}
void query::load() {
cout << "Press 1 if you would like to load from persistence files and 2 if you would like to load from files on your computer." << endl;
int choice;
cin >> choice;
if (choice == 1) {
    rwfile data;
    data.readTree("output.txt");
    data.readPeople("outputPeople.txt");
    data.readOrgs("outputOrgs.txt");
} else if (choice == 2) {
    cout << "Enter path to your files." << endl;
    string path;
    cin >> path;
    rwfile data;
    data.loadStopWords();
    data.populate_tree(path);
} else {
    cout << "Bad answer. Back to menu." << endl;
}
}
void query::write() {
    cout << "Enter path to your files." << endl;
    string path;
    cin >> path;
    rwfile data;
    data.loadStopWords();
    data.populate_tree(path);
    data.printTree ("output.txt", data.getTree().populateVector());
    data.printPeople ("outputPeople.txt", data.getPeopleHash().populateVector());
    data.printOrgs ("outputOrgs.txt", data.getOrganizationsHash().populateVector());
}