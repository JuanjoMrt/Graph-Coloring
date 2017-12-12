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
                alpha;
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
        */
        void MainLoop(unsigned int n_iterations, double min_temp);

        unsigned int CalculateFitness(Individual &ind);


        double getRandom(double start, double finish){
            random_device rd;
            mt19937 mt(rd());
            uniform_real_distribution<double> dist(start, finish);
        return dist(mt);
        }


};