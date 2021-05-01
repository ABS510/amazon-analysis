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

vector<Forest::Node*> Forest::adjVertices(int idx) {
    if (unsigned(idx) >= _topProduct.size()) {
        return vector<Forest::Node*>();
    }
    vector<Node*> adjVertices;
    long productId = _topProduct[idx];
    Node* product = _itemsMap[productId];
    
    for (Node* adj : product->_connected) {
        if (std::find(_topProduct.begin(), _topProduct.end(), adj->_itemId) != _topProduct.end()) {
            adjVertices.push_back(adj);
        }
    }
    return adjVertices;
}

void Forest::SCCUtil(int u, int disc[], int low[], stack<int> *st,
                    bool stackMember[])
{
    // A static variable is used for simplicity, we can avoid use
    // of static variable by passing a pointer.
    static int time = 0;
  
    // Initialize discovery time and low value
    disc[u] = low[u] = ++time;
    st->push(u);
    stackMember[u] = true;
  
    // Go through all vertices adjacent to this
    vector<Node*>::iterator i;

    vector<Node*> edges = adjVertices(u);

    for (i = edges.begin(); i != edges.end(); ++i)
    {
        int v = getIndex(*i);  // v is current adjacent of 'u'
        // If v is not visited yet, then recur for it
        if (disc[v] == -1)
        {
            SCCUtil(v, disc, low, st, stackMember);
  
            // Check if the subtree rooted with 'v' has a
            // connection to one of the ancestors of 'u'
            // Case 1 (per above discussion on Disc and Low value)
            low[u]  = min(low[u], low[v]);
        }
  
        // Update low value of 'u' only of 'v' is still in stack
        // (i.e. it's a back edge, not cross edge).
        // Case 2 (per above discussion on Disc and Low value)
        else if (stackMember[v] == true)
            low[u]  = min(low[u], disc[v]);
    }
  
    // head node found, pop the stack and print an SCC
    int w = 0;  // To store stack extracted vertices
    if (low[u] == disc[u])
    {
        while (st->top() != u)
        {
            w = (int) st->top();
            cout << _topProduct[w] << " ";
            stackMember[w] = false;
            st->pop();
        }
        w = (int) st->top();
        cout << _topProduct[w] << "\n";
        stackMember[w] = false;
        st->pop();
    }
}
  
// The function to do DFS traversal. It uses SCCUtil()
void Forest::SCC()
{
    int *disc = new int[_topProduct.size()];
    int *low = new int[_topProduct.size()];
    bool *stackMember = new bool[_topProduct.size()];
    stack<int> *st = new stack<int>();
  
    // Initialize disc and low, and stackMember arrays
    for (int i = 0; unsigned(i) < _topProduct.size(); i++)
    {
        disc[i] = -1;
        low[i] = -1;
        stackMember[i] = false;
    }
  
    // Call the recursive helper function to find strongly
    // connected components in DFS tree with vertex 'i'
    for (int i = 0; unsigned(i) < _topProduct.size(); i++)
        if (disc[i] == -1)
            SCCUtil(i, disc, low, st, stackMember);
}

int Forest::getIndex(Node* v) {
    for (int i = 0; unsigned(i) < _topProduct.size(); i++) {
        if (v->_itemId == _topProduct[i]) {
            return i;
        }
    }
    return -1;
}