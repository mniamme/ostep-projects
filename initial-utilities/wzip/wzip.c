#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    FILE *file;

    char *currentChar = NULL;
    char *buffer = malloc(sizeof(char));
    int count = 0;

    for (int i = 1; i < argc; i++)
    {
        // open file
        file = fopen(argv[i], "r");

        while (fread(buffer, 1, 1, file) != 0)
        {
            if (currentChar == NULL)
            {
                count = 1;
                currentChar = malloc(1);
                *currentChar = *buffer;
            }
            else if (*buffer != *currentChar)
            {
                fwrite(&count, 4, 1, stdout);
                fwrite(currentChar, 1, 1, stdout);

                count = 1;
                *currentChar = *buffer;
            }
            else
            {
                count++;
            }
        }

        // close file
        fclose(file);
    }

    fwrite(&count, 4, 1, stdout);
    fwrite(currentChar, 1, 1, stdout);

    return 0;
}