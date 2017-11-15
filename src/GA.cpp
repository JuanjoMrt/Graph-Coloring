#include "GA.h"

    GA::GA(unsigned int n_individuals, unsigned int n_genes, unsigned int n_edges, vector<vector<unsigned int>> main_graph){
        this->n_individuals = n_individuals;
        this->n_genes = n_genes;
        this->n_edges = n_edges;
        this->main_graph = main_graph;

        for(unsigned int i = 0; i < n_individuals; i++){

            Individual a(n_genes);
            population.push_back(a);
        }

    };

    vector<Individual> GA::FindBestIndividuals( unsigned int p){
        
        vector<Individual> best_individuals;

        //pair< Fitness value, index in the population>
        priority_queue< pair<unsigned int, int>> best_ind;

        /*  To have the best n_best_individuals, we insert the elements
            into a queue and then pop just what we need.
            (It can be done more efficient, if we don't push the individuals
            smaller than the last element of the queue but back() is not working
            for some reason, I will improve this if I have time)
        */

        for (unsigned int i = 0; i < n_individuals; ++i) {
    
            best_ind.push(std::pair<unsigned int, int>(fitnessOfIndividual(i), i));
        }
        double percentage = (double)p/100;
    

        //Number of individuals that we will choose
        int n_best_individuals = percentage*n_individuals;


        /*  Here we pop the elements that we want
        */
        for (int i = 0; i < n_best_individuals; ++i) {
            int ki = best_ind.top().second;

            best_individuals.push_back(this->population[ki]);
            
            best_ind.pop();
        }

        population = best_individuals;
        n_individuals = best_individuals.size();
        return best_individuals;
    }


    unsigned int GA::fitnessOfIndividual(unsigned int index){
        
        unsigned int fit = 0;
        //If we calculate it previously we dont need to do it again
        if(population[index].getFitness() != 0){
            fit = population[index].getFitness();
        }
        else{
            
            for(unsigned int i = 0; i < n_genes; i++){
                for(unsigned int j = 0; j < main_graph[i].size(); j++){
                    unsigned int cmp_number = population[index].at( main_graph[i][j] );
                    if(population[index].at(i) != cmp_number){
                        fit++;
                    }
                }
                
            }
            
                fit += (n_genes - population[index].getNumOfColours());
            



            population[index].setFitness(fit);
        }
    return fit;
    };

    void GA::printPopulation(){
        for(unsigned int i = 0; i < n_individuals; i++){
            cout << endl;
            population[i].printChromosome();
            cout << "Fitness: " << fitnessOfIndividual(i) ;
        }


    };