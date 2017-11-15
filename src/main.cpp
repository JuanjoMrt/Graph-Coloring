#include <iostream>
#include <fstream>
#include <vector>
#include "GA.h"
#include "individual.h"
#include <random>



using namespace std;

#define END "\e[0m"
#define BLUE "\e[44m"
#define RED "\e[45m"
#define GREEN "\e[42m"



class Graph{
private: 
    vector<vector<unsigned int>> graph;
    unsigned int n_nodes, n_edges;

public:
    bool loadGraph(string graph_name){ //graph_name: Name of the graph
        string file_path = "data/";
        file_path += graph_name + ".txt"; //Store the path of the plaintext
        
        ifstream plain_graph (file_path);
        
        if(plain_graph.fail()) throw ("Cant open the file path");

        
        string input;
        plain_graph >> input;
        while(input != "edge")
            plain_graph >> input;
        
       
        plain_graph >> n_nodes >> n_edges;

        unsigned int node1,node2;
        char e;

        /*Now we know the number of nodes, so
        we resize the graph to allocate all*/
        graph.resize(n_nodes);


        /*Set the last node, we will use this variable to know 
        when we are loading the edges of a different node, 
        in order to insert it in the vector
        */
       // unsigned int last_node = 0; 

        while(!plain_graph.eof()){

            /*Loading the values into variables*/
            plain_graph >> e >> node1 >> node2;
            graph[node1 - 1].push_back(node2 - 1);
            //graph[node2].push_back(node1);

        }
        plain_graph.close();
        return true;
    }

    void printGrahp(){
        if(!(graph.size() > 0)){
            cout << "The graph is not loaded.";
        }
        else{
            for (size_t i = 0; i < graph.size(); i++)
            { 
                cout << endl << BLUE << "[" << i << "]" << END << "->";
                for (size_t j = 0; j < graph[i].size(); j++)
                {
                    cout << " " << graph[i][j] ;
                }
            }
            cout << endl;
        }
    }


    unsigned int getNodes(){
        return this->n_nodes;
    }
    unsigned int getEdges(){
        return this->n_edges;
    }

    vector<vector<unsigned int>> getGraph(){
        return this->graph;
    }



};


int main(int argc, char *argv[]){

/*Here we will store the name of our graph data */
vector< string > data = {"myciel3.col", "queen5_5.col", "hola"};
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

    /*Check if the graph number is valid*/
    if(n_graph >= data.size()){
        cout << "Not a valid graph"<< endl;
    }
    else{
        bool error = graph_main.loadGraph(data[n_graph]);
        if(!error){
            cout << "The graph did not load." << endl;
            return 0;            
        }
        else{
            cout << "Succesful load." << endl;
        }

    }
    graph_main.printGrahp();
    


   
    Individual in(graph_main.getNodes());
    
    //in.printChromosome();
    //in.mutate();
    //in.printChromosome();

    //cout << in.getRandom(0.0, )



    int n_individuals = 10;

    GA GA_Solution(n_individuals, graph_main.getNodes(), graph_main.getEdges(), graph_main.getGraph());

    GA_Solution.printPopulation();
    
    cout << endl << "Fitness: " << GA_Solution.fitnessOfIndividual(3) << endl;
    cout << graph_main.getEdges() << endl;

    vector<Individual> a = GA_Solution.FindBestIndividuals(30);

    GA_Solution.printPopulation();

    cout << endl << "Mutation" << endl ;
    GA_Solution.mutateAll();
    GA_Solution.printPopulation();



    



}