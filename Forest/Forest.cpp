#pragma once
#include "Forest.h"
#include <unordered_map>
#include <vector>
#include <algorithm>

// Node* Forest::Node::makeNode(long itemId){
//     Node* newnode = new Node;
//     newnode->_itemId = itemId;
//     newnode->_copIndex = 0;
// }


Forest::Node(long itemID){
    newnode->_itemId = itemId;
    newnode->_copIndex = 0;
}

Forest::Node(){}

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
                createNode = new Forest::Node(b);
                _itemsMap[b] = createNode;
            }
            map[a]->_connected.push_back(_itemsMap[b]);
            
        }else{              //this is our first time seeing this itemId
            createNode = new Forest::Node(a);
            _itemsMap[a] = createNode;
            if(!_itemsMap[b]){
                createNode = new Forest::Node(b);
                _itemsMap[b] = createNode;
            }
            map[a]->_connected.push_back(_itemsMap[b]);
        }
        
    }
}

void Forest::filter(int size){
    //I am thinking IDDFS will be called here
    
    for(auto &iter : _itemsMap){
        long index = iter.first;
        Node* node = iter.second;
        node->_copIndex = IDDFS(node, _copLimit);
    }

    std::vector<std::pair<long, long>> rank;

    for(auto &iter : _itemsMap){
        long index = iter.first;                        //save the itemID in index
        long copIndex = iter.second->_copIndex;         //save copIndex here

        if(rank.size()<size) rank.push_back(std::make_pair(copIndex, index)); //if vector is less than desired size, just push back
        else{
            sort(rank.rbegin(), rank.rend()); //sort to check if the node we are pushing is greater than min.

            if(copIndex > rank[0].first){   //if so, pop back and replace
                rank.pop_back());
                rank.push_back(std::make_pair(copIndex, index));
            }
        }
    }

    for(auto &iter : rank){
        _top500.push_back(iter.second); //push in the rank of the index. Now, _top500 will store the items with highest copIndex
    }
}

/*
Perform IDDFS starting from the <start> node with the given <limit> and count the number of distinct nodes that are linked to <start>
Set the count of distinct linked nodes within the Node class's <_copIndex>
Return count
Is it possible(easier) to implement using recursion? 
*/
int Forest::IDDFS(Node* start, int limit){
    int count = 0;
    if(limit == 1){
        count = start->_connected.size();
        //start->_copIndex = count;
        return count;
    }
    
    for(unsigned long i = 0; i<start->_connected.size(); i++){
            Node* n = start->_connected[i];
            count = count + IDDFS(n, limit-1);
        }
    return count;
}

