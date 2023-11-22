// Include everything necessary here
#include <stdlib.h>
#include "functions.h"

double generate_random(double min, double max)
{
    // implement a function to return a value between min and max
    return min + (max - min) * (double)rand() / (double)RAND_MAX;
}

unsigned int generate_int()
{
    // implement the function to return a random integer value
    return (unsigned int)rand();
}

// Function to initialize a random population
void generate_population(int POPULATION_SIZE, int NUM_VARIABLES, double population[POPULATION_SIZE][NUM_VARIABLES], double Lbound[NUM_VARIABLES], double Ubound[NUM_VARIABLES]) {
    // randomly initialize for all values in "population[i][j]""
    int i, j;
    for (i = 0; i < POPULATION_SIZE; i++) {
        for (j = 0; j < NUM_VARIABLES; j++) {
            population[i][j] = generate_random(Lbound[j], Ubound[j]);
        }
    }
}

// Function to compute the objective function for each member of the population
void compute_objective_function(int POPULATION_SIZE, int NUM_VARIABLES, double population[POPULATION_SIZE][NUM_VARIABLES], double fitness[POPULATION_SIZE])
{
    /* compute "fitness[i]"" for each set of decision variables (individual) or each row in "population"
    by calling "Objective_function" */
    for(int i = 0; i < POPULATION_SIZE; i++){
        fitness[i] = Objective_function(NUM_VARIABLES, population[i]);
    }
}


void crossover(int POPULATION_SIZE, int NUM_VARIABLES, double fitness[POPULATION_SIZE], double new_population[POPULATION_SIZE][NUM_VARIABLES], double population[POPULATION_SIZE][NUM_VARIABLES], double crossover_rate)
{
    /* Implement the logic of crossover function here based on "fitness_probs" or each set
    of decision variables (individual) or each row in "population".
    And save the new population in "new_population"*/
    double total_fitness = 0.0;
    double fitness_probs[POPULATION_SIZE];
    double cumulative_prob[POPULATION_SIZE];
    int index[POPULATION_SIZE];

    //Calculating the total fitness and probabilities like the provided pdf
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        total_fitness += fitness[i];
    }
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        fitness_probs[i] = fitness[i] / total_fitness;
    }
    cumulative_prob[0] = fitness_probs[0];
    for (int i = 1; i < POPULATION_SIZE; i++)
    {
        cumulative_prob[i] = fitness_probs[i]+cumulative_prob[i-1];
    }

    // Selecting two individuals to crossover
    for (int i = 0; i < POPULATION_SIZE-1; i++)
    {
        double random_num=generate_random(0,1);
        if (cumulative_prob[i]<random_num && random_num<cumulative_prob[i+1])
        {
            index[i]=i;
        }
        else
        {
            index[i]=1;
        }
    }

    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        for (int j = 0; j < NUM_VARIABLES-1; j++)
        {
            new_population[i][j] = population[index[i]][j];
        }
    }
    // loop to decide which variables are going to be used for crossover
    for (int i = 0; i < POPULATION_SIZE; i+=2)
    {
        double random_num=generate_random(0,1);
        if (random_num<crossover_rate)
        {
            double parent1[NUM_VARIABLES];
            double parent2[NUM_VARIABLES];
            for (int j = 0; j < NUM_VARIABLES; j++)
            {
                parent1[j] = new_population[i][j];
                parent2[j] = new_population[i + 1][j];
            }

            int crosspoint = generate_int() % (NUM_VARIABLES - 1) + 1;
            double child1[NUM_VARIABLES];
            double child2[NUM_VARIABLES];

            //performing the crossover ith child1 and child2
            for (int j = 0; j < crosspoint; j++)
            {
                child1[j] = parent1[j];
                child2[j] = parent2[j];
            }

            for (int j = crosspoint; j < NUM_VARIABLES; j++)
            {
                child1[j] = parent2[j];
                child2[j] = parent1[j];
            }

            // Replace the parents with the new children in new_population
            for (int j = 0; j < NUM_VARIABLES; j++)
            {
                new_population[i][j] = child1[j];
                new_population[i + 1][j] = child2[j];
            }
        }
    }
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        for (int j = 0; j < NUM_VARIABLES; j++)
        {
            population[i][j] = new_population[i][j];
        }
    }
}

//follows the same logic of the python code that was provided
void mutate(int POPULATION_SIZE, int NUM_VARIABLES, double new_population[POPULATION_SIZE][NUM_VARIABLES], double population[POPULATION_SIZE][NUM_VARIABLES], double Lbound[NUM_VARIABLES], double Ubound[NUM_VARIABLES], double mutate_rate)
{
    //finding the total number of variables in the population
    int total_gen = NUM_VARIABLES*POPULATION_SIZE;
    int total_gen_mutate = total_gen * mutate_rate;

    //using the loop to mutate random genes
    for (int i = 0; i < total_gen_mutate; i++)
    {
        int rand1 = rand() % POPULATION_SIZE;
        int rand2 = rand() % NUM_VARIABLES;

        new_population[rand1][rand2] = generate_random(Lbound[NUM_VARIABLES], Ubound[NUM_VARIABLES]);
    }

    //copying the mutations into the population
    for (int i = 0; i < POPULATION_SIZE; i++)
    {
        for (int j = 0; j < NUM_VARIABLES; j++)
        {
            population[i][j] = new_population[i][j];
        }
    }
}
