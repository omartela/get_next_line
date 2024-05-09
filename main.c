#include <fcntl.h>
#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h> // for atoi()

int main(int argc, char *argv[]) {
    int fd;
    char *line;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Open the file specified in the command-line argument
    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }

    // Read lines from the file until end of file
    while ((line = get_next_line(fd)) != NULL) {
        printf("tulostaa rivin\n");
        printf("%s\n", line);
        free(line);
    }

    // Close the file
    close(fd);
    return 0;
}
