#include "../cs225/catch/catch.hpp"

#include "../Forest.h"

#include <iostream>
// #include <vector>
#include <unordered_map>
// #include <fstream>
// #include <string>

TEST_CASE("Checking Initialization 1"){
    Forest forest = Forest();
    REQUIRE(0 == forest.get_copLimit());
}

TEST_CASE("Checking Initialization 2"){
    Forest forest1 = Forest(1);
    Forest forest2 = Forest(2);
    Forest forest3 = Forest(3);
    REQUIRE(1 == forest1.get_copLimit());
    REQUIRE(2 == forest2.get_copLimit());
    REQUIRE(3 == forest3.get_copLimit());
}

TEST_CASE("Checking Node Creation 1"){
    Forest forest = Forest();
    Forest::Node* createNode = new Forest::Node();
    forest.set_itemsMap(1, createNode);

    REQUIRE(createNode == forest.get_itemsMap()[1]);
}

TEST_CASE("Checking Node Creation 2"){
    Forest forest = Forest();
    vector<Forest::Node*> nodes;

    for(long i = 0; i<5; i++){
        Forest::Node* createNode = new Forest::Node(i);
        nodes.push_back(createNode);
        forest.set_itemsMap(i, createNode);
    }

    REQUIRE(nodes[0] == forest.get_itemsMap()[0]);
    REQUIRE(nodes[4] == forest.get_itemsMap()[4]);
    REQUIRE(nodes[1] == forest.get_itemsMap()[1]);
    REQUIRE(nodes[3] == forest.get_itemsMap()[3]);
    REQUIRE(nodes[2] == forest.get_itemsMap()[2]);

    REQUIRE(5 == forest.get_itemsMap().size());
}

TEST_CASE("Checking readFromFile 1"){
    Forest forest = Forest();
    forest.readFromFile("tests/sample_testcase1.txt");
    REQUIRE(3 == forest.get_itemsMap()[1]->_connected.size());
    REQUIRE(3 == forest.get_itemsMap()[2]->_connected.size());
    REQUIRE(2 == forest.get_itemsMap()[3]->_connected.size());
    REQUIRE(8 == forest.get_itemsMap().size());
}

TEST_CASE("Checking IDDFS Limit 1"){
    Forest forest = Forest();
    forest.readFromFile("tests/sample_testcase1.txt");

    // unordered_map<Forest::Node*, bool> bookkeep1;
    // unordered_map<Forest::Node*, bool> bookkeep2;
    // unordered_map<Forest::Node*, bool> bookkeep3;
    
    // std::cout<<forest.IDDFS(forest.get_itemsMap()[0], 3);
    REQUIRE(3 == forest.IDDFS(forest.get_itemsMap()[1], 1)); 
    REQUIRE(3 == forest.IDDFS(forest.get_itemsMap()[2], 1));
    REQUIRE(2 == forest.IDDFS(forest.get_itemsMap()[3], 1));
    // REQUIRE(3 == forest.IDDFS(forest.get_itemsMap()[1], 1));
    // REQUIRE(3 == forest.IDDFS(forest.get_itemsMap()[2], 1));
    // REQUIRE(2 == forest.IDDFS(forest.get_itemsMap()[3], 1));
}

TEST_CASE("Checking IDDFS Limit 2.1"){
    Forest forest = Forest();
    forest.readFromFile("tests/sample_testcase1.txt");

    // std::cout<<forest.IDDFS(forest.get_itemsMap()[0], 3);
    REQUIRE(5 == forest.IDDFS(forest.get_itemsMap()[1], 2));
    REQUIRE(5 == forest.IDDFS(forest.get_itemsMap()[3], 2));
    REQUIRE(5 == forest.IDDFS(forest.get_itemsMap()[2], 2));
}

TEST_CASE("Checking IDDFS Limit 2.2"){
    Forest forest = Forest();
    forest.readFromFile("tests/sample_testcase2.txt");

    REQUIRE(6 == forest.IDDFS(forest.get_itemsMap()[1], 3));
    REQUIRE(5 == forest.IDDFS(forest.get_itemsMap()[1], 2));
}

TEST_CASE("Checking IDDFS testcase 3 big"){
    Forest forest = Forest();
    forest.readFromFile("tests/sample_testcase3.txt");
    unordered_map<Forest::Node*, bool> bookkeep1;

    REQUIRE(6 == forest.IDDFS(forest.get_itemsMap()[1], 2));
    // bookkeep1.clear();
    REQUIRE(6 == forest.IDDFS(forest.get_itemsMap()[1], 3));
}