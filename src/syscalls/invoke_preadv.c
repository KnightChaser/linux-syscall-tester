// src/syscalls/invoke_preadv.c
#define _GNU_SOURCE
#include "../utils/logger.h"
#include <fcntl.h>
#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

void invoke_preadv_syscall(void) {
    const char *name = "preadv";
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

    log_step("SYS_preadv");
    char buf1[256], buf2[256];
    // NOTE: refer to invoke_readv.c for explanation
    struct iovec iov[2] = {{.iov_base = buf1, .iov_len = sizeof(buf1)},
                           {.iov_base = buf2, .iov_len = sizeof(buf2)}};
    off_t offset = 0;
    ssize_t n = syscall(SYS_preadv, fd, iov, 2, offset);
    if (n < 0) {
        log_error(name, "preadv");
    }

    log_info(name, "Read %zd bytes into 2 buffers from %s at offset %jd", n,
             path, (intmax_t)offset);

    log_step("SYS_close");
    if (syscall(SYS_close, fd) < 0) {
        log_error(name, "close");
    }

    log_success(name);
}
