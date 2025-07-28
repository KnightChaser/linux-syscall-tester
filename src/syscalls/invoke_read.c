// src/syscalls/invoke_read.c
#define _GNU_SOURCE
#include "../utils/logger.h"
#include "invoke_syscalls.h"
#include <fcntl.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

void invoke_read_syscall(void) {
    const char *name = "read";
    char path[PATH_MAX];
    const char *home = getenv("HOME");
    if (!home) {
        log_error(name, "$HOME (env) is not set");
    }

    unsigned long path_len = snprintf(path, sizeof(path), "%s/.bashrc", home);
    if (path_len >= sizeof(path)) {
        log_error(name, "snprintf failed or path too long");
    } else if (path_len < 0) {
        log_error(name, "snprintf failed");
    } else {
        log_info(name, "Path to read: %s", path);
    }

    log_request(name);

    log_step("SYS_open (O_RDONLY)");
    int fd = syscall(SYS_open, path, O_RDONLY, 0);
    if (fd < 0) {
        log_error(name, "open");
    }

    log_step("SYS_read");
    char buf[1024];
    ssize_t bytes_read = syscall(SYS_read, fd, buf, sizeof(buf) - 1);
    if (bytes_read < 0) {
        log_error(name, "read");
    } else {
        buf[bytes_read] = '\0'; // Null-terminate the string
        log_info(name, "Read data from file");
    }

    log_step("SYS_close");
    if (syscall(SYS_close, fd) < 0) {
        log_error(name, "close");
    }

    log_success(name);
}
