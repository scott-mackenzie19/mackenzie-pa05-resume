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

DSHash<string, vector<article>> &rwfile::getOrganizationsHash() {
     return this->Organizations;
}

DSHash<string, vector<article>> &rwfile::getPeopleHash() {
    return this->People;
}

void rwfile::setOrganizations(DSHash<string, vector<article>> &table) {
    this->Organizations = table;
}

void rwfile::setPeople(DSHash<string, vector<article>> &table) {
    this->People = table;
}

void rwfile::addPeople(string &Person, article art) {
    vector<article> vec;
    vec.push_back(art);
    // if not contains, put, if contains, second.push_back
    if (!People.get(Person)) People.put(Person, vec);
    else People.at(Person).push_back(art);
}

void rwfile::addOrg(string &Org, article art) {
    vector<article> vec;
    vec.push_back(art);
    // if not contains, put, if contains, second.push_back
    if (!Organizations.get(Org)) Organizations.put(Org, vec);
    else Organizations.at(Org).push_back(art);
}

void rwfile::parse(const string &filename) {
    ///
    ///used TA Christian's reference
    ///

    FILE *fp = fopen(filename.c_str(), "rb");
    char buffer[35540];
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
    string filePath = filename;
    art1.setPath(filePath);
    const rapidjson::Value &attributes = document["entities"]["persons"];
    const rapidjson::Value &holder = document["entities"]["organizations"];
    int counter = 1;
    for (rapidjson::Value::ConstValueIterator itr = attributes.Begin(); itr != attributes.End(); ++itr) {
        const rapidjson::Value &attribute = *itr;
        // cout<<"Author "<<counter<<endl;
        for (rapidjson::Value::ConstMemberIterator itr2 = attribute.MemberBegin();
             itr2 != attribute.MemberEnd(); ++itr2) {
            if (itr2->name.IsString() && itr2->value.IsString()) {
                if (strlen(itr2->value.GetString()) > 0) {
                    // addPeople needs a second parameter now, i changed it to work with hashmaps
                    // add for second parameter the object of the article that this person is found in. not sure how to do that
                    //make a copy
                    string tempor = itr2->value.GetString();
                    addPeople(tempor, art1);
                }
            }
        }
        counter++;
    }
    lines = counter;
    for (rapidjson::Value::ConstValueIterator itr = holder.Begin(); itr != holder.End(); ++itr) {
        const rapidjson::Value &hold = *itr;
        // cout<<"Author "<<counter<<endl;
        for (rapidjson::Value::ConstMemberIterator itr2 = hold.MemberBegin();
             itr2 != hold.MemberEnd(); ++itr2) {
            if (itr2->name.IsString() && itr2->value.IsString()) {
                if (strlen(itr2->value.GetString()) > 0) {
                    // addPeople needs a second parameter now, i changed it to work with hashmaps
                    // add for second parameter the object of the article that this person is found in. not sure how to do that
                    //make a copy
                    string tempor = itr2->value.GetString();
                    addOrg(tempor, art1);
                }
            }
        }
        counter++;
    }
    tokenize_file(art1);
    fclose(fp);
}

string holder;

void rwfile::populate_tree(const string &path) { //first custom
    int num = 0;
    int count = 0;
    for (const auto &dirEntry : fs::recursive_directory_iterator(path)) {
        if (!is_directory(dirEntry) && holder.find(dirEntry.path().c_str()) == string::npos) {
            string filename = dirEntry.path().c_str();
            parse(filename);
            num++;
            cout << num << endl;
            count = 1;
            holder.append(dirEntry.path().c_str());
        } else if (is_directory(dirEntry) && holder.find(dirEntry.path().c_str()) ==
                                             string::npos) { //if file is a folder and not already searched, function repeats
            holder.append(dirEntry.path().c_str());
            cout << "first" << endl;
            populate_tree(dirEntry.path().c_str());
        } else {}
    }
}


void rwfile::tokenize_file(article &file) {
    stringstream ss(file.getBody());
    LOOP:
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
            temp1.setPath(file.getPath());
            Porter2Stemmer::trim(word);
            for (int i = 0; i < stopWords.size(); i++) {
                //cout << stopWords[i] << endl;
                if (stopWords[i] == word) {
                    goto LOOP;
                }
            }
            Porter2Stemmer::stem(word);
            unordered_map<string, article> value;
           // wordTree.insert(word, value).insert(make_pair(file.getID(), temp1));

            unordered_map<string, article>*  ptr= &wordTree.insert(word, value);
            if (ptr->empty()) { //if map of word empty
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

void rwfile::printTree(string arg, vector<pair<string, unordered_map<string, article>>> vec) {
    ofstream output(arg);
    if (!output) exit(EXIT_FAILURE);
    for (int i = 0; i < vec.size(); i++) {
        output << vec[i].first << ";";
        auto it = vec[i].second.begin();
        while (it != vec[i].second.end()) {
            output << it->second.getPath() << "~" << it->second.getNumOccurences() << ":" << it->second.getID() << ":";
            ++it;
        }
        output << endl;
    }
    output.close();
}

void rwfile::printPeople(string arg, vector<pair<string, vector<article>>> vec) {
    ofstream output(arg);
    if (!output) exit(EXIT_FAILURE);
    for (int i = 0; i < vec.size(); i++) {
        output << vec[i].first << ";";
        auto it = vec[i].second.begin();
        while (it != vec[i].second.end()) {
            output << it->getPath() << ":";
            ++it;
        }
        output << endl;
    }
    output.close();
}

void rwfile::printOrgs(string arg, vector<pair<string, vector<article>>> vec) {
    ofstream output(arg);
    if (!output) exit(EXIT_FAILURE);
    for (int i = 0; i < vec.size(); i++) {
        output << vec[i].first << ";";
        auto it = vec[i].second.begin();
        while (it != vec[i].second.end()) {
            output << it->getPath() << ":";
            it++;
        }
        output << endl;
    }
    output.close();
}

void rwfile::set_tree(DSAvlTree<string, unordered_map<string, article>> &table) {
    this->wordTree = table;
}

void rwfile::loadStopWords() {
    string stop = "able\n"
                  "about\n"
                  "above\n"
                  "abroad\n"
                  "according\n"
                  "accordingly\n"
                  "across\n"
                  "actually\n"
                  "adj\n"
                  "after\n"
                  "afterwards\n"
                  "again\n"
                  "against\n"
                  "ago\n"
                  "ahead\n"
                  "ain't\n"
                  "all\n"
                  "allow\n"
                  "allows\n"
                  "almost\n"
                  "alone\n"
                  "along\n"
                  "alongside\n"
                  "already\n"
                  "also\n"
                  "although\n"
                  "always\n"
                  "am\n"
                  "amid\n"
                  "amidst\n"
                  "among\n"
                  "amongst\n"
                  "an\n"
                  "and\n"
                  "another\n"
                  "any\n"
                  "anybody\n"
                  "anyhow\n"
                  "anyone\n"
                  "anything\n"
                  "anyway\n"
                  "anyways\n"
                  "anywhere\n"
                  "apart\n"
                  "appear\n"
                  "appreciate\n"
                  "appropriate\n"
                  "are\n"
                  "aren't\n"
                  "around\n"
                  "as\n"
                  "a's\n"
                  "aside\n"
                  "ask\n"
                  "asking\n"
                  "associated\n"
                  "at\n"
                  "available\n"
                  "away\n"
                  "awfully\n"
                  "back\n"
                  "backward\n"
                  "backwards\n"
                  "be\n"
                  "became\n"
                  "because\n"
                  "become\n"
                  "becomes\n"
                  "becoming\n"
                  "been\n"
                  "before\n"
                  "beforehand\n"
                  "begin\n"
                  "behind\n"
                  "being\n"
                  "believe\n"
                  "below\n"
                  "beside\n"
                  "besides\n"
                  "best\n"
                  "better\n"
                  "between\n"
                  "beyond\n"
                  "both\n"
                  "brief\n"
                  "but\n"
                  "by\n"
                  "came\n"
                  "can\n"
                  "cannot\n"
                  "cant\n"
                  "can't\n"
                  "caption\n"
                  "cause\n"
                  "causes\n"
                  "certain\n"
                  "certainly\n"
                  "changes\n"
                  "clearly\n"
                  "c'mon\n"
                  "co\n"
                  "co.\n"
                  "com\n"
                  "come\n"
                  "comes\n"
                  "concerning\n"
                  "consequently\n"
                  "consider\n"
                  "considering\n"
                  "contain\n"
                  "containing\n"
                  "contains\n"
                  "corresponding\n"
                  "could\n"
                  "couldn't\n"
                  "course\n"
                  "c's\n"
                  "currently\n"
                  "dare\n"
                  "daren't\n"
                  "definitely\n"
                  "described\n"
                  "despite\n"
                  "did\n"
                  "didn't\n"
                  "different\n"
                  "directly\n"
                  "do\n"
                  "does\n"
                  "doesn't\n"
                  "doing\n"
                  "done\n"
                  "don't\n"
                  "down\n"
                  "downwards\n"
                  "during\n"
                  "each\n"
                  "edu\n"
                  "eg\n"
                  "eight\n"
                  "eighty\n"
                  "either\n"
                  "else\n"
                  "elsewhere\n"
                  "end\n"
                  "ending\n"
                  "enough\n"
                  "entirely\n"
                  "especially\n"
                  "et\n"
                  "etc\n"
                  "even\n"
                  "ever\n"
                  "evermore\n"
                  "every\n"
                  "everybody\n"
                  "everyone\n"
                  "everything\n"
                  "everywhere\n"
                  "ex\n"
                  "exactly\n"
                  "example\n"
                  "except\n"
                  "fairly\n"
                  "far\n"
                  "farther\n"
                  "few\n"
                  "fewer\n"
                  "fifth\n"
                  "first\n"
                  "five\n"
                  "followed\n"
                  "following\n"
                  "follows\n"
                  "for\n"
                  "forever\n"
                  "former\n"
                  "formerly\n"
                  "forth\n"
                  "forward\n"
                  "found\n"
                  "four\n"
                  "from\n"
                  "further\n"
                  "furthermore\n"
                  "get\n"
                  "gets\n"
                  "getting\n"
                  "given\n"
                  "gives\n"
                  "go\n"
                  "goes\n"
                  "going\n"
                  "gone\n"
                  "got\n"
                  "gotten\n"
                  "greetings\n"
                  "had\n"
                  "hadn't\n"
                  "half\n"
                  "happens\n"
                  "hardly\n"
                  "has\n"
                  "hasn't\n"
                  "have\n"
                  "haven't\n"
                  "having\n"
                  "he\n"
                  "he'd\n"
                  "he'll\n"
                  "hello\n"
                  "help\n"
                  "hence\n"
                  "her\n"
                  "here\n"
                  "hereafter\n"
                  "hereby\n"
                  "herein\n"
                  "here's\n"
                  "hereupon\n"
                  "hers\n"
                  "herself\n"
                  "he's\n"
                  "hi\n"
                  "him\n"
                  "himself\n"
                  "his\n"
                  "hither\n"
                  "hopefully\n"
                  "how\n"
                  "howbeit\n"
                  "however\n"
                  "hundred\n"
                  "i'd\n"
                  "ie\n"
                  "if\n"
                  "ignored\n"
                  "i'll\n"
                  "i'm\n"
                  "immediate\n"
                  "in\n"
                  "inasmuch\n"
                  "inc\n"
                  "inc.\n"
                  "indeed\n"
                  "indicate\n"
                  "indicated\n"
                  "indicates\n"
                  "inner\n"
                  "inside\n"
                  "insofar\n"
                  "instead\n"
                  "into\n"
                  "inward\n"
                  "is\n"
                  "isn't\n"
                  "it\n"
                  "it'd\n"
                  "it'll\n"
                  "its\n"
                  "it's\n"
                  "itself\n"
                  "i've\n"
                  "just\n"
                  "k\n"
                  "keep\n"
                  "keeps\n"
                  "kept\n"
                  "know\n"
                  "known\n"
                  "knows\n"
                  "last\n"
                  "lately\n"
                  "later\n"
                  "latter\n"
                  "latterly\n"
                  "least\n"
                  "less\n"
                  "lest\n"
                  "let\n"
                  "let's\n"
                  "like\n"
                  "liked\n"
                  "likely\n"
                  "likewise\n"
                  "little\n"
                  "look\n"
                  "looking\n"
                  "looks\n"
                  "low\n"
                  "lower\n"
                  "ltd\n"
                  "made\n"
                  "mainly\n"
                  "make\n"
                  "makes\n"
                  "many\n"
                  "may\n"
                  "maybe\n"
                  "mayn't\n"
                  "me\n"
                  "mean\n"
                  "meantime\n"
                  "meanwhile\n"
                  "merely\n"
                  "might\n"
                  "mightn't\n"
                  "mine\n"
                  "minus\n"
                  "miss\n"
                  "more\n"
                  "moreover\n"
                  "most\n"
                  "mostly\n"
                  "mr\n"
                  "mrs\n"
                  "much\n"
                  "must\n"
                  "mustn't\n"
                  "my\n"
                  "myself\n"
                  "name\n"
                  "namely\n"
                  "nd\n"
                  "near\n"
                  "nearly\n"
                  "necessary\n"
                  "need\n"
                  "needn't\n"
                  "needs\n"
                  "neither\n"
                  "never\n"
                  "neverf\n"
                  "neverless\n"
                  "nevertheless\n"
                  "new\n"
                  "next\n"
                  "nine\n"
                  "ninety\n"
                  "no\n"
                  "nobody\n"
                  "non\n"
                  "none\n"
                  "nonetheless\n"
                  "noone\n"
                  "no-one\n"
                  "nor\n"
                  "normally\n"
                  "not\n"
                  "nothing\n"
                  "notwithstanding\n"
                  "novel\n"
                  "now\n"
                  "nowhere\n"
                  "obviously\n"
                  "of\n"
                  "off\n"
                  "often\n"
                  "oh\n"
                  "ok\n"
                  "okay\n"
                  "old\n"
                  "on\n"
                  "once\n"
                  "one\n"
                  "ones\n"
                  "one's\n"
                  "only\n"
                  "onto\n"
                  "opposite\n"
                  "or\n"
                  "other\n"
                  "others\n"
                  "otherwise\n"
                  "ought\n"
                  "oughtn't\n"
                  "our\n"
                  "ours\n"
                  "ourselves\n"
                  "out\n"
                  "outside\n"
                  "over\n"
                  "overall\n"
                  "own\n"
                  "particular\n"
                  "particularly\n"
                  "past\n"
                  "per\n"
                  "perhaps\n"
                  "placed\n"
                  "please\n"
                  "plus\n"
                  "possible\n"
                  "presumably\n"
                  "probably\n"
                  "provided\n"
                  "provides\n"
                  "que\n"
                  "quite\n"
                  "qv\n"
                  "rather\n"
                  "rd\n"
                  "re\n"
                  "really\n"
                  "reasonably\n"
                  "recent\n"
                  "recently\n"
                  "regarding\n"
                  "regardless\n"
                  "regards\n"
                  "relatively\n"
                  "respectively\n"
                  "right\n"
                  "round\n"
                  "said\n"
                  "same\n"
                  "saw\n"
                  "say\n"
                  "saying\n"
                  "says\n"
                  "second\n"
                  "secondly\n"
                  "see\n"
                  "seeing\n"
                  "seem\n"
                  "seemed\n"
                  "seeming\n"
                  "seems\n"
                  "seen\n"
                  "self\n"
                  "selves\n"
                  "sensible\n"
                  "sent\n"
                  "serious\n"
                  "seriously\n"
                  "seven\n"
                  "several\n"
                  "shall\n"
                  "shan't\n"
                  "she\n"
                  "she'd\n"
                  "she'll\n"
                  "she's\n"
                  "should\n"
                  "shouldn't\n"
                  "since\n"
                  "six\n"
                  "so\n"
                  "some\n"
                  "somebody\n"
                  "someday\n"
                  "somehow\n"
                  "someone\n"
                  "something\n"
                  "sometime\n"
                  "sometimes\n"
                  "somewhat\n"
                  "somewhere\n"
                  "soon\n"
                  "sorry\n"
                  "specified\n"
                  "specify\n"
                  "specifying\n"
                  "still\n"
                  "sub\n"
                  "such\n"
                  "sup\n"
                  "sure\n"
                  "take\n"
                  "taken\n"
                  "taking\n"
                  "tell\n"
                  "tends\n"
                  "th\n"
                  "than\n"
                  "thank\n"
                  "thanks\n"
                  "thanx\n"
                  "that\n"
                  "that'll\n"
                  "thats\n"
                  "that's\n"
                  "that've\n"
                  "the\n"
                  "their\n"
                  "theirs\n"
                  "them\n"
                  "themselves\n"
                  "then\n"
                  "thence\n"
                  "there\n"
                  "thereafter\n"
                  "thereby\n"
                  "there'd\n"
                  "therefore\n"
                  "therein\n"
                  "there'll\n"
                  "there're\n"
                  "theres\n"
                  "there's\n"
                  "thereupon\n"
                  "there've\n"
                  "these\n"
                  "they\n"
                  "they'd\n"
                  "they'll\n"
                  "they're\n"
                  "they've\n"
                  "thing\n"
                  "things\n"
                  "think\n"
                  "third\n"
                  "thirty\n"
                  "this\n"
                  "thorough\n"
                  "thoroughly\n"
                  "those\n"
                  "though\n"
                  "three\n"
                  "through\n"
                  "throughout\n"
                  "thru\n"
                  "thus\n"
                  "till\n"
                  "to\n"
                  "together\n"
                  "too\n"
                  "took\n"
                  "toward\n"
                  "towards\n"
                  "tried\n"
                  "tries\n"
                  "truly\n"
                  "try\n"
                  "trying\n"
                  "t's\n"
                  "twice\n"
                  "two\n"
                  "un\n"
                  "under\n"
                  "underneath\n"
                  "undoing\n"
                  "unfortunately\n"
                  "unless\n"
                  "unlike\n"
                  "unlikely\n"
                  "until\n"
                  "unto\n"
                  "up\n"
                  "upon\n"
                  "upwards\n"
                  "us\n"
                  "use\n"
                  "used\n"
                  "useful\n"
                  "uses\n"
                  "using\n"
                  "usually\n"
                  "v\n"
                  "value\n"
                  "various\n"
                  "versus\n"
                  "very\n"
                  "via\n"
                  "viz\n"
                  "vs\n"
                  "want\n"
                  "wants\n"
                  "was\n"
                  "wasn't\n"
                  "way\n"
                  "we\n"
                  "we'd\n"
                  "welcome\n"
                  "well\n"
                  "we'll\n"
                  "went\n"
                  "were\n"
                  "we're\n"
                  "weren't\n"
                  "we've\n"
                  "what\n"
                  "whatever\n"
                  "what'll\n"
                  "what's\n"
                  "what've\n"
                  "when\n"
                  "whence\n"
                  "whenever\n"
                  "where\n"
                  "whereafter\n"
                  "whereas\n"
                  "whereby\n"
                  "wherein\n"
                  "where's\n"
                  "whereupon\n"
                  "wherever\n"
                  "whether\n"
                  "which\n"
                  "whichever\n"
                  "while\n"
                  "whilst\n"
                  "whither\n"
                  "who\n"
                  "who'd\n"
                  "whoever\n"
                  "whole\n"
                  "who'll\n"
                  "whom\n"
                  "whomever\n"
                  "who's\n"
                  "whose\n"
                  "why\n"
                  "will\n"
                  "willing\n"
                  "wish\n"
                  "with\n"
                  "within\n"
                  "without\n"
                  "wonder\n"
                  "won't\n"
                  "would\n"
                  "wouldn't\n"
                  "yes\n"
                  "yet\n"
                  "you\n"
                  "you'd\n"
                  "you'll\n"
                  "your\n"
                  "you're\n"
                  "yours\n"
                  "yourself\n"
                  "yourselves\n"
                  "you've\n"
                  "zero";
    stringstream ss(stop);
    while (ss.good()) {
        string word;
        getline(ss, word);
        Porter2Stemmer::trim(word);
        stopWords.emplace_back(word);
    }
}



/**
  * below was throwing errors so it's commented out so we can fix other problems before coming back to it
  */

void rwfile::readTree(const string& arg) {
    ifstream input (arg);
    if (!input) exit (EXIT_FAILURE);
    int numLines = 0;
    string str;
    while (getline (input, str)) {
        stringstream ss(str);
        string temp;
        getline(ss, temp, ';'); //word
        while (ss.good()) {
            string path;
            string ID;
            string tempNum;
            getline(ss, path, '~');
            getline(ss, tempNum, ':');
            getline(ss, ID, ':');
            article art1;
           if (!tempNum.empty()) {
               int numOccurrences = stoi(tempNum);
               art1.setNum(numOccurrences);
           }
            art1.setPath(path);
            art1.setID(ID);
            unordered_map<string, article> index_me;
         //   cout << temp << endl;
            wordTree.insert(temp, index_me).insert(make_pair(art1.getID(), art1));
        }
        numLines++;
    }
    input.close();
}

void rwfile::readPeople(string arg) {
    ifstream input(arg);
    if (!input) exit(EXIT_FAILURE);
    string str;
    while (getline(input, str)) {
        stringstream ss(str);
        string temp;
        getline(ss, temp, ';');
        string temp2;
        while (getline(ss, temp2, ':')) {
            string path = temp2.substr(0, temp2.find(':'));
            FILE *fp = fopen(path.c_str(), "rb");
            if (fp == nullptr) {
                continue;
            }
            char buffer[35540];
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
            string filePath = path;
            art1.setPath(filePath);
            addPeople(temp, art1);
            fclose(fp);
        }
    }
}

void rwfile::readOrgs(string arg) {
    ifstream input(arg);
    if (!input) exit(EXIT_FAILURE);
    string str;
    while (getline(input, str)) {
        stringstream ss(str);
        string temp;
        getline(ss, temp, ';');
        string temp2;
        while (getline(ss, temp2, ':')) {
            string path = temp2.substr(0, temp2.find(':'));
            FILE *fp = fopen(path.c_str(), "rb");
            char buffer[35540];
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
            string filePath = path;
            art1.setPath(filePath);

            addOrg(temp, art1);
            fclose(fp);
        }
    }
}

int rwfile::getLines() {
    return lines;
}