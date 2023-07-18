#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool valid(char *password);

// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
int main(void)
{
    char password[255];
    printf("Enter your password: ");
    scanf("%s", password);

    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

bool valid(char *password)
{
    bool uppercaseLetter = false;
    bool lowercaseLetter = false;
    bool numberCharacter = false;
    bool symbolCharacter = false;

    int length = strlen(password);

    for(int i = 0; i < length; i++)
    {
        if (isupper(password[i]) != 0)
        {
            uppercaseLetter = true;
        }

        if (islower(password[i]) != 0)
        {
            lowercaseLetter = true;
        }

        if (isdigit(password[i]) != 0)
        {
            numberCharacter = true;
        }

        // ASCII 33 - 47
        if(password[i] > 32 && password[i] < 48)
        {
            symbolCharacter = true;
        }
    }

    return uppercaseLetter && lowercaseLetter && numberCharacter && symbolCharacter;
}

