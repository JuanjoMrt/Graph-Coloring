#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <vector>
#include <stdlib.h>
#include <time.h> 
#include <iostream>

#define END "\e[0m"
#define BLUE "\e[44m"
#define RED "\e[45m"
#define GREEN "\e[42m"
#define BLACK_FOREGRND "\e[30m"
    

using namespace std;

class Individual{
    private:
        vector<unsigned int> chromosome;
        unsigned int n_genes;
        unsigned int N_colours_used = 0;
        unsigned int fitness = 0;

    public:

        /*  Initialize a certain individual with random values, 
            and n_genes number of genes
        */
        Individual(unsigned int n_genes);

        /*  Create an individual based on parent_a and parent_b
        */
        Individual(Individual, Individual);

        /*  Numer of differents colours used in this result
        */
        unsigned int getNumOfColours();

        /*  Print the Chromosome and its colours 
        */
        void printChromosome();

        /*  It will return the value of the chromosome at the i position
        */
        unsigned int at(unsigned int i);

        /*  Assign a value to the fitness
        */
        void setFitness(unsigned int fitness);

        /*  Return the fitness of the individual
        */
        unsigned int getFitness();




        


};

#endif