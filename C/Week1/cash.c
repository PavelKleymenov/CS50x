#include <stdio.h>

// Include the prototype for each function implemented below
int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)

{
    // Ask how many cents the customer should receive
    int cents = get_cents();

    // Calculate the number of quarters to be given to the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to be given to the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to be given to the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to be given to the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Calculate the total number of coins to hand out
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to be given to the customer
    printf("%i\n", coins);
}

int get_cents(void)

{
    int cents;
    do
    
    {
        // Prompt user for the number of change that is due
        printf("Cents due: ");

        // Get and save the input the user has typed
        scanf("%d", &cents);
    }
    
    while (cents < 0);

    // Return cents
    return cents;
}

int calculate_quarters(int cents)

{
    int quarters = 0;

    while (cents >= 25)

    {
        cents = cents - 25;
        quarters++;
    }

    // Return quarters
    return quarters;
}

int calculate_dimes(int cents)

{
    int dimes = 0;

    while (cents >= 10)

    {
        cents = cents - 10;
        dimes++;
    }

    // Return dimes
    return dimes;
}

int calculate_nickels(int cents)

{
    int nickels = 0;

    while (cents >= 5)

    {
        cents = cents - 5;
        nickels++;
    }

    // Return nickels
    return nickels;
}

int calculate_pennies(int cents)

{
    int pennies = 0;

    while (cents >= 1)

    {
        cents = cents - 1;
        pennies++;
    }

    // Return pennies
    return pennies;
}