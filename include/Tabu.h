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

        /*  It will find the first collision of a individual
            if there is no collision it will return a random node of the individual
        */
        int findFirstCollision();

        /*  Checks if the move is not in the tabu list
            p: position
            c: color
        */
        bool checkTabuList(int p, int c);

        /*  It will create a new neighborhood and choose the next neighbor based
            on his fitness and if it is not in the memory
        */
        void NextNeighbor();

        /*  Main Loop for Tabu search
                max_iterations: maximum number of iteration before the program stops
                total_iteration: the real total iteration that the program made
                min_colors: minimum amount of colors needed to solve the problem (if unknown "min_colors = 0" )
        */
        void MainLoop(unsigned int max_iterations, unsigned int &total_iterations, unsigned int min_colors);

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