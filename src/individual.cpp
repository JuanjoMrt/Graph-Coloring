#include "individual.h"


    Individual :: Individual(unsigned int n_genes){
        this->n_genes = n_genes;
        chromosome.resize(n_genes);


        
        int random;
        unsigned int colour = 0;
        
        for(unsigned int i = 0; i < n_genes; i++){
            random = rand() % n_genes;

            if(random == 0 || i == 0)
                chromosome[i] = colour;
            else{
                colour++;
                chromosome[i] = colour;
            } 
        }
        
        this->N_colours_used = colour;
    }

    unsigned int Individual::getNumOfColours(){
        return this->N_colours_used;
    }

    void Individual::printChromosome(){
        for(unsigned int i = 0; i < chromosome.size(); i++){
            cout << GREEN << BLACK_FOREGRND << " " << this->chromosome[i]  << END ;
        }
        cout << " N of colour used: " <<this->N_colours_used <<endl;            
    };

    unsigned int Individual::at(unsigned int i){
        return this->chromosome[i];
    }

    void Individual::setFitness(unsigned int fitness){
        this->fitness = fitness;
    }

    unsigned int Individual::getFitness(){
        return this->fitness;
    }


