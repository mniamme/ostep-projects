#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    // if no file is provided, exit 0
    if (argc < 2)
    {
        exit(0);
    }

    FILE *input;

    char buffer[BUFFER_SIZE];

    // for each file specifed
    for (int i = 1; i < argc; i++)
    {
        input = fopen(argv[i], "r");

        // if file couldn't be opened, exit 1
        if (input == NULL)
        {
            printf("wcat: cannot open file\n");
            exit(1);
        }

        // read the content of the file and write it to the standard output
        while (fgets(buffer, BUFFER_SIZE, input) != NULL)
        {
            printf("%s", buffer);
        }

        // close the file
        fclose(input);
    }

    return 0;
}
