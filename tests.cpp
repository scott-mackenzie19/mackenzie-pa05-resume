//
// Created by Kate Bouis on 11/15/21.
//

#include "catch.hpp"
#include "DSAvlTree.h"

TEST_CASE ("DSAvlTree") {
    DSAvlTree<int> tree;
    // globally create tree
    tree.insert(5);
    tree.insert(4);
    tree.insert(3);
    // each section represents one function
    SECTION ("test destructor") {

    }
    SECTION ("test height") {

    }
    SECTION ("test contains") {

    }
    SECTION ("test balance") {

    }
}