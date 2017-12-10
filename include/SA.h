#include<iostream>
#include<vector>
#include "individual.h"

using namespace std;

class SA{
    private:
        Individual best_solution;
        Individual current_solution;
        double temperature, min_temp;
        unsigned int n_nodes;
        vector<vector<unsigned int>> main_graph;

    public:
        SA(double initial_temperature,int min_temperature,unsigned int n_nodes ,vector<vector<unsigned int>> main_graph);

        Individual GetBestState();

        void MainLoop(unsigned int n_iterations);



};