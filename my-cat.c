#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *file;
    char buffer[256];
    int i;

    if (argc == 1) {
        printf("No files specified.\n");
        exit(0);
    }

    for (i=1;i!=argc;i++) {
        if((file = fopen(argv[i], "r")) == NULL) {
            perror("my-cat: cannot open file\n");
            exit(1);
        }

        while (fgets(buffer, 254, file) != NULL) {
            printf("%s", buffer);
        }
        fclose(file);
    }

    return 0;
}