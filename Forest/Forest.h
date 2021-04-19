#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <string>

using namespace std;

class Forest{
    public:
        struct Node{
            long _itemId;
            long _copIndex;

            vector<Node*> _connected;
            Node(long itemId);
            Node();

            private:
        };

        Forest();
        Forest(int copLimit);
        void readFromFile(string file);
        void filter(size_t size);
        // int IDDFS(Node* start, int limit, unordered_map<Node*, bool> & bookkeep);
        int IDDFS(Node* start, int limit);
        int IDDFS_helper(Node* start, Node* cur, int limit, unordered_map<Node*, bool>& visited);
        
        int get_copLimit();
        void set_itemsMap(long idx, Node* node);
        unordered_map<long, Node*> get_itemsMap();

    private:
        unordered_map<long, Node*> _itemsMap;
        vector<long> _top500;   //this is to store the itemId of the 500 most optimum products to be cut down to
        int _copLimit;          //this should by default be 0, this is the limit we set for IDDFS
        

};