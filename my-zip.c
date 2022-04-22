#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
    FILE* file;
    size_t len = 0;
    char *line = NULL;
    int h, i, line_len, ascii;

    unsigned char bytes[5];
    unsigned long int occur;
    
    if (argc == 1) {
        printf("my-zip: file1 [file2 ...]\n");
        exit(1);
    } else {
        for(h=1;h!=argc;h++) {
            if((file = fopen(argv[h], "r")) == NULL) {
                perror("File opening failed");
                exit(1);
            }

            while ((getline(&line, &len, file)) != -1) {
                line_len = strlen(line);
                for(i=0;i<line_len;i++) {
                    occur = 1;

                    // counting how many times the same character occurs
                    while(i+1<line_len && line[i] == line[i+1]) {
                        occur++;
                        i++;
                    }

                    // putting the number to first 4 bits and ascii to 5th bit.
                    bytes[0] = (occur >> 24) & 0xFF;
                    bytes[1] = (occur >> 16) & 0xFF;
                    bytes[2] = (occur >> 8) & 0xFF;
                    bytes[3] = (occur >> 0) & 0xFF;
                    ascii = line[i];
                    bytes[4] = (ascii >> 0) & 0xFF;

                    fwrite(bytes, sizeof(unsigned char), sizeof(bytes), stdout);
                }

            }
            fclose(file);
        }
    }
    return 0;
}