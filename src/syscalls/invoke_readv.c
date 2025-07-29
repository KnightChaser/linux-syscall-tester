// src/syscalls/invoke_readv.c
#define _GNU_SOURCE
#include "../utils/logger.h"
#include "invoke_syscalls.h"
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

void invoke_readv_syscall(void) {
    const char *name = "readv";
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

    // NOTE: readv() syscall is used to read data into multiple buffers at once.
    // In this example, we read the contents of a file into two buffers
    // (iovec[0] and iovec[1]) using the same readv syscall.
    log_step("SYS_readv");
    char buf1[256], buf2[256];
    struct iovec iov[2] = {{.iov_base = buf1, .iov_len = sizeof(buf1)},
                           {.iov_base = buf2, .iov_len = sizeof(buf2)}};
    ssize_t n = syscall(SYS_readv, fd, iov, 2);
    if (n < 0) {
        log_error(name, "readv");
    }
    log_info(name, "Read %zd bytes into 2 buffers from %s", n, path);

    log_step("SYS_close");
    if (syscall(SYS_close, fd) < 0) {
        log_error(name, "close");
    }

    log_success(name);
}
