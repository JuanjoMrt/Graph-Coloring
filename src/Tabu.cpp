#include "Tabu.h"


Tabu::Tabu(unsigned int neighborhood_size, unsigned int n_nodes, unsigned int n_edges, vector<vector<unsigned int>> main_graph){
    this->neighborhood_size = neighborhood_size;
    this->n_nodes = n_nodes;
    this->n_edges = n_edges;
    this->main_graph = main_graph;
    this->tabu_size = n_edges/4;
    
    Individual new_individual(n_nodes);
    this->best_solution = this->current_solution = new_individual;

}



int Tabu::findFirstCollision(){
    int pos,pos_collision;
    bool collision = false;

    // If we already know that there aren't any collisions
    if(current_solution.getFitness() < n_edges){

        for (unsigned int i = 0; i < n_nodes && !collision; i++){
            for(unsigned int j = 0; j < main_graph[i].size() && !collision; j++){
                pos = main_graph[i][j]; 

                if(current_solution.at(i) == current_solution.at(pos)){
                    pos_collision = i;
                    collision = true;
                }
            }
        }
    }

    if(!collision){
        pos_collision = getRandom(0, n_nodes);
    }

    return pos_collision;
};

bool Tabu::checkTabuList(int p, int c){
    bool in_tabu_list = false;

    for(unsigned int i = 0; i < tabu_list.size() && !in_tabu_list ;i++){
        
        if(tabu_list[i].first == p && tabu_list[i].second == c)
            in_tabu_list = true;
    }

    return in_tabu_list;
};



void Tabu::NextNeighbor(){

    
    //Find a node to create a neighborhood
    int node = this->findFirstCollision();
    set<int> neighborhood;
    set<int>::iterator it;
    pair<int,int> best_move;
    Individual best_neighbor;
    Individual local_current = best_neighbor = this->current_solution;
    best_neighbor.setFitness(0);

    /*  If we cannot find a feasible neighborhood,
        it will start the proccess from another position
    */
    unsigned int failed_neighborhood = 0; 
    int index = 0;

    //for(unsigned int i = 0; i < neighborhood_size; i++){
    while(neighborhood.size() != neighborhood_size){
        
        /*  This way if it got stuck it will search
            in other areas that were not visited
        */
        if(failed_neighborhood == neighborhood_size*2){
            node = getRandom(0, n_nodes);
            if(critical_solutions.size() > 0){
                local_current = critical_solutions.at(critical_solutions.size()-1);
                critical_solutions.pop_back();
            }
            /*else{
                this->best_solution.printChromosome();
                cout << "FIT: " << this->best_solution.getFitness() << endl;
                sleep(2);
                exit(0);             
            }*/
                
            failed_neighborhood = 0;
        }




        //Pick a color different from the one in the node
        unsigned int color = this->getRandom(0,n_nodes);

        
        if(current_solution.at(node) == color)
            color = (color + 1) % n_nodes;

        bool found = false; 

        //Check if that color is already in the neighborhood
        if(neighborhood.size() > 0){
            it = neighborhood.find(color);
            if(it != neighborhood.end())
                found = true; 
        }
        

        //Check if the move is in the tabu list
        if(!found && !this->checkTabuList(node, color)){
            neighborhood.insert(color);

            local_current.setFitness(0);
            local_current.insertColor(node,color);
            this->CalculateFitness(local_current);

            if( best_neighbor.getFitness() < local_current.getFitness()){
                best_neighbor = local_current;
            }
        }
        else{
            failed_neighborhood++;
        }
       //cout << "Failed: " << failed_neighborhood << " i: " << index << endl;
        index++;
    }

    best_move.first = node;
    best_move.second = best_neighbor.at(node);

    //cout << "p: " <<  best_move.first << "  c: " << best_move.second << endl;
    

    if(tabu_list.size() >= tabu_size){
        tabu_list.erase(tabu_list.begin());
    }
    
    tabu_list.push_back(best_move);
    this->current_solution = best_neighbor;
    

};

void Tabu::MainLoop(unsigned int max_iterations, unsigned int &total_iterations, unsigned int min_colors){

    
    // current_neighbor = find best neighbor
        //create neighborhood
        //find best neighbor
        //Insert move in tabu list

    //If best_neighbor < current_neighbor
    //best = current
    int min_solution_found = 0;
    bool found = false;
    for (total_iterations = 0; total_iterations < max_iterations && !found; total_iterations++){

        //cout << "IT: " << i << endl;
        //current_solution.printChromosome();

        this->CalculateFitness(current_solution);
        if(current_solution.getFitness() == min_colors){
            min_solution_found++;
            if(min_solution_found == 8)
                found = true;
        }

        this->NextNeighbor();

        //current_solution.printChromosome();
        //cout << "FIT: " << current_solution.getFitness()<<endl;

        if(best_solution.getFitness() < current_solution.getFitness()){
            best_solution = current_solution;
            critical_solutions.push_back(current_solution);
        }





    }

    cout << "\n\nBest Solution:" << endl;
    best_solution.printChromosome();
    cout << "FIT: " << best_solution.getFitness() << endl;


};

unsigned int Tabu::CalculateFitness(Individual& ind){
    
    unsigned int fit = 0;
    //If we calculate it previously we dont need to do it again
    if(ind.getFitness() != 0){
        fit = ind.getFitness();
    }
    else{
        
        for(unsigned int i = 0; i < n_nodes; i++){
            
            for(unsigned int j = 0; j < main_graph[i].size(); j++){
                unsigned int cmp_number = ind.at( main_graph[i][j] );
                
                if(ind.at(i) != cmp_number){
                    fit++;
               
                }
            }

        }
        if(fit == n_edges)
            fit += (n_nodes - ind.getNumOfColours());

        ind.setFitness(fit);
    }
return fit;
};