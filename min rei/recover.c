#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t BYTE;

bool check(BYTE *buffer);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Remember file names
    char *infile = argv[1];

    // Open input file
    FILE *inptr = fopen(infile, "r");
    // Checks if input file returns null
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    // Initialise buffer
    BYTE *buffer = malloc(512);
    // Initialise filename array
    char filename[8];
    // Initialise file number
    int filenumber = 0;
    // Initialise size_t block (full-512 or not-terminate)
    size_t block = 512;

    // Repeat until end of card (read 512 BYTES at a time)
    while (block == 512)
    {
        // If start of new JPEG
        if (check(buffer) == true)
        {
            // Create new file
            sprintf(filename, "%03i.jpg", filenumber);
            FILE *img = fopen(filename, "w");
            filenumber ++;

            // Write until new jpeg signature
            do
            {
                fwrite(buffer, 1, 512, img);
                block = fread(buffer, 1, 512, inptr);
            }
            while (!check(buffer) && block == 512);

            fclose(img);
        }
        else if (check(buffer) == false)
        {
            // Initialise the first block
            block = fread(buffer, 1, 512, inptr);
        }
    }

    // Free memory for buffer
    free(buffer);

    // Close infile
    fclose(inptr);

    return 0;
}

// Check if JPEG found
bool check(BYTE *b)
{
    if (b[0] == 0xff && b[1] == 0xd8 && b[2] == 0xff && ((b[3] & 0xf0) == 0xe0))
    {
        return true;
    }
    else
    {
        return false;
    }
}
