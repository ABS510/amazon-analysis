#include "Forest.h"
#include <iostream>
#include <fstream>
#include <vector>

int main(){
    int limit;
    limit = 3;
    Forest forest = Forest(limit);

    std::cout<<"Class Created!"<<std::endl;

    std::cout<<"Reading from file..."<<std::endl;
    forest.readFromFile("../Amazon0601.txt");
    std::cout<<"File read!"<<std::endl;

    std::cout<<"Appling filter..."<<std::endl;
    forest.filter(300);
    std::cout<<"Filter applied!"<<std::endl;
    
    std::cout<<"Generating top product..."<<std::endl;
    std::vector<long> top_product = forest.get_topProduct();
    std::cout<<"Top product generated at index:"<<std::endl;
    
    int cnt = 0;
    for(auto itr : top_product){
        std::cout<<"Product Rank "<<++cnt<<") " << itr<<"\twith COP Index : "<<forest.get_itemsMap()[itr]->_copIndex<<std::endl;
    }

    std::cout<<"Saving the Ranking ... "<<std::endl;
    std::ofstream outfile("results/result_midpoint.txt");
    cnt = 0;
    for(auto itr : top_product){
        outfile<<"Product Rank "<<++cnt<<") " << itr<<"\twith COP Index : "<<forest.get_itemsMap()[itr]->_copIndex<<"\n";
    }
    std::cout<<"Ranking Saved!" << "\n";

    vector<vector<long>> stronglyConnected = forest.SCC();
    for (unsigned i = 0; i < stronglyConnected.size(); i++) {
        for (unsigned j = 0; j < stronglyConnected[i].size(); j++) {
            cout << stronglyConnected[i][j] << " ";
        }
        cout << "\n";
    }
}