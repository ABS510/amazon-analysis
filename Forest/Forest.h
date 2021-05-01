#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <string>
#include <stack>
#include <list>
using namespace std;

class Forest{
    public:
        struct Node{
            long _itemId; //Product ID (First column of txt file)
            long _copIndex; //Will store _copIndex here

            vector<Node*> _connected; //vector of connected nodes
            Node(long itemId); //constructor of Node struct
            Node();             //default constructor

        };

        Forest(); //Default constructor of Forest class
        Forest(int copLimit); //constructor of forest class that sets copLimit
        void readFromFile(string file); //function to read from txt file and generate all the nodes
        void filter(size_t size);   //function to filter top-N products
        int IDDFS(Node* start, int limit); //Performs Depth-Limited Search to find copindex
        int IDDFS_helper(Node* start, Node* cur, int limit, unordered_map<Node*, bool>& visited); //helper function of IDDFS
        
        int get_copLimit();         //returns _copIndex
        void set_itemsMap(long idx, Node* node); //helps create _itemsMap
        unordered_map<long, Node*> get_itemsMap(); // returns _itemsMap
        vector<long> get_topProduct(); //returns _topProduct

        vector<Node*> adjVertices(int idx);
        void SCCUtil(int u, int disc[], int low[], stack<int> *st, bool stackMember[], vector<vector<long>>& connectedComps);
        vector<vector<long>> SCC();
        int getIndex(Node* v);

    private:
        unordered_map<long, Node*> _itemsMap;
        vector<long> _topProduct;   //this is to store the itemId of the 500 most optimum products to be cut down to
        int _copLimit;          //this should by default be 0, this is the limit we set for IDDFS
        

};