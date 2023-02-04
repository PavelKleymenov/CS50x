// Simulate the inheritance of blood types for each member of a family

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Create a structure called person wherein the first member
    is the 2 parents that parents the person has, and second is
    the number of gene forms determining person's bloodtype */
typedef struct person

{
    struct person *parents[2];
    char alleles[2];
}

// Declare a variable representing person
person;

/*Make sure to specify the number of generations
    the should program examine, as well as,
        how the output should be indented */
const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

// Include the prototypes for the functions implemented below
person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)

{
    // Initialize random number generator
    srand(time(0));

    // Create a family which is spread across three generations
    person *p = create_family(GENERATIONS);

    /* Print a family tree that indicates the blood type
            of every family member*/
    print_family(p, 0);

    // Free allocated memory so as to prevent memory leaks
    free_family(p);
}

// Create a new individual with `generations`
person *create_family(int generations)

{
    // Allocate memory for a new person
    person *p = malloc(sizeof(person));

    // Return NULL if allocation fails to come about
    if (p == NULL)

    {
        return NULL;
    }

    // If there are still generations to create
    if (generations > 1)
    
    {
        // Create a pair of new parents for the current person by recursively calling create_family
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        // Set parent pointers for the current person
        p->parents[0] = parent0;
        p->parents[1] = parent1;

        // Randomly assign current person's alleles based on the alleles of their parents
        p->alleles[0] = p->parents[0]->alleles[rand() % 2];
        p->alleles[1] = p->parents[1]->alleles[rand() % 2];
    }

    // If there are no generations left to create
    else
    
    {

        // Set parent pointers to NULL
        p->parents[0] = NULL;
        p->parents[1] = NULL;

        // Randomly assign alleles
        p->alleles[0] = random_allele();
        p->alleles[1] = random_allele();

    }

    // Return newly created person
    return p;
}

// Free `p` and all ancestors of `p`.
void free_family(person *p)

{

    if (p == NULL)

    {
        return;
    }

    free_family(p->parents[0]);
    free_family(p->parents[1]);

    free(p);

}

// Print each family member and their alleles.
void print_family(person *p, int generation)

{

    if (p == NULL)

    {
        return;
    }

    // Make sure that output gets printed with the desired indentation
    for (int i = 0; i < generation * INDENT_LENGTH; i++)

    {
        printf(" ");
    }

    // Display child' alleles
    if (generation == 0)

    {
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }

    // Display parents' alleles
    else if (generation == 1)
    
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }

    else

    {   // Display alleles of the grandparents
        for (int i = 0; i < generation - 2; i++)
        
        {
            printf("Great-");
        }
        
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0], p->alleles[1]);
    }

    // Print the parents of current generation
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Implement a function that randomly chooses a blood type allele
char random_allele()

{
    // This variable is there to determine the allele
    int r = rand() % 3;

    // If no remainder - assign the 'A'
    if (r == 0)

    {
        return 'A';
    }

    // If remainder amounts to one - assign the 'B'
    else if (r == 1)

    {
        return 'B';
    }

    // Render an apology if remainder is neither 0, nor 1
    else
 
    {
        return 'O';
    }
}