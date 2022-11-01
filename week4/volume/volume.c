// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);
    printf("%f\n", factor);

    // TODO: Copy header from input file to output file
    // read header from input - 44 bytes - fread
    uint8_t header[HEADER_SIZE];
    fread(header, HEADER_SIZE, 1, input);

    // write header to output - fwrite
    fwrite(header, HEADER_SIZE, 1, output);

    // TODO: Read samples from input file and write updated data to output file

    int16_t buffer;
    int16_t new_buffer;

    // repeat for each sample:
    // read the sample
    // multiply by the factor
    // write new sample to output

    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        new_buffer = buffer * factor;
        fwrite(&new_buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
