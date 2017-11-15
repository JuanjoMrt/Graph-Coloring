#include "GA.h"

    GA::GA(unsigned int n_individuals, unsigned int n_genes, unsigned int n_edges, vector<vector<unsigned int>> main_graph){
        this->n_individuals = n_individuals;
        this->n_genes = n_genes;
        this->n_edges = n_edges;
        this->main_graph = main_graph;

        for(unsigned int i = 0; i < n_individuals; i++){

            srand (time(NULL) + i+1);
            Individual a(n_genes);
            population.push_back(a);
        }

    };

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
            if(fit == n_edges){
                fit += (n_genes - population[index].getNumOfColours());
            }



            population[index].setFitness(fit);
        }
    return fit;
    };

    void GA::printPopulation(){
        for(unsigned int i = 0; i < n_individuals; i++){
            cout << endl;
            population[i].printChromosome();
        }


    };