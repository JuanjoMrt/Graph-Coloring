#include "individual.h"


    Individual :: Individual(unsigned int n_genes){
        this->n_genes = n_genes;
        chromosome.resize(n_genes);


        
        int random;
        unsigned int colour = 0;
        
        for(unsigned int i = 0; i < n_genes; i++){

            
            random = this->getRandom(0.0 , n_genes);

            if(random == 0 || i == 0)
                chromosome[i] = colour;
            else{
                colour++;
                chromosome[i] = colour;
            } 
        }
        
        this->N_colours_used = colour + 1;
    }

    Individual::Individual(vector<unsigned int> chromosome, unsigned int N_colours_used){
        this->chromosome = chromosome;
        this->n_genes = chromosome.size();
        this->N_colours_used = N_colours_used;
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

    void Individual::mutate(){

        double colours = N_colours_used;
        //cout << "colours: "<< colours/2 << endl;
        unsigned int random_a = this->getRandom(1.0 , colours/2);
        unsigned int random_b;
        //cout << "random_a: "<< random_a << endl;

        for(unsigned int i = 0; i < random_a; i++){
            random_b = this->getRandom(0.0 , N_colours_used - random_a);
            replace (chromosome.begin(), chromosome.end(), N_colours_used - 1, random_b);
            this->N_colours_used--;
        }

    }


