// Include everything necessary here 
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main(int argc, char *argv[])
{
    // <YOUR CODE: Handle the possible errors in input data given by the user and say how to execute the code>
    srand((unsigned int)time(NULL));

    if (argc != 6)
    {
        printf("Usage: %s POPULATION_SIZE MAX_GENERATIONS crossover_rate mutation_rate stop_criteria\n", argv[0]);
        return 1;
    }

    // <YOUR CODE: Assign all inputs given by the user argv[i]> like
    // POPULATION_SIZE, MAX_GENERATIONS, crossover_rate, mutate_rate, stop_criteria
    int POPULATION_SIZE = atoi(argv[1]);
    int MAX_GENERATIONS = atoi(argv[2]);
    double crossover_rate = atof(argv[3]);
    double mutate_rate = atof(argv[4]);
    double stop_criteria = atof(argv[5]);
    double best_fitness = 1e20;
    int running_generation = 1;

    if (POPULATION_SIZE <= 0 || MAX_GENERATIONS <= 0 || crossover_rate < 0 || mutate_rate < 0 || stop_criteria < 0){ // checks if input is valid
        printf("Invalid input, please try again\n");
        return 1;
    }
    // ###################################################################################
    // you dont need to change anything here
    // the number of variables
    int NUM_VARIABLES = 2;
    // the lower bounds of variables
    double Lbound[] = {-5.0, -5.0};
    // the upper bounds of variable
    double Ubound[] = {5.0, 5.0};
    // ###################################################################################


    // <YOUR CODE: Here make all the initial print-outs>
    printf("Genetic Algorithm is initiated.\n");
    printf("------------------------------------------------\n");
    printf("The number of variables: %d\n", NUM_VARIABLES);
    printf("Lower bounds: [%f, %f]\n", Lbound[0], Lbound[1]);
    printf("Upper bounds: [%f, %f]\n", Ubound[0], Ubound[1]);
    printf("Population Size: %d\n", POPULATION_SIZE);
    printf("Max Generations: %d\n", MAX_GENERATIONS);
    printf("Crossover Rate: %f\n", crossover_rate);
    printf("Mutation Rate: %f\n", mutate_rate);
    printf("Stopping criteria: %e\n", stop_criteria);
    printf("Results\n");
    printf("------------------------------------------------\n");

    clock_t start_time, end_time;
    double cpu_time_used;
    start_time = clock();

    // <YOUR CODE: Declare all the arrays you need here>
    double population[POPULATION_SIZE][NUM_VARIABLES];
    double new_population[POPULATION_SIZE][NUM_VARIABLES];
    double fitness[POPULATION_SIZE];
    double best_solution[NUM_VARIABLES];

    // <YOUR CODE: Call generate_population function to initialize the "population"> like:
    // generate_population(POPULATION_SIZE, NUM_VARIABLES, population, Lbound, Ubound);
    generate_population(POPULATION_SIZE, NUM_VARIABLES, population, Lbound, Ubound);


    // iteration starts here. The loop continues until MAX_GENERATIONS is reached
    // Or stopping criteria is met
    for (int generation = 0; generation < MAX_GENERATIONS; generation++)
    {

        printf("Generation: %d\n", generation);
        // <YOUR CODE: Compute the fitness values using objective function for
        // each row in "population" (each set of variables)> like:
        // compute_objective_function(POPULATION_SIZE, NUM_VARIABLES, population, fitness);
        compute_objective_function(POPULATION_SIZE, NUM_VARIABLES, population, fitness);

        // <YOUR CODE: Here implement the logic of finding the best solution with minimum fitness value
        // and the stopping criteria>

       printf("Current best fitness: %f\n", best_fitness);
       // printf("Current fitness[0]: %f\n", fitness[0]);

        //chcecking the fitness values to see improvement
        for (int i = 0; i < POPULATION_SIZE; i++)
        {
            if (fitness[i] < best_fitness)
            {
                best_fitness = fitness[i];
                for (int j =0; j < NUM_VARIABLES; j++)
                {
                    best_solution[j] = population[i][j];
                }
            }
        }

        // Check the stopping criteria (difference between current and previous best fitness)
        if (best_fitness < stop_criteria)
        {
            printf("Stopping criteria met. Algorithm terminated.\n");
            break;// Exit the loop
        }


        // <YOUR CODE: Here call the crossover function>
        crossover(POPULATION_SIZE, NUM_VARIABLES, fitness, new_population, population, crossover_rate);

        // <YOUR CODE: Here call the mutation function>
        mutate(POPULATION_SIZE, NUM_VARIABLES, new_population, population, Lbound, Ubound, mutate_rate);
        // Now you have a new population, and it goes to the beginning of loop to re-compute all again
    }
    // <YOUR CODE: Jump to this part of code if the stopping criteria is met before MAX_GENERATIONS is met>


    // ###################################################################################
    // You dont need to change anything here
    // Here we print the CPU time taken for your code
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("CPU time: %f seconds\n", cpu_time_used);
    // ###################################################################################

    // <Here print out the best solution and objective function value for the best solution like the format>
    //loop to print out the best solution and objective function value for the best solution
    printf("Best solution: ");
    for (int i = 0; i < NUM_VARIABLES; i++)
    {
        printf("%f ", best_solution[i]);
    }
    printf("\n");
    printf("Best objective function value: %f\n", best_fitness);

    return 0;
    // <YOUR CODE: End of the program>
}
