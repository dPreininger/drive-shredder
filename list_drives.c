#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int starts_with(char *str, char *prefix) {
    if(strncmp(str, prefix, strlen(prefix)) == 0)
        return 1;
    return 0;
}

int print_formatted(char *str) {
    char* device = strtok(str, " ");
    char* mount_point = strtok(NULL, " ");
    char* fs_type = strtok(NULL, " ");

    printf("File system type: %s\nDevice: %s\nMounted on: %s\n\n", fs_type, device, mount_point);
}

void read_file(char *filename) {
    FILE* fp = fopen(filename, "r");
    if(fp == NULL) {
        fprintf(stderr, "Error opening file.\n");
        exit(EXIT_FAILURE);
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    while((read = getline(&line, &len, fp)) != -1) {
        if(starts_with(line, "/dev/"))
            print_formatted(line);
    }

    fclose(fp);
    if(line)
        free(line);
}

int main() {
    read_file("/proc/mounts");
    return EXIT_SUCCESS;
}