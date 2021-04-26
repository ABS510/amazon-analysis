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
    Node::_itemId = -1; //set _itemID as default
    Node::_copIndex = -1; //set _copIndex to be -1 as default
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
    std::ifstream myfile(file); //read from file to myfile
    int a, b;
    while(myfile >> a >> b){ //store first column to a, second to b with tab separated
        if(_itemsMap.find(a) == _itemsMap.end()){ //if we have not created a node yet
            Node* createNode = new Forest::Node(a); //create node
            _itemsMap[a] = createNode;  //allocate the address of node to the _itemsMap
        }
        if(_itemsMap.find(b) == _itemsMap.end()){ //if we have not created b node yet
            Node* createNode = new Forest::Node(b); //create node
            _itemsMap[b] = createNode; //allocate the address of b node to the _itemsMap
        }
        _itemsMap[a]->_connected.push_back(_itemsMap[b]); //push the address of b to _connected vector of _itemsmap[a]
    } 
}

void Forest::filter(size_t size){ //size is the number of rankings we want to get. i.e. size = 30, we get top 30 products of highest copIndex
    for(auto &iter : _itemsMap){ //iterate through _itemsMap
        long index = iter.first; //we know first element of itemsmap is the index(itemID)
        Node* node = iter.second;//second is the address of that index
        node->_copIndex = IDDFS(node, _copLimit); //set copIndex of the node by running Depth Limited Search
    }

    std::vector<std::pair<long, long>> rank; //make a map of rank to help us rank the products according to copIndex

    for(auto &iter : _itemsMap){ //Iterate through _itemsMap

        long index = iter.first;                        //save the itemID in index
        long copIndex = iter.second->_copIndex;         //save copIndex here
        if(rank.size()<size) {
            rank.push_back(std::make_pair(copIndex, index)); //if vector is less than desired size, just push back
            }
        else{
            sort(rank.rbegin(), rank.rend()); //sort to check if the node we are pushing is greater than min.
            
            if(copIndex > rank[size-1].first){   //if so, pop back and replace
                rank.pop_back();
                rank.push_back(std::make_pair(copIndex, index));
            }
            // std::cout<<"Current Rank:"; //just print to debug
            for(size_t i = 0; i<size; i++){
                // std::cout<<rank[i].second<<" "; //just print to debug
            }
            // std::cout<<std::endl; //just print to debug

            //std::cout<<"Current Rank:"; //just print to debugug

        }
    }
    sort(rank.rbegin(), rank.rend()); //sort from largest to smallest in rank

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
    unordered_map<Forest::Node*, bool> visited; //created map of visited to perfrom the recursive iteration
    return IDDFS_helper(start, start, limit, visited);
}

int Forest::IDDFS_helper(Node* start, Node* cur, int limit, unordered_map<Node*, bool>& bookkeep){
    /*
    Node* start     : starting address of the Depth limited search (DLS)
    Node* cur       : current address we are iterating
    int limit       : limit we will set in our depth limited search
    map<> bookkeep  : checks which nodes are visited and which are not to prevent crash
    */

    int count = 0; //count is number of nodes it is connected to.

    if(limit == 1){ //base case
        bookkeep[cur] = 1; 
        count = cur->_connected.size(); //set count to be the number of connected nodes
        for(unsigned long i = 0; i<cur->_connected.size(); i++){ //delete all the duplicating nodes
            if(bookkeep[cur->_connected[i]]) count--;
            bookkeep[cur->_connected[i]] = 1;
        }
        return count;
    }
    
    if(limit == 0) return 0; //if limit = 0 simply return 0

    bookkeep[cur] = 1; //set the node as visited
    count += cur->_connected.size();          //for every node we visit, we need to add its branching factor
    for(unsigned long i = 0; i<cur->_connected.size(); i++){
        if(bookkeep[cur->_connected[i]]) count--; //if we have visited the node, we decrement the count
        // bookkeep[cur->_connected[i]] = 1; 
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