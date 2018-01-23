#include<iostream>
#include<vector>
#include<cmath>

#include "individual.h"

using namespace std;

class SA{
    private:
        Individual best_solution;
        Individual current_solution;
        double  temperature,
                temperature0,
                alpha = 0.02;
        unsigned int    n_nodes, 
                        n_edges;
        int coolMode;
        vector<vector<unsigned int>> main_graph;

    public:

        SA(double initial_temperature,unsigned int n_nodes,unsigned int n_edges ,vector<vector<unsigned int>> main_graph);

        //
        SA(double initial_temperature,int coolMode, int alpha,unsigned int n_nodes,unsigned int n_edges ,vector<vector<unsigned int>> main_graph);

        /*  Returns the best solution found so far
        */
        Individual GetBestState();

        /*
        */
        int findFirstCollision();

        /*  It will find in the neighborhood a suitable neighbor
            according to its fitness and to the current temperature

            Neighborhood = Solutions where there is a different colour assigned
                            to a certain node in the graph that has a collision
            
            Collision = Two nodes with the same colour and with a common edge
        */
        void NextNeighbor();

        /*  Reduce the temperature according to a function
        */
        void cool(int k);

        /*  Main loop where the algorithm is used,
            It will reduce the temperature and find
            new neighbors in every iteration
                max_iterations: maximum number of iteration before the program stops
                min_temp: if the minimum temperature is reach the program will stops
                total_iteration: the real total iteration that the program made
                min_colors: minimum amount of colors needed to solve the problem (if unknown "min_colors = 0" )
        */
        void MainLoop(unsigned int max_iterations, double min_temp, unsigned int &total_iterations, unsigned int min_colors);


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