/**
 * wgrep.c
 *
 * Searches a file for a specified term.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Search a file and print any line that contains the search term.
 *
 * @param path The path to the file to search.
 * @param search_term The substring to search for.
 */
void search_file(const char *path, const char *search_term)
{
    FILE *fp = fopen(path, "r");
    if (!fp) {
        printf("wgrep: cannot open file\n");
        exit(1);
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    while ((nread = getline(&line, &len, fp)) != -1) {
        if (strstr(line, search_term)) {
            printf("%s", line);
        }
    }

    free(line);
    fclose(fp);
}

/**
 * Search standard input for a search term.
 *
 * @param search_term The substring to search for.
 */
void search_stdin(const char *search_term)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    while ((nread = getline(&line, &len, stdin)) != -1) {
        if (strstr(line, search_term)) {
            printf("%s", line);
        }
    }
    free(line);
}

int main(int argc, char *argv[])
{
    if (argc <= 1) {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }

    const char *search_term = argv[1];
    if (strlen(search_term) == 0) { /* match no lines */
        return 0;
    }

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
