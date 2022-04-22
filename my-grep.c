#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *file;
    size_t len = 0;
    char *line = NULL;
    int i;
    
    if (argc == 1) {
        printf("my-grep: searchterm [file ...]\n");
        exit(1);
    } else if (argc == 2) {
        while (getline(&line, &len, stdin) != -1) {
            if (strstr(line, argv[1]) != NULL) {
                printf("%s", line);
            }
        }
    } else {
        for (i=2;i!=argc;i++) {

            if ((file = fopen(argv[i], "r")) == NULL) {
                printf("my-grep: cannot open file\n");
                exit(1);
            }

            while ((getline(&line, &len, file)) != -1) {
                if (strstr(line, argv[1]) != NULL) {
                    printf("%s", line);
                }
            }
            fclose(file);
        }
        free(line);
    }

    return 0;
}