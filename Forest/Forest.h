#include<iostream>
#include<vector>
#include<unordered_map>
#include<fstream>

using namespace std;

class Forest{
    public:
        struct Node{
            long _itemId;
            long _copIndex;
            vector<Node*> _connected;
            Node(long itemId);
            Node();
        }
        void readFromFile(string file);
        void setCopLimit(int limit);
        void filter(int size);
        int IDDFS(Node* start, int limit);
    
    private:
        std::unordered_map<long, Node*> _itemsMap;
        std::vector<long> _top500;   //this is to store the itemId of the 500 most optimum products to be cut down to
        int _copLimit;          //this should by default be 0, this is the limit we set for IDDFS
}