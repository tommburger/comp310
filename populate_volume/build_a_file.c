// create_file filename size
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE_LENGTH 100

int main(int argc, char *argv[])
{
    if (argc != 3) {
       fprintf(stderr, "usage: %s filename size\n", argv[0]);
       return 1;
    }

    int size = atoi(argv[2]);
    if (size <= 0) {
        fprintf(stderr, "file size must be positive\n");
        return 2;
    }

    FILE *f = fopen(argv[1], "w");
    if (f == NULL) {
        perror("cannot create specified file");
        return 3;
    }

    char line[LINE_LENGTH];
    memset(line, ' ', sizeof(line));
    line[LINE_LENGTH-1] = '\n';

    int num_full_lines = size / LINE_LENGTH; 
    int remaining = size % LINE_LENGTH;

    for (int ln=0; ln<num_full_lines; ++ln) {
        char prefix[60];
        int prefix_length = snprintf(prefix, sizeof(prefix), 
                 "%5d of %-5d   %.30s  size: %d", 
                 ln, num_full_lines, argv[1], size);
        int written = fwrite(prefix, 1, prefix_length, f);
        if (written != prefix_length) {
            perror("error in writing prefix");
            return 4;
        }
        written = fwrite(&line[prefix_length], 
                         1,
                         LINE_LENGTH - prefix_length, 
                         f);
        if (written != LINE_LENGTH - prefix_length) {
            perror("error in writing rest of line");
            return 5;
        }
    }

    line[LINE_LENGTH - 2] = '<';
    int amt = fwrite(&line[LINE_LENGTH - remaining], 1, remaining, f);
    if (amt != remaining) {
        perror("error in writing remainder");
    }
    fclose(f);
}
