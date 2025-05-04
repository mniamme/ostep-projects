#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }

    FILE* file;
    char* currentChar = malloc(1);
    int* currentCount = malloc(4);
    
    for (int i = 1; i < argc; i++)
    {
        // open file
        file = fopen(argv[i], "r");

        while (fread(currentCount, 4, 1, file) != 0)
        {
            // read char
            fread(currentChar, 1, 1, file);
            
            // print to stdout the char currentCount times
            for (int j = 0; j < *currentCount; j++)
            {
                printf("%c", *currentChar);
            }
        }

        // close file
        fclose(file);
    }
    return 0;
}