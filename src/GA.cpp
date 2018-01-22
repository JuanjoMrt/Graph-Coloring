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

    GA::GA(unsigned int n_genes, unsigned int n_edges, vector<vector<unsigned int>> main_graph){
        this->n_genes = n_genes;
        this->n_edges = n_edges;
        this->main_graph = main_graph;
        this->n_individuals = 0;
    }


    void GA::addIndividual(Individual ind_new){
        this->population.push_back(ind_new);
        n_individuals++;
    };

    vector<Individual> GA::FindBestIndividuals( double percentage){
        
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

        //Number of individuals that we will choose
        int n_best_individuals = percentage*n_individuals;


        /*  Here we pop the elements that we want
        */
        for (int i = 0; i < n_best_individuals; ++i) {
            int ki = best_ind.top().second;

            best_individuals.push_back(this->population[ki]);
            
            best_ind.pop();
        }

        return best_individuals;
    };

    vector<Individual> GA::Reproduce(vector<Individual> population, unsigned int new_ind){
        vector<Individual> new_population;
        unsigned int parent_1, parent_2;
        Individual son(n_genes);
        unsigned int n_individuals = population.size();
        

        for(unsigned int i = 0; i < new_ind;i++){
            parent_1 = getRandom(0, n_individuals);
        
            //This way we won't have parent_1 == parent_2
            parent_2 = (parent_1 + (int)getRandom(1, n_individuals - 1))  % n_individuals;
            //cout << "parent 1: " << parent_1 << ", parent 2: " << parent_2 << endl;

            son = population[parent_1].reproduce(population[parent_2]);
            new_population.push_back( son );

        }
        return new_population;
    }

    vector<Individual> GA::Mutate(vector<Individual> population, unsigned int new_ind){
        vector<Individual> new_population;
        unsigned int random_idx;

        for(unsigned int i = 0; i < new_ind; i++){
            random_idx = getRandom(0, population.size());

            Individual new_individual = population[random_idx];
            new_individual.mutate();
            new_population.push_back(new_individual);
        }
        return new_population;
    }


    void GA::CreateNewPopulation(double p_best, double p_reproduce, double p_mutations){
        double p_total = p_best + p_reproduce + p_mutations;
        
        p_best = p_best / p_total;
        double n_reproduce = n_individuals * (p_reproduce / p_total);
        double n_mutations = n_individuals * (p_mutations / p_total);
        vector<Individual> new_population;
        
        new_population = FindBestIndividuals(p_best);
        
        vector<Individual> reproduce_v = Reproduce(new_population, n_reproduce);
        vector<Individual> mutate_v = Mutate(new_population, n_mutations);
        
        //Insert the reproduce and mutate vector into the new population.
        
        new_population.insert(end(new_population), begin(reproduce_v), end(reproduce_v));
        
        new_population.insert(end(new_population), begin(mutate_v), end(mutate_v));


        this->population = new_population;
    }


    unsigned int GA::fitnessOfIndividual(unsigned int index){
        
        unsigned int fit = 0;
        //If we calculate it previously we dont need to do it again
        if(population[index].getFitness() != 0){
            fit = population[index].getFitness();
        }
        else{
            
            for(unsigned int i = 0; i < n_genes; i++){
                //cout << endl <<"i=" << i << "-  ";
                for(unsigned int j = 0; j < main_graph[i].size(); j++){
                    unsigned int cmp_number = population[index].at( main_graph[i][j] );
                    //cout << population[index].at(i)<<","<< cmp_number << " " ;
                    if(population[index].at(i) != cmp_number){
                        fit++;
                    //    cout << "1 ";
                    }
                    /*else{
                        cout << "0 ";
                    }*/
                }

            }
            if(fit == n_edges)
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

    bool GA::CorrectColor(unsigned int n_colors, double percentage){
        int avg = 0;
        bool finish = false;
        double per = n_individuals * (percentage/100);

        for(unsigned int i = 0; i < population.size() && !finish; i++){
            if(population[i].getNumOfColours() == n_colors){
                avg++;
                if(avg == per)
                    finish = true;
            }
        }

        return finish;
    };


    void GA::MainLoop(unsigned int max_iterations,unsigned int &total_iterations,double p_best,double p_cross,double p_mutation, int min_colors){
        bool cor_color = false;
        cout << endl;
        for(total_iterations = 0; total_iterations < max_iterations && !cor_color; total_iterations++){
            //cout << "NEW POPULATION in iteration " << j << ":" << endl;
            this->CreateNewPopulation( 40.0, 40.0, 20.0);
            if(this->CorrectColor(min_colors,100.0 - p_mutation)){
                cor_color = true;
            }
        }

    }