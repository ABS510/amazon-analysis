#include<iostream>
#include<vector>
#include<map>
#include<fstream>

using namespace std;

class Forest{
    public:
        struct Node{
            long _itemId;
            long _copIndex;
            vector<Node*> _connected;
            Node* makeNode(long itemId);
        }
        void readFromFile(string file);
        void filter500();
    
    private:
        map<long, Node*> _itemsMap;
        vector<long>
}