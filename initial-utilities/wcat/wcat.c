#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 16384

int main(int argc, char **argv)
{
    if (argc <= 1) {
        return 0;
    }

    FILE *fp = NULL;
    for (int i = 1; i < argc; ++i) {
        fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wcat: cannot open file\n");
            return EXIT_FAILURE;
        }

        char *line = malloc(MAX_LINE_LENGTH + 1);
        while (fgets(line, MAX_LINE_LENGTH + 1, fp) != NULL) {
            printf("%s", line);
        }
        fclose(fp);
        free(line);
    }

    return EXIT_SUCCESS;
}