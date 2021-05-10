#include "Forest.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>

int main(){
    int limit;
    std::cout << "Enter limit for IDDFS (less than or equal to 4): " << std::endl;
    std::cin >> limit;
    Forest forest = Forest(limit);
    std::cout<<"Forest initialized!"<<std::endl;

    std::cout<<"Enter input file: "<<std::endl;
    std::string file;
    std::cin >> file; 
    forest.readFromFile(file);
    std::cout<<"File read!"<<std::endl;
    
    int top;
    std::cout<<"Enter ranking N: "<<std::endl;
    std::cin >> top;
    forest.filter(top);
    std::cout<<"Filter applied!"<<std::endl;
    
    //std::cout<<"Generating top product..."<<std::endl;
    std::vector<long> top_product = forest.get_topProduct();
    //std::cout<<"Top product generated at index:"<<std::endl;
    
    int cnt = 0;
    /*for(auto itr : top_product){
        std::cout<<"Product Rank "<<++cnt<<") " << itr<<"\twith COP Index : "<<forest.get_itemsMap()[itr]->_copIndex<<std::endl;
    }*/

    //std::cout<<"Saving the Ranking ... "<<std::endl;
    std::ofstream outfile("results/result_midpoint.txt");
    cnt = 0;
    for(auto itr : top_product){
        outfile<<"Product Rank "<<++cnt<<") " << itr<<"\twith COP Index : "<<forest.get_itemsMap()[itr]->_copIndex<<"\n";
    }
    //std::cout<<"Ranking Saved!" << "\n";

    std::cout<<"Do you want to execute Tarjan's algorithm? (yes or no)"<<std::endl;
    std::string tarjan;
    std::cin>> tarjan;
    if(tarjan == "yes") {
        int scc_number = 0;
        vector<vector<long>> stronglyConnected = forest.SCC();
        /*for (unsigned i = 0; i < stronglyConnected.size(); i++) {
            if(stronglyConnected[i].size() <= 1){
                continue;
            }
            cout << "Strongly connected component " << ++scc_number << ": ";
            for (unsigned j = 0; j < stronglyConnected[i].size(); j++) {
                cout << stronglyConnected[i][j] << " ";
            }
            cout << "\n";
        }*/
        scc_number = 0;
        for (unsigned i = 0; i < stronglyConnected.size(); i++) {
            if(stronglyConnected[i].size() <= 1){
                continue;
            }
            outfile << "Strongly connected components " << ++scc_number << ": ";
            for (unsigned j = 0; j < stronglyConnected[i].size(); j++) {
                outfile << stronglyConnected[i][j] << " ";
            }
            outfile << "\n";
        }
    }

    std::cout<<"Do you want to execute BFS? (yes or no)"<<std::endl;
    std::string bfs;
    std::cin>> bfs;
    if(bfs == "yes") {
        unsigned long _totalnumfiltered = forest.BFS();
        //cout << "After filtering from " << forest.get_itemsMap().size() << " items, " << "total number of products now is: " << _totalnumfiltered << endl;
        outfile << "After filtering from " << forest.get_itemsMap().size() << " items, " << "total number of products now is: " << _totalnumfiltered << endl;
    }
    outfile << "\n";
    outfile << "Your inputs were: limit: " << limit << " and ranking : " << top << " with file path " << file << "\n"; 
}