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
    }
    else if (choice == 2) {
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
    cout << "Enter your search term." << endl;
    string query;
    vector <article> artv;
    vector <article> peopleVec;
    vector <article> orgVec;
    vector <article> notVec;
    while (cin >> query) {
        if (query != "and" && query != "or" && query != "not" && query != "person" && query != "org") {
            Porter2Stemmer::trim(query);
            Porter2Stemmer::stem(query);

            if (!data.getTree().contains(query)) {
                cout << "no documents" << endl;
                menu();
            }
            unordered_map<string, article> temp1 = data.getTree().find(query);

            artv = findArticles(temp1);

        } else if (query == "and") {
            string and1;
            string and2;
            cin >> and1;
            cin >> and2;
            Porter2Stemmer::trim(and1);
            Porter2Stemmer::stem(and1);
            Porter2Stemmer::trim(and2);
            Porter2Stemmer::stem(and2);

            if (!data.getTree().contains(and1) || !data.getTree().contains(and2)) {
                cout << "no documents" << endl;
                menu();
            }

            unordered_map<string, article> temp1 = data.getTree().find(and1);
            unordered_map<string, article> temp2 = data.getTree().find(and2);

            vector <article> results1;
            vector <article> results2;

            results1 = findArticles (temp1);
            results2 = findArticles (temp2);

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
            Porter2Stemmer::trim(or1);
            Porter2Stemmer::stem(or1);
            Porter2Stemmer::trim(or2);
            Porter2Stemmer::stem(or2);
            if (!data.getTree().contains(or1) && !data.getTree().contains(or2)) {
                cout << "no documents" << endl;
                menu();
            }
            unordered_map<string, article> temp1 = data.getTree().find(or1);
            unordered_map<string, article> temp2 = data.getTree().find(or2);

            vector <article> results1;
            vector <article> results2;
            results1= findArticles(temp1);
            results2 = findArticles (temp2);

            for (int i = 0; i < results1.size(); i++) {
                for (int j = 0; j < results2.size(); j++)
                    if (results1[i] == results2[j]) results2.erase(results2.begin() + (j - 1));
            }
            for (int i = 0; i < results1.size(); i++) artv.emplace_back(results1[i]);
            for (int i = 0; i < results2.size(); i++) artv.emplace_back(results2[i]);

        } else if (query == "person") {
            string author;
            cin >> author;
            string wholeName = author;
            while (cin >> author) {
                if (author == "person" || author == "org" || author == "not") break;
                wholeName += " " + author;
            }
            for (int i = 0; i < data.getPeopleHash().at(author).size(); i++) {
                peopleVec.emplace_back(data.getPeopleHash().at(author).at(i));
            }
        } else if (query == "org") {
            string org;
            cin >> org;
            string fullOrg = org;
            while (cin >> org) {
                if (org == "person" || org == "org" || org == "not") break;
                fullOrg += " " + org;
            }
            for (int i = 0; i < data.getOrganizationsHash().at(org).size(); i++) {
                orgVec.emplace_back(data.getOrganizationsHash().at(org).at(i));
            }
        } else if (query == "not") {
            string notString;
            cin >> notString;
            Porter2Stemmer::trim(notString);
            Porter2Stemmer::stem(notString);
            if (!data.getTree().contains(notString)) {
                cout << "no documents" << endl;
                menu();
            }
            unordered_map<string, article> temp1 = data.getTree().find(notString);

            notVec = findArticles (temp1);
        }
    }

vector <article> temp;
    for (int i = 0; i < peopleVec.size(); i++) {
        for (int j = 0; j < artv.size(); j++) {
            if (peopleVec[i] == artv[j]) temp.emplace_back(peopleVec[i]);
        }
    }
    artv = temp;
    temp.clear();
    for (int i = 0; i < orgVec.size(); i++) {
        for (int j = 0; j < artv.size(); j++) {
            if (orgVec[i] == artv[j]) temp.emplace_back(orgVec[i]);
        }
    }
    artv = temp;
    temp.clear();

    for (int i = 0; i < notVec.size(); i++) {
        for (int j = 0; j < artv.size(); j++) {
           if (notVec[i] == artv[j]) artv.erase(artv.begin() + (j-1));
        }
    }
    sort(artv.begin(),artv.end());
    display(artv);
}
void query::stats() {
    rwfile stat1;
    cout << "We have " << stat1.getLines() << " files loaded into the engine." << endl;
    int numNodes = 0;
    ifstream input(path1);
    if (!input) exit(EXIT_FAILURE);
    string str;
    while (getline(input, str)) {
        numNodes++;
    }
    cout << "The Avl Tree is handling " << numNodes << " nodes." << endl;
    int numAuthors = 0;
    ifstream input2(path2);
    if (!input2) exit(EXIT_FAILURE);
    while (getline(input2, str)) {
        numAuthors++;
    }
    int numOrgs = 0;
    ifstream input3(path3);
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
    data.readTree(path1);
    data.readPeople(path2);
    data.readOrgs(path3);
}
 else if (choice == 2) {
    cout << "Enter path to your files." << endl;
    string path;
    cin >> path;
    data.loadStopWords();
    data.populate_tree(path);
}
 else {
    cout << "Bad answer. Back to menu." << endl;
}
}
void query::write() {
    cout << "Enter path to your files." << endl;
    string path;
    cin >> path;
    data.loadStopWords();
    data.populate_tree(path);
    data.printTree (path1, data.getTree().populateVector());
    data.printPeople (path2, data.getPeopleHash().populateVector());
    data.printOrgs (path3, data.getOrganizationsHash().populateVector());
}

vector <article> query::findArticles (unordered_map<string, article> temp){
    unordered_map<string, article> ::iterator ptr;
    vector <article> results;
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
        results.emplace_back(art1);
        fclose(fp);
    }
    return results;
}

void query::display(vector<article> vec){
    for (int i = 0; i < 15; i ++){
        cout << "Search Result " << i << ": " << vec[i].getTitle() << endl;
    }
    cout << "Select an article # or press '0' to return to menu." << endl;
    int artChoice;

    cin >> artChoice;
    if (artChoice == 0) menu();

    cout << vec[artChoice].getBody() << endl;

    cout << "If you would like to choose another article press 1. If you would like to go to menu press any other button." << endl;
    int articleOrMenu;
    cin >> articleOrMenu;
    if (articleOrMenu == 1) display(vec);
    else menu();
}