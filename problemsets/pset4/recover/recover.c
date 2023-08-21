#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

bool isJPEG(uint8_t *bytes);
 
int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./recover file.raw\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if(input == NULL)
    {
        printf("Cannot open the file with path '%s'\n", argv[1]);
        return 1;
    }

    uint8_t buffer[512];
    int jpeg_counter = 0;
    char filename[8];
    bool saving = false;
    FILE *output;

    while(fread(&buffer, sizeof(int8_t), 512, input) == 512)
    {
        if(isJPEG(buffer))
        {
            saving = true;
            jpeg_counter++;
            sprintf(filename, "%i.jpeg", jpeg_counter);

            output = fopen(filename, "w");
            if (output == NULL)
            {
                printf("Could not create %s.\n", filename);
                fclose(input);
                return 1;
            }

            fwrite(&buffer, sizeof(int8_t), 512, output);
        }
        else if(saving)
        {
            fwrite(&buffer, sizeof(int8_t), 512, output);
        }
    }

    printf("jpg count: %i\n", jpeg_counter);

    fclose(input);
    fclose(output);

    return 0;
}

bool isJPEG(uint8_t *bytes)
{
    // jpeg file starts with:
    // 11111111 11011000 11111111 1110....
    return bytes[0] == 0b11111111 && bytes[1] == 0b11011000 && bytes[2] == 0b11111111 && bytes[3] >> 4 == 0b1110;
}
 
