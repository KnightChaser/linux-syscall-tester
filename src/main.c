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

    // Parse command line options
    while ((c = getopt_long(argc, argv, "s:", longopts, NULL)) != -1) {
        if (c == 's')
            syscall_name = optarg;
        else
            usage(argv[0]);
    }
    if (!syscall_name)
        usage(argv[0]);

    // Dispatch to the appropriate syscall function based on the name
    if (strcmp(syscall_name, "open") == 0) {
        invoke_open_syscall();
    } else {
        fprintf(stderr, "Error: unsupported syscall '%s'\n", syscall_name);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
