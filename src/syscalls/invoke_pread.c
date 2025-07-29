// src/syscalls/invoke_pread.c
#define _GNU_SOURCE
#include "../utils/logger.h"
#include "invoke_syscalls.h"
#include <fcntl.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

void invoke_pread_syscall(void) {
    const char *name = "pread";
    char path[PATH_MAX];
    const char *home = getenv("HOME");
    if (!home) {
        log_error(name, "HOME not set");
    }
    if (snprintf(path, sizeof(path), "%s/.bashrc", home) >= (int)sizeof(path)) {
        log_error(name, "path too long");
    }

    log_request(name);

    log_step("SYS_open (O_RDONLY)");
    int fd = syscall(SYS_open, path, O_RDONLY, 0);
    if (fd < 0) {
        log_error(name, "open");
    }

    log_step("SYS_pread64");
    char buf[512];
    off_t offset = 0;
    ssize_t n = syscall(SYS_pread64, fd, buf, sizeof(buf), offset);
    if (n < 0) {
        log_error(name, "pread64");
    }
    log_info(name, "Read %zd bytes from %s at offset %jd", n, path,
             (intmax_t)offset);

    log_step("SYS_close");
    if (syscall(SYS_close, fd) < 0) {
        log_error(name, "close");
    }

    log_success(name);
}
