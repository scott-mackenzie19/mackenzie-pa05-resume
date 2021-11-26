//
// Created by Kate Bouis on 11/15/21.
//

#include "catch.hpp"
#include "DSAvlTree.h"
#include "string"
#include "DSHash.h"
using namespace std;

TEST_CASE ("DSAvlTree") {
    DSAvlTree<string, int> tree;
    // globally create tree
    int& var1 = tree.insert("yes");
    int& var2 = tree.insert("no");
    int& var3 = tree.insert("maybe");
    // each section represents one function
    SECTION ("test contains") {
        REQUIRE (tree.contains("yes"));
        REQUIRE (tree.contains("no"));
    }
}

TEST_CASE ("DSHash") {
    DSHash<string, int> hash;
    // globally create hash table
    hash.put("word", 1);
    hash.put("key", 2);
    hash.put("hello", 5);
    SECTION ("test get") {
        REQUIRE (hash.get("word"));
        REQUIRE (hash.get("key"));
        REQUIRE (!hash.get("data"));
    } SECTION ("test remove") {
        hash.remove("key");
        REQUIRE (!hash.get("key"));
    } SECTION ("test []") {
        REQUIRE (hash["word"] == 1);
        REQUIRE (hash["key"] == 2);
        REQUIRE (hash["hello"] != 4);
    }
}