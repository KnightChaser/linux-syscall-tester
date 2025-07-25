// src/main.c
#include "syscalls/invoke_syscalls.h"
#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * Displays usage information for the program.
 *
 * @param prog The name of the program.
 */
static void usage(const char *prog) {
    fprintf(stderr,
            "Usage: %s -s <syscall>\n"
            "  --syscall, -s  name of syscall to invoke (e.g. open, unlink)\n",
            prog);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
    int c;
    char *syscall_name = NULL;

    struct option longopts[] = {{"syscall", required_argument, NULL, 's'},
                                {NULL, 0, NULL, 0}};

    while ((c = getopt_long(argc, argv, "s:", longopts, NULL)) != -1) {
        switch (c) {
        case 's':
            syscall_name = optarg;
            break;
        default:
            usage(argv[0]);
        }
    }

    if (!syscall_name)
        usage(argv[0]);

    if (strcmp(syscall_name, "open") == 0) {
        const char *path = "testfile.txt";
        int fd = invoke_open_syscall(path, O_CREAT | O_WRONLY, 0644);
        if (fd < 0) {
            perror("open syscall failed");
            return EXIT_FAILURE;
        }
        printf("✅ opened '%s' → fd %d\n", path, fd);
        close(fd);

    } else {
        fprintf(stderr, "Error: unsupported syscall '%s'\n", syscall_name);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
