#include "SA.h"


SA::SA(double initial_temperature,int min_temperature,unsigned int n_nodes ,vector<vector<unsigned int>> main_graph){
    this->temperature = initial_temperature;
    this->min_temp = min_temperature;
    this->main_graph = main_graph;
    this->n_nodes = n_nodes;
    Individual new_individual(n_nodes);
    this->best_solution = new_individual;
    this->current_solution = new_individual;
};


Individual SA::GetBestState(){
    return this->best_solution;
};

void SA::MainLoop(unsigned int n_iterations){
    for(unsigned int i = 0; i < n_iterations;i++){
        
        this->NextNeighbor();
        this->cool();

        if(temperature < min_temp)
            break;
        
        if(current_solution.getFitness() > best_solution.getFitness())
            best_solution = current_solution;
        

    }


};