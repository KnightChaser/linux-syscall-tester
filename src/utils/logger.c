// src/utils/logger.c
#define _GNU_SOURCE
#include "logger.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

// ANSI color codes for the terminal
#define BOLD "\033[1m"
#define RESET "\033[0m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RED "\033[31m"
#define BLUE "\033[34m"

void log_request(const char *name) {
    printf("[+] Request to execute syscall \"%s\" delivered.\n", name);
}

void log_step(const char *step) {
    printf(YELLOW "[~] Executing %s (En route)\n" RESET, step);
}

void log_info(const char *name, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    printf(BLUE "[*] Syscall \"%s\": " RESET, name);
    vprintf(fmt, ap);
    printf("\n");
    va_end(ap);
}

void log_success(const char *name) {
    printf(GREEN BOLD "[✔] syscall \"%s\" executed successfully.\n" RESET,
           name);
}

void log_error(const char *name, const char *msg) {
    fprintf(stderr, RED "[✘] syscall \"%s\" failed: %s\n" RESET, name, msg);
    exit(EXIT_FAILURE);
}
