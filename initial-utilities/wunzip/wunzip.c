/**
 * wunzip.c
 *
 * RLE file decompression tool.
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }

    for (int i = 1; i < argc; ++i) {
        FILE *fp = fopen(argv[i], "rb");
        if (!fp) {
            printf("wunzip: cannot open file\n");
            exit(1);
        }

        char buf[2];
        int count;
        while (fread(&count, sizeof(int), 1, fp)) {
            fread(buf, sizeof(unsigned char), 1, fp);

            if (!buf[0] || buf[0] == '\0') {
                continue;
            }

            char ch = buf[0];
            for (int j = 0; j < count; ++j) {
                printf("%c", ch);
            }
        }

        fclose(fp);
    }
}
