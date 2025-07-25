// src/main.c
#include "dispatch.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

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
    char *name = NULL;
    struct option opts[] = {{"syscall", required_argument, NULL, 's'},
                            {NULL, 0, NULL, 0}};

    while ((c = getopt_long(argc, argv, "s:", opts, NULL)) != -1) {
        if (c == 's') {
            name = optarg;
        } else {
            usage(argv[0]);
        }
    }

    if (!name) {
        usage(argv[0]);
    }

    int result = dispatch_syscall(name);
    return result == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
