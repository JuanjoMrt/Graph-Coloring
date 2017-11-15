#include <vector>
#include <stdlib.h>
#include <time.h> 

#include "individual.h"
using namespace std;

class GA{
    private:
        vector<Individual> population; 
        unsigned int n_individuals;
        unsigned int n_genes;
        unsigned int n_edges;
        vector<vector<unsigned int>> main_graph;
        



    public: 

        /*  It will inicializate the population with a n_individuals number of individuals
            All individuals will be intilized with random values
            n_genes is the number of nodes in the graph
        */
        GA(unsigned int n_individuals, unsigned int n_genes, unsigned int n_edges, vector<vector<unsigned int>> main_graph);

        /*  It will find the bests Individuals of the current population
            return: Bests Individuals
        */
        vector<Individual> FindBestIndividuals();

        /*  With "FindBestIndividuals" will find the best individuals of the current population
            and create a new population
            A percentaje of 
        */
        void CreateNewPopulation(int randomness);

        /*  Method that will return a bool if there was a problem running the Genetic Algorithm
            It will write in best_individual, the best result it could find
        */
        bool CalculateGA(Individual &best_individual);

        /*  It will return an int with the value of the fitness of the Individual
            This value is calcuflated:
                1. Every time a edge is good (both nodes have different colours)
                    it will add 1 to the variable, if the node is not correct wilk add 0.

                2. If all the edges are correct (fitnes = N_edges) it will add  
                    N-N_colours_used to the value.
        */
        unsigned int fitnessOfIndividual(unsigned int index);


        /*  Print the population and the values of the Individuals
        */
        void printPopulation();






};