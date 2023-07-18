#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    char* names[7] = { "Bill", "Charlie", "Fred", "George", "Ginny", "Percy", "Ron" };
    int length = sizeof(names) / sizeof(names[0]);
    char match[] = "Ron";

    for(int i = 0; i < length; i++)
    {
        if(strcmp(names[i], match) == 0)
        {
            printf("%s == %s\n", names[i], match);
            printf("true");
            return 0;
        }
    }

    printf("false");
    return 0;
}
