#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <vector>
#include <stdlib.h>
#include <time.h> 
#include <iostream>
#include <random>
#include <algorithm>

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

        /*  Create an individual with a given chromosome and the number of colours used
        */
        Individual(vector<unsigned int> chromosome, unsigned int N_colours_used);

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

        /*  It will mutate the individual
        */ 
        void mutate();

    
    

        double getRandom(double start, double finish){
            random_device rd;
            mt19937 mt(rd());
            uniform_real_distribution<double> dist(start, finish);
        return dist(mt);
        }


        


};

#endif