#include <stdio.h>
#include <stdlib.h>

long get_cents(void);
int calculate_quarters(long cents);
int calculate_dimes(long cents);
int calculate_nickels(long cents);
int calculate_pennies(long cents);

int main(void)
{
    // Ask how many cents the customer is owed
    long cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

long get_cents(void)
{
    char *line = NULL;
    char *end = NULL;
    size_t size = 0;
    ssize_t result;
    long cents;

    do
    {
        printf("Change owed: ");
        result = getline(&line, &size, stdin);

        if(result == -1)
        {
            continue;
        }

        cents = strtol(line, &end, 10);
    }
    while(result == -1 || line == end || cents < 1);

    free(line);

    return cents;
}

int calculate_quarters(long cents)
{
    return cents / 25;
}

int calculate_dimes(long cents)
{
    return cents / 10;
}

int calculate_nickels(long cents)
{
    return cents / 5;
}

int calculate_pennies(long cents)
{
    return cents;
}

