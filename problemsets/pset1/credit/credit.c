#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // check if input is a number
    // https://en.cppreference.com/w/c/string/byte/strtol
    char input[20];
    long number;
    char* end;

    do
    {
        printf("Number: ");
        scanf("%s", input);
        number = strtol(input, &end, 10);
    }
    while ((end == input) || (*end != '\0'));

    long numberCopy = number;
    int evenNumbersSum = 0;

    while (numberCopy != 0)
    {
        numberCopy /= 10;
        int digit = numberCopy % 10;
        numberCopy /= 10;

        digit *= 2;
        while (digit != 0)
        {
            evenNumbersSum += (digit % 10);
            digit /= 10;
        }
    }

    numberCopy = number;
    int oddNumbersSum = 0;
    while (numberCopy != 0)
    {
        int digit = numberCopy % 10;
        oddNumbersSum += digit;
        numberCopy /= 10;
        numberCopy /= 10;
    }

    int checkSum = evenNumbersSum + oddNumbersSum;
    int lastDigit = checkSum % 10;

    printf("multiply sum: %i\n", evenNumbersSum);
    printf("rest sum: %i\n", oddNumbersSum);
    printf("%i + %i = %i\n", evenNumbersSum, oddNumbersSum, checkSum);

    if(lastDigit == 0)
    {
        printf("last digit is 0 - the credit card number is valid\n");
    }
    else
    {
        printf("INVALID\n");
        return 0;
    }

    // 34[...], 37[...] AmericanExpress
    // 51[...], 52[...], 53[...], 54[...], 55[...] MasterCard
    // 4[...] Visa

    switch(input[0]) {
        case '3':
            if(input[1] == '4' || input[1] == '7')
            {
                printf("AMEX");
            }
            else
            {
                printf("INVALID");
            }
        break;

        case '4':
            printf("VISA");
            break;

        case '5':
            if(input[1] == '1' || input[1] == '2' || input[1] == '3' || input[1] == '4' || input[1] == '5')
            {
                printf("MASTERCARD");
            }
            else
            {
                printf("INVALID");
            }
            break;

        default:
            printf("INVALID");
            break;
    }
}
