#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void overwrite(char* device, u_int8_t data) {
    int fd = open(device, O_WRONLY);
    if (fd < 0) {
        fprintf(stderr, "Error opening device file.\n");
        exit(EXIT_FAILURE);
    }

    // Fill chunk with data
    u_int8_t* chunk = malloc(512);
    for (int i = 0; i < 512; i++)
        chunk[i] = data;

    // Write chunk to device until full
    ssize_t written, total = 0;
    do {
        total += written = write(fd, chunk, 512);
    } while (written == 512);

    printf("Overwrote %ld bytes (%ld chunks) with charcter %c.\n", total, total / 512, data);

    close(fd);
    free(chunk);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <device mount point>\n", argv[0]);
        return EXIT_FAILURE;
    }

    overwrite(argv[1], 0x00);
    overwrite(argv[1], 0xFF);
    printf("Done.\n");
    return EXIT_SUCCESS;
}