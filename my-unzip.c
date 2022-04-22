#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    FILE* file;
    struct stat st;
    int i, j;

    if (argc == 1) {
        printf("Not enough argmunets\n");
        exit(0);
    } else {
        if((file = fopen(argv[1], "r")) == NULL) {
            perror("File opening failed");
            exit(1);
        }

        fstat(fileno(file), &st);
        unsigned char buffer[st.st_size];
        fread(&buffer, sizeof(char), st.st_size, file);

        for (i=0;i<st.st_size;i=i+5) {
            // converting the number and character from binary to their respective formats
            int number = (buffer[i]) << 24 | (buffer[i+1]) << 16 | (buffer[i+2]) << 8 | (buffer[i+3]);
            char character = buffer[i+4];

            // printing the result to the stdout
            for (j=0;j<number;j++) {
                printf("%c", character);
            }
        }

        fclose(file);
    }

    return 0;
}