/**
 * wcat.c
 *
 * Reads a file and prints out its contents.
 */

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_LENGTH 1024

/**
 * Print the contents of a file to standard output.
 */
void print_file(const char *path)
{
    FILE *fp = fopen(path, "r");
    if (!fp) {
        printf("wcat: cannot open file\n");
        exit(1);
    }

    char *buffer = malloc(sizeof(char) * BUFFER_LENGTH);
    while (fgets(buffer, BUFFER_LENGTH, fp)) {
        printf("%s", buffer);
    }

    free(buffer);
    fclose(fp);
}

int main(int argc, char *argv[])
{
    if (argc == 1) {
        return 0;
    }

    for (int i = 1; i < argc; ++i) {
        print_file(argv[i]);
    }

    return 0;
}
