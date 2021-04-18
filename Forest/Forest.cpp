#include "Forest.h"

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>


Forest::Forest(){
    _copLimit = 0;
}

Forest::Forest(int copLimit){
    _copLimit = copLimit;
}


/*
Set the limit for co-purchasing, this is the limit used for IDDFS
*/

Forest::Node::Node(){
    Node::_itemId = -1;
    Node::_copIndex = -1;
}

Forest::Node::Node(long itemId){
    Node::_itemId = itemId;
    Node::_copIndex = 0;
}


/*
Function below takes in the .txt file and create the forest of all items by
mapping each itemId to their pointer in the forest
*/




void Forest::readFromFile(string file){
    std::ifstream myfile(file);
    int a, b;
    while(myfile >> a >> b){
        if(_itemsMap.find(a) == _itemsMap.end()){
            Node* createNode = new Forest::Node(a);
            _itemsMap[a] = createNode;
        }
        if(_itemsMap.find(b) == _itemsMap.end()){
            Node* createNode = new Forest::Node(b);
            _itemsMap[b] = createNode;
        }
        _itemsMap[a]->_connected.push_back(_itemsMap[b]);
    }
}

void Forest::filter(size_t size){
    for(auto &iter : _itemsMap){
        long index = iter.first;
        Node* node = iter.second;
        node->_copIndex = IDDFS(node, _copLimit);
    }

    std::vector<std::pair<long, long>> rank;

    for(auto &iter : _itemsMap){
        long index = iter.first;                        //save the itemID in index
        long copIndex = iter.second->_copIndex;         //save copIndex here

        if(rank.size()<size) 
            rank.push_back(std::make_pair(copIndex, index)); //if vector is less than desired size, just push back
        else{
            sort(rank.rbegin(), rank.rend()); //sort to check if the node we are pushing is greater than min.

            if(copIndex > rank[0].first){   //if so, pop back and replace
                rank.pop_back();
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
int Forest::IDDFS(Node* start, int limit, unordered_map<Node*, bool> & bookkeep){
    int count = 0;
    if(limit == 1){
        bookkeep[start] = 1;
        count = start->_connected.size();
        for(unsigned long i = 0; i<start->_connected.size(); i++){
            if(bookkeep[start->_connected[i]]){
                count--;
            }
            bookkeep[start->_connected[i]] = 1;
        }
        return count;
    }
    if(limit == 0){
        return 0;
    }
    bookkeep[start] = 1;
    count += start->_connected.size();          //for every node we visit, we need to add its branching factor
    for(unsigned long i = 0; i<start->_connected.size(); i++){
        if(bookkeep[start->_connected[i]]){
            count--;
        }
        bookkeep[start->_connected[i]] = 1;
        count = count + IDDFS(start->_connected[i], limit-1, bookkeep);   //perform IDDFS on each immediately neighboring node
    }
    return count;
}


// int Forest::IDDFS(Node* start, int limit, unordered_map<Node*, bool> &bookkeep){
//     int count = 0;
//     if(limit == 1){
//         count = start->_connected.size();
//         for(unsigned long i = 0; i<start->_connected.size(); i++){
//             if(bookkeep[start->_connected[i]]){
//                 count--;
//             }
//         }
//         return count;
//     }
//     // if(limit == 0) return 0;

//     bookkeep[start] = true;
    
//     std::cout<<start->_itemId<<std::endl;
//     for(size_t i = 0; i<start->_connected.size(); i++){
//         if(bookkeep[start->_connected[i]] == true) continue;
//         count = count + IDDFS(start->_connected[i], limit-1, bookkeep);
//         std::cout<<count<<std::endl;
//     }
//     return count;
// }



int Forest::get_copLimit(){
    return _copLimit;
};

void Forest::set_itemsMap(long idx, Forest::Node* node){
    _itemsMap[idx] = node;
}

unordered_map<long, Forest::Node*> Forest::get_itemsMap(){
    return _itemsMap;
}
