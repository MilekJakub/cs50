#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "wav.h"

bool check_format(WAVHEADER header);
uint8_t get_block_size(WAVHEADER header);

const int HEADER_SIZE = 42 * 8;

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if(argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav");
        return 1;
    }

    // Open input file for reading
    FILE *input = fopen(argv[1], "r");

    if(input == NULL)
    {
        printf("Could not open the '%s' file.\n", argv[1]);
        return 1;
    }

    // Read header
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, input);

    // Use check_format to ensure WAV format
    if(!check_format(header))
    {
        printf("This is not valid .wav file.\n");
        fclose(input);
        return 1;
    }

    // Open output file for writing
    FILE *output = fopen(argv[2], "w");
    if(output == NULL)
    {
        printf("Could not create file.\n");
        fclose(input);
        return 1;
    }

    // Write header to file
    fwrite(&header, sizeof(WAVHEADER), 1, output);

    // Use get_block_size to calculate size of block
    uint8_t block_size = get_block_size(header);

    // Write reversed audio to file
    uint8_t buffer[block_size];
    uint32_t number_of_blocks = 0;
    fseek(input, HEADER_SIZE, SEEK_SET);

    while(fread(&buffer, sizeof(buffer), 1, input) == 1)
    {
        number_of_blocks++;
    }

    uint8_t blocks[number_of_blocks][block_size];

    fseek(input, HEADER_SIZE, SEEK_SET);
    uint32_t index = 0;

    while(fread(&buffer, sizeof(buffer), 1, input) == 1)
    {
        for(int i = 0; i < block_size; i++)
        {
            blocks[index][i] = buffer[i];
        }

        index++;
    }

    printf("number_of_blocks: %i\n", number_of_blocks);
    printf("index: %i\n", index);

    for(int i = number_of_blocks; i > 0; i--)
    {
        for(int j = 0; j < block_size; j++)
        {
            buffer[j] = blocks[i][j];
        }
        fwrite(&buffer, sizeof(buffer), 1, output);
    }
    
    fclose(input);
    fclose(output);

    return 0;
}

bool check_format(WAVHEADER header)
{
    return header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E';
}

uint8_t get_block_size(WAVHEADER header)
{
    return header.numChannels * header.bitsPerSample;
}

