#include <iostream>
#include <vector>


using namespace std;


class Graph{
private: 
    vector<vector<unsigned int>> graph;


public:
    bool loadGraph(string graph_name){
    
        return true;
    }

};



int main(int argc, char *argv[]){

/*Here we will store the name of our graph data */
vector< string > data = {" myciel3.col", "queen5_5.col"};
Graph graph_main;

unsigned int n_graph;

    if(argc < 2){
        cout << "Select a graph from the list: " << endl;
        for (size_t i = 0; i < data.size(); i++)
        {
            cout << " [" << i << "] "<< data[i] << endl;
        }
        cout << "Enter a number: " ;
        cin >> n_graph;
    }
    else if(argc > 2 ){
        cout << "To many arguments." << endl;
        return 0;
    }
    else if(argc == 2){
        n_graph = atoi(argv[1]);
    }

    cout << n_graph << endl;

    /*Check if the graph number is valid*/
    if(n_graph >= data.size()){
        cout << "Not a valid graph"<< endl;
    }
    else{
        if(!graph_main.loadGraph(data[n_graph])){
            cout << "The graph did not load." << endl;
            return 0;            
        }
        else{
            cout << "Succesful load." << endl;
        }

    }
    



}