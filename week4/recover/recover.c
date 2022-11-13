#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc != 2)
    {
        printf("Usage: .recover IMAGE\n");
        return 1;
    }

    // open memory card file
    FILE *raw_file = fopen(argv[1], "r");

    // establish buffer
    const int BLOCK_SIZE = 512;
    BYTE buffer[BLOCK_SIZE];

    // establish file counter
    int counter = 0;
    char *filename = malloc(8 * sizeof(char));
    FILE *img = NULL;

    // repeat until end of card
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        // look for beginning of a JPEG file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // start of JPEG
            // if first JPEG
            if (counter == 0)
            {
                // create new JPEG file
                sprintf(filename, "%03i.jpg", counter);
                img = fopen(filename, "w");
            }
            else
            {
                // close existing JPEG file
                fclose(img);

                // create new JPEG file
                sprintf(filename, "%03i.jpg", counter);
                img = fopen(filename, "w");
            }

            // write data
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);

            // increase counter for next file
            counter += 1;

        }
        else
        {
            // not start of JPEG
            // keep writing to current file (if any)
            if (counter > 0)
            {
                // keep writing to current file
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
            }
        }
    }

    // close any remaining files
    fclose(img);
    fclose(raw_file);
    free(filename);
}
