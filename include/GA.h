#include <vector>
#include <stdlib.h>
#include <time.h> 
#include <queue>

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
            Percentage of Indiviuals that will return:
                From 0% to 100%
            return: Bests p% Individuals
        */
        vector<Individual> FindBestIndividuals( unsigned int p);

        /*  It will use a previous Individual and mutate it to create
            a new one.
            index: The index of the previous one in population
            return: The new Individual
        */
        Individual Mutation(unsigned int index);

        /*  Will create a new Individual based on his parents
            idx_X: Index of both parents
            p: Percentage used from the parent_1 
                (1-p will be the percentage used from parent_2)
            return: The new individual
        */
        Individual Create(unsigned int idx_parent_1, unsigned int idx_parent_2);

        /*  With "FindBestIndividuals" will find the best individuals of the current population
            and create a new population
                1. A percentage will be mutations.
                2. A percentage will be created with 2 parents.
                3. A percentage will remain from the previous population.
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
            
            Return: Fitness of a specific infividual
        */
        unsigned int fitnessOfIndividual(unsigned int index);


        /*  Print the population and the values of the Individuals
        */
        void printPopulation();

        void mutateAll(){
            for (unsigned int i = 0; i < n_individuals; i++){
                population[i].mutate();
            }
        }

    






};