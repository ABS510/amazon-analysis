#include "../cs225/catch/catch.hpp"

#include "../Forest.h"

#include <iostream>
// #include <vector>
// #include <unordered_map>
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
    forest.readFromFile("tests/sample_verysmall.txt");

    REQUIRE(8 == forest.get_itemsMap().size());
}

TEST_CASE("Checking readFromFile 2"){

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
    forest.readFromFile("tests/sample_verysmall.txt");

    REQUIRE(8 == forest.get_itemsMap().size());
}

TEST_CASE("Checking readFromFile 2"){
    
}