#include "SA.h"


SA::SA(double initial_temperature,unsigned int n_nodes, unsigned int n_edges ,vector<vector<unsigned int>> main_graph){
    this->temperature = this->temperature0 = initial_temperature;
    this->main_graph = main_graph;
    this->n_nodes = n_nodes;
    this->n_edges = n_edges;

    vector<unsigned int> chromosome;
    for(unsigned int i = 0; i < n_nodes; i++)
        chromosome.push_back(1);
    
    Individual new_individual(chromosome);
    this->best_solution = new_individual;
    this->current_solution = new_individual;
};
SA::SA(double initial_temperature,int coolMode, int alpha,unsigned int n_nodes,unsigned int n_edges ,vector<vector<unsigned int>> main_graph){
    this->temperature = initial_temperature;
    this->main_graph = main_graph;
    this->n_nodes = n_nodes;
    this->n_edges = n_edges;
    this->coolMode = coolMode;
    this->alpha = alpha;

    Individual new_individual(n_nodes);
    this->best_solution = new_individual;
    this->current_solution = new_individual;
};

Individual SA::GetBestState(){
    return this->best_solution;
};

int SA::findFirstCollision(){
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


void SA::NextNeighbor(){

    //Find a node with a collision
    int node = this->findFirstCollision();
    //cout << "Collision, pos: " << node << endl;

    //Try a version where neighbors are choosen randomly not 
    //with a node that has a collision 

    //It can be a solution without collisions and not be the best
    
    //Pick a color different from the one in the node
    unsigned int color = this->getRandom(0,n_nodes);
    
    //cout << "New Color :" << color << endl;
    if(current_solution.at(node) == color)
        color = (color + 1) % n_nodes;

    
    Individual temp_solution = current_solution;
    temp_solution.insertColor(node,color);
    temp_solution.setFitness(0);

    unsigned int temp_fit = this->CalculateFitness(temp_solution);
    unsigned int current_fit = this->CalculateFitness(current_solution);
    //cout << "c_fit: " << current_fit << ", temp_fit: " << temp_fit << endl;
    //If the neighbor is better, we move to the neighbor
    if(temp_fit > current_fit){
        current_solution = temp_solution;
    }
    else{

        /*Check this value*/
        double p = this->getRandom(0,1);
        int diff_fitness = current_fit - temp_fit;

        if(p < exp(-diff_fitness/temperature))
            current_solution = temp_solution;
    }
};

void SA::cool(int k){
    switch(coolMode){
        case 0:
            //Linear
            temperature = temperature - alpha;
        break;
        case 1:
            //Geometric
            temperature = temperature*alpha;
        default:
            //Boltzmann
            temperature = temperature0*(1/(log(k+2)));
        break;
    }
};

void SA::MainLoop(unsigned int max_iterations, double min_temp, unsigned int &total_iterations,unsigned int min_colors){
    int correct = 0;
    bool correct_color = false;
    for(unsigned int i = 0; i < max_iterations && !correct_color;i++){
        //cout << "\n\nIt number: " << i << endl;
        //current_solution.printChromosome();
        //cout << "FIT: " << current_solution.getFitness() << endl;
        this->NextNeighbor();
        this->cool(i);

        if(temperature < min_temp){
            break;
        }
        else{
            //cout << "Temp: " << temperature << endl;
        }
            
        
        if(current_solution.getFitness() > best_solution.getFitness())
            best_solution = current_solution;



        if(current_solution.getNumOfColours() == min_colors)
            correct++;
        if(correct == 10){
            correct_color = true;
            total_iterations = i;
        }
    }


};

unsigned int SA::CalculateFitness(Individual& ind){
    
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