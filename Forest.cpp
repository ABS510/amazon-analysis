#pragma once
#include "Forest.h"

Node* Forest::Node::makeNode(long itemId){
    Node* newnode = new Node;
    newnode->_itemId = itemId;
    newnode->_copIndex = 0;
}

/*
Set the limit for co-purchasing, this is the limit used for IDDFS
*/
void Forest::setCopLimit(long limit){
    _copLimit = limit;
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

void Forest::filter500(){
    //I am thinking IDDFS will be called here
    //this is probably just a loop going through all the items, getting their Node*, then calling IDDFS on those Node*
}

/*
Perform IDDFS starting from the <start> node with the given <limit> and count the number of distinct nodes that are linked to <start>
Set the count of distinct linked nodes within the Node class's <_copIndex>
Return count
Is it possible(easier) to implement using recursion? 
*/
int IDDFS(Node* start, int limit){
    int count = 0;
    if(limit == 1){
        count = start->_connected.size();
        //start->_copIndex = count;
        return count;
    }
    while(limit>1){
        for(unsigned long i = 0; i<start->_connected.size(); i++){
            Node* n = start->_connected[i];
            count = count + IDDFS(n, limit-1);
        }
    }
    
}
