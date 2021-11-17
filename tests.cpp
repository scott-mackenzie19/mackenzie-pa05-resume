//
// Created by Kate Bouis on 11/15/21.
//

#include "catch.hpp"
#include "DSAvlTree.h"

TEST_CASE ("DSAvlTree") {
    DSAvlTree<int> tree;
    // globally create tree
    int& var1 = tree.insert(5);
    int& var2 = tree.insert(4);
    int& var3 = tree.insert(3);
    // each section represents one function
    SECTION ("test contains") {
        REQUIRE (tree.contains(3));
        REQUIRE (tree.contains(4));
        REQUIRE (tree.contains(5));
    }
}