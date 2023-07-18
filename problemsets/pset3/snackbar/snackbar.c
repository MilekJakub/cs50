#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>

#define NUM_ITEMS 10

typedef struct
{
    char *item;
    float price;
}
menu_item;

menu_item menu[NUM_ITEMS];

void add_items(void);
float get_cost(char *item);

int main(void)
{
    add_items();

    printf("\nWelcome to Beach Burger Shack!\n");
    printf("Choose from the following menu to order. Press enter when done.\n\n");

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        printf("%s: $%.2f\n", menu[i].item, menu[i]. price);
    }
    printf("\n");

    float total = 0;
    while(true)
    {
        char *item;
        size_t buffersize = 0;
        ssize_t nread;

        printf("Enter a food item: ");
        nread = getline(&item, &buffersize, stdin);

        if(nread == -1)
        {
            printf("ERROR! Cannot read food item.");
            return 1;
        }

        if (strlen(item) == 1)
        {
            printf("\n");
            break;
        }

        float cost = get_cost(item);

        if(cost == 0.0f)
        {
            printf("Invalid item!\n");
        }

        total += cost;
    }

    printf("Your total cost is: $%.2f\n", total);
}

void add_items(void)
{
    menu_item burger = { .item = "Burger", .price = 9.50 };
    menu_item vegan_burger = { .item = "Vegan Burger", .price = 11 };
    menu_item hot_dog = { .item = "Hot Dog", .price = 5 };
    menu_item cheese_dog = { .item = "Cheese Dog", .price = 7 };
    menu_item fries = { .item = "Fries", .price = 5 };
    menu_item cheese_fries = { .item = "Cheese Fries", .price = 6 };
    menu_item cold_pressed_juice = { .item = "Cold Pressed Juice", .price = 7 };
    menu_item cold_brew = { .item = "Cold Brew", .price = 3 };
    menu_item water = { .item = "Water", .price = 2 };
    menu_item soda = { .item = "Soda", .price = 2 };

    menu[0] = burger;
    menu[1] = vegan_burger;
    menu[2] = hot_dog;
    menu[3] = cheese_dog;
    menu[4] = fries;
    menu[5] = cheese_fries;
    menu[6] = cold_pressed_juice;
    menu[7] = cold_brew;
    menu[8] = water;
    menu[9] = soda;

    return;
}

float get_cost(char *item)
{
    float price = 0.0f;
    size_t length = strlen(item);
    item[length - 1] = '\0';

    for(int i = 0; i < NUM_ITEMS; i++)
    {
        if(strcmp(item, menu[i].item) == 0)
        {
            price = menu[i].price;
            break;
        }
    }

    return price;
}
