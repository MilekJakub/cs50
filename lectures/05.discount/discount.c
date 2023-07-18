#include <stdio.h>

float discount(float price, int percent);

int main(void)
{
    float regular, sale;
    int percentOff;

    printf("Regular price: ");
    scanf("%f", &regular);

    printf("Percent Off: ");
    scanf("%d", &percentOff);

    sale = discount(regular, percentOff);
    printf("Sale price: %.2f\n", sale);

    return 0;
}

float discount(float price, int percent)
{
    return price * (100 - percent) / 100;
}

