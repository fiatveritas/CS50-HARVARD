#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    else if (argc == 2)
    {
        //code
        //printf("made it here!\n");
        typedef uint8_t BYTE;
        char *infile = argv[1]; //this is the string containing file name
        FILE *inptr = fopen(infile, "r");
        char filename[64];
        if (inptr == NULL)
        {
            fprintf(stderr, "Could not open %s.\n", infile);
            return 3;
        }

        // Ensure infile is (likely) a 24-bit uncompressed BMP 4.0
        int counter = 0;
        int i = 0;
        int const B_SIZE = 512;
        BYTE bytes[B_SIZE]; //the encoding for jpegs is in BYTE data type
        size_t elements = fread(bytes, 1, B_SIZE, inptr); //rubber stamp while() loop, I almost forgot why I need this
        while (elements > 0)
        {
            if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (((bytes[3] & 0xf0) >= 0xe0) && ((bytes[3] & 0xf0) <= 0xef)))
            {
                sprintf(filename, "%03i.jpg", counter);
                FILE *outptr = fopen(filename, "w");
                fwrite(&bytes, sizeof(bytes), 1, outptr);
                elements = fread(bytes, 1, B_SIZE, inptr);
                //need this nested while loop to keep pushing things into the image file
                //it breaks out if it detects the header for another jpeg
                while (elements > 0)
                {
                    if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (((bytes[3] & 0xf0) >= 0xe0) && ((bytes[3] & 0xf0) <= 0xef)))
                    {
                        fclose(outptr);
                        break;
                    }
                    else
                    {
                        fwrite(&bytes, sizeof(bytes), 1, outptr); //pass in the address of the bytes, bytes is not in the heap
                        elements = fread(bytes, 1, B_SIZE, inptr);
                    }
                }
                counter++;
            }
            else
            {
                elements = fread(bytes, 1, B_SIZE, inptr); //this else statement is needed incase the first try doesn't find jpg
                continue;
            }
        }
        // Close infile
        fclose(inptr);

        return 0;
    }
    else
    {
        printf("Usage: ./recover image\n");
        return 2;
    }

}
