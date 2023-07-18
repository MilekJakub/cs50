// Calculate your half of a restaurant bill
// Data types, operations, type casting, return value

#include <stdio.h>

float half(float bill, float tax, int tip);

int main(void)
{
    float bill_amount;
    printf("Bill before tax and tip: ");
    scanf("%f", &bill_amount);

    float tax_percent;
    printf("Sale Tax Percent: ");
    scanf("%f", &tax_percent);

    int tip_percent;
    printf("Tip percent: ");
    scanf("%d", &tip_percent);

    printf("You will owe $%.2f each!\n", half(bill_amount, tax_percent, tip_percent));
}

float half(float bill, float tax, int tip)
{
    float calculatedTax = bill * (tax / 100);
    float calculatedTip = (bill + calculatedTax) * ((float)tip / 100);
    return (bill + calculatedTax + calculatedTip) / 2;
}
