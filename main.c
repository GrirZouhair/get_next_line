// main.c
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main()
{
    int fd;
    char *line;

    // Open the test file
    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("Failed to open file");
        return 1;
    }

    // Read lines and print them
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);  // Print the line
        free(line);  // Free the memory after printing
    }

    // Close the file
    close(fd);

    return 0;
}
