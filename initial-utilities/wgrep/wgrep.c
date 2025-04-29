#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool findPattern(char *s, int n, char *p)
{
    int p_ptr = 0;
    for (int i = 0; i < n; i++)
    {

        // if current char in s matches where the p_ptr is pointing,
        // proceed to the next char to compare.
        // otherwise, reset the counter to search for the pattern again.
        if (s[i] == p[p_ptr])
        {
            p_ptr++;
        }
        else
        {
            p_ptr = 0;
        }

        // if all chars in p were matched, return true
        if (p_ptr == strlen(p))
        {
            return true;
        }
    }

    return false;
}

void grep(FILE *file, char *p)
{
    // set buffer to null and its size to zero to allow geline automatically allocate buffer
    char *buffer = NULL;
    size_t n = 0;

    // Read line by line and for each line search for the pattern inside it
    int nr;
    while ((nr = getline(&buffer, &n, file)) != -1)
    {
        // find pattern
        bool patternFound = findPattern(buffer, nr, p);

        // if pattern found in line, print the line
        if (patternFound)
        {
            printf("%s", buffer);
        }
    }

    free(buffer);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        // exit with 1. and print how to use message
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }
    else if (argc == 2)
    {
        // read from the stdin
        grep(stdin, argv[1]);
    }
    else
    {
        for (int i = 2; i < argc; i++)
        {
            // open file
            FILE *file = fopen(argv[i], "r");

            if (file == NULL)
            {
                printf("wgrep: cannot open file\n");
                exit(1);
            }

            // search for pattern in file
            grep(file, argv[1]);

            fclose(file);
        }
    }
    return 0;
}