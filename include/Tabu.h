#include<iostream>
#include<vector>
#include<list>
#include <unistd.h>


#include "individual.h"

using namespace std;

class Tabu {
    private:

        Individual  best_solution,
                    initial_solution,
                    current_solution;

        vector<Individual> critical_solutions;

        // pair<position, color>
        vector< pair<int,int> > tabu_list;
        unsigned int tabu_size;
        unsigned int neighborhood_size;

        unsigned int    n_nodes, 
                        n_edges;
        vector<vector<unsigned int>> main_graph;




    public:

        Tabu(unsigned int neighborhood_size, unsigned int n_nodes, unsigned int n_edges, vector<vector<unsigned int>> main_graph);

        /*
        */
        int findFirstCollision();

        /*  Checks if the move is not in the tabu list
            p is the position
            c is the color
        */
        bool checkTabuList(int p, int c);

        /*
        */
        void NextNeighbor();

        /*
        */
        void MainLoop(unsigned int n_iterations);

        /*  It will return an int with the value of the fitness of the Individual
            This value is calcuflated:
                1. Every time a edge is good (both nodes have different colours)
                    it will add 1 to the variable, if the node is not correct wilk add 0.

                2. If all the edges are correct (fitnes = N_edges) it will add  
                    N-N_colours_used to the value.
            
            Return: Fitness of a specific infividual
        */ 
        unsigned int CalculateFitness(Individual &ind);

        double getRandom(double start, double finish){
            random_device rd;
            mt19937 mt(rd());
            uniform_real_distribution<double> dist(start, finish);
        return dist(mt);
        }

        


};