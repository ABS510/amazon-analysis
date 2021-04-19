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

        std::cout<<"Index : "<<index<<" COPIndex : "<<copIndex<<std::endl;


        if(rank.size()<size) {
            rank.push_back(std::make_pair(copIndex, index)); //if vector is less than desired size, just push back
            }
        else{
            sort(rank.rbegin(), rank.rend()); //sort to check if the node we are pushing is greater than min.
            
            if(copIndex > rank[size-1].first){   //if so, pop back and replace
                rank.pop_back();
                rank.push_back(std::make_pair(copIndex, index));
            }

            for(size_t i = 0; i<size; i++){
                std::cout<<rank[i].second;
            }
            std::cout<<std::endl;
        }
    }
    sort(rank.rbegin(), rank.rend()); 

    for(auto &iter : rank){
        _topProduct.push_back(iter.second); //push in the rank of the index. Now, _top500 will store the items with highest copIndex
    }
}

/*
Perform IDDFS starting from the <start> node with the given <limit> and count the number of distinct nodes that are linked to <start>
Set the count of distinct linked nodes within the Node class's <_copIndex>
Return count
Is it possible(easier) to implement using recursion? 
*/
int Forest::IDDFS(Node* start, int limit){
    unordered_map<Forest::Node*, bool> visited;
    return IDDFS_helper(start, start, limit, visited);
}

int Forest::IDDFS_helper(Node* start, Node* cur, int limit, unordered_map<Node*, bool>& bookkeep){
    int count = 0;

    if(limit == 1){
        bookkeep[cur] = 1;
        count = cur->_connected.size();
        for(unsigned long i = 0; i<cur->_connected.size(); i++){
            if(bookkeep[cur->_connected[i]]) count--;
            bookkeep[cur->_connected[i]] = 1;
        }
        return count;
    }
    
    if(limit == 0) return 0;

    bookkeep[cur] = 1;
    count += cur->_connected.size();          //for every node we visit, we need to add its branching factor
    for(unsigned long i = 0; i<cur->_connected.size(); i++){
        if(bookkeep[cur->_connected[i]]) count--;
        bookkeep[cur->_connected[i]] = 1;
        count = count + IDDFS_helper(start, cur->_connected[i], limit-1, bookkeep);   //perform IDDFS on each immediately neighboring node
    }
    return count;
}


int Forest::get_copLimit(){
    return _copLimit;
};

void Forest::set_itemsMap(long idx, Forest::Node* node){
    _itemsMap[idx] = node;
}

unordered_map<long, Forest::Node*> Forest::get_itemsMap(){
    return _itemsMap;
}

std::vector<long> Forest::get_topProduct(){
    return _topProduct;
}