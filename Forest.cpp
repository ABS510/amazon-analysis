#pragma once
#include "Forest.h"

Node* Forest::Node::makeNode(long itemId){
    Node* newnode = new Node;
    newnode->_itemId = itemId;
    newnode->_copIndex = 0;
}

/*
Function below takes in the .txt file and create the forest of all items by
mapping each itemId to their pointer in the forest
*/
void Forest::readFromFile(string file){
    ifstream myfile(file);
    long a, b;
    Node* createNode;
    while(!myfile.eof()){
        fin >> a;           //item id of left column
        fin >> b;           //item id of right column
        if(_itemsMap[a]){   //we previously already created this node in the forest
            if(!_itemsMap[b]){
                createNode = makeNode(b);
                _itemsMap[b] = createNode;
            }
            map[a]->_connected.push_back(_itemsMap[b]);
        }else{              //this is our first time seeing this itemId
            createNode = makeNode(a);
            _itemsMap[a] = createNode;
            if(!_itemsMap[b]){
                createNode = makeNode(b);
                _itemsMap[b] = createNode;
            }
            map[a]->_connected.push_back(_itemsMap[b]);
        }
    }
}