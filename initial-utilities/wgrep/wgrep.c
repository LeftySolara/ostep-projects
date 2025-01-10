/**
 * wgrep.c
 *
 * Look through input line-by-line for a user-specified
 * search term and print lines that contain it.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void search_file(char *file_path, char *search_term)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    FILE *fp = fopen(file_path, "r");
    if (fp == NULL) {
        printf("wgrep: cannot open file\n");
        exit(EXIT_FAILURE);
    }

    while ((nread = getline(&line, &len, fp)) != -1) {
        if (strstr(line, search_term) != NULL) {
            printf("%s", line);
        }
    }

    free(line);
    fclose(fp);
}

void search_stdin(char *search_term)
{
    char *line;
    int line_max = 16384;

    line = malloc(line_max + 1);
    if (line == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(line, line_max + 1, stdin) != NULL) {
        if (strstr(line, search_term) != NULL) {
            printf("%s", line);
        }
    }
    free(line);
}

int main(int argc, char **argv)
{
    if (argc <= 1) {
        printf("wgrep: searchterm [file ...]\n");
        return EXIT_FAILURE;
    }

    char *search_term = argv[1];

    if (argc == 2) {
        search_stdin(search_term);
    }
    else {
        for (int i = 2; i < argc; ++i) {
            search_file(argv[i], search_term);
        }
    }

    return 0;
}