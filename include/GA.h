#include <vector>
#include <stdlib.h>
#include <time.h> 
#include <queue>

#include "individual.h"
using namespace std;

class GA{
    private:
        //current population
        vector<Individual> population; 
        
        //Number of individuals in the population
        unsigned int n_individuals;
        //Number of genes in the graph
        unsigned int n_genes;
        //Number of edges in the graph
        unsigned int n_edges;
        //The graph being used
        vector<vector<unsigned int>> main_graph;
        



    public: 

        /*  It will initialize the population with a n_individuals number of individuals
            All individuals will be intilized with random values
            n_genes is the number of nodes in the graph
        */
        GA(unsigned int n_individuals, unsigned int n_genes, unsigned int n_edges, vector<vector<unsigned int>> main_graph);

        /*  Initialize a GA without a population
        */
        GA(unsigned int n_genes, unsigned int n_edges, vector<vector<unsigned int>> main_graph);

        /*  Add a new individual to the population
            ind_new: New individual
        */
        void addIndividual(Individual ind_new);

        /*  It will find the bests Individuals of the current population
            Percentage of Indiviuals that will return:
                From 0 to 1
            return: Bests p% Individuals
        */
        vector<Individual> FindBestIndividuals( double percentage);

        /*  Will generate a new population based on a previous one, using the reproduce method
            and the number of individuals that we want
            population: previous population
            new_ind: numbwe of individuals in the new population

            return: the new population
        */
        vector<Individual> Reproduce(vector<Individual> population, unsigned int new_ind);

        /*  Will generate a new population based on a previous one, using the mutate method
            and the number of individuals that we want
            population: previous population
            new_ind: numbwe of individuals in the new population

            return: the new population
        */
        vector<Individual> Mutate(vector<Individual> population, unsigned int new_ind);

        /*  It will create a new population
                p_best: A percentage will remain from the previous population. (Best Individuals)
                p_reproduce: A percentage will be created with 2 parents.
                p_mutatuions: A percentage will be mutations. 
        */
        void CreateNewPopulation(double p_best, double p_reproduce, double p_mutations);

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

        /*  It will check if the "percentage" of the population has found a
            solution with "n_colors"

                n_colors: The number of colours that will use as a reference
                percentage: The percentage of the population that has to found a 
                    solution with that number of colours
            return: true if all of that individuals have a solution with that n_colors 
        */
        bool CorrectColor(unsigned int n_colors, double percentage);

        /*  Main Loop for the Genetic Algorithm system
                max_iterations: maximum number of iteration before the program stops
                total_iteration: the real total iteration that the program made
                p_best: Percentage of the best individuals that will be used to create a new population
                p_cross: percentage of the new individuals that will be created reproducing other individuals
                p_mutation: Percentage of the new individuals that will be created with mutations
                min_colors: minimum amount of colors needed to solve the problem (if unknown "min_colors = 0" )
        */
        void MainLoop(unsigned int max_iterations, unsigned int &total_iterations,double p_best,double p_cross,double p_mutation, int min_colors);

        /*  Test method to mutate all the individuals of a population (just for fun)
        */
        void mutateAll(){
            for (unsigned int i = 0; i < n_individuals; i++){
                population[i].mutate();
            }
        }

        /*  It will return a random number between start and finish
        */
        double getRandom(double start, double finish){
            random_device rd;
            mt19937 mt(rd());
            uniform_real_distribution<double> dist(start, finish);
        return dist(mt);
        }

        /*  It will add the number of colors being used in each individual in the population
        */
        void ColorsPerIndividual(vector<vector<unsigned int>> &old_colors){

            for(unsigned int i = 0; i < n_individuals; i++){
                old_colors[i].push_back(population[i].getNumOfColours());
            }
        };









};