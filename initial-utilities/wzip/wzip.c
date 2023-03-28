/**
 * wzip.c
 *
 * Simple run-length encoding tool.
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Write the given run length to standard output.
 *
 * The run length is written as a 4-byte integer while the char
 * is written as a normal char.
 *
 * @param run_length The run length to write.
 * @param ch The character to write.
 */
void write_run_length(size_t run_length, char ch)
{
    unsigned char bytes[4];

    bytes[3] = (run_length >> 24) & 0xFF;
    bytes[2] = (run_length >> 16) & 0xFF;
    bytes[1] = (run_length >> 8) & 0xFF;
    bytes[0] = run_length & 0xFF;

    fwrite(bytes, sizeof(bytes[0]), 4, stdout);
    fprintf(stdout, "%c", ch);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    char buf[2], buf_prev[2];
    size_t count = 0;

    for (int i = 1; i < argc; ++i) {
        FILE *fp = fopen(argv[i], "r");
        if (!fp) {
            printf("wzip: cannot open file\n");
            exit(1);
        }

        while (fread(buf, 1, 1, fp) != 0) {
            if (strcmp(buf, buf_prev) == 0) {
                ++count;
            }
            else {
                if (buf_prev[0] != '\0') {
                    write_run_length(count, buf_prev[0]);
                }
                count = 1;
                strcpy(buf_prev, buf);
            }
        }

        fclose(fp);
    }

    write_run_length(count, buf_prev[0]);

    return 0;
}
