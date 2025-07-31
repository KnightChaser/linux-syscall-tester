// src/syscalls/invoke_pwrite64.c
#define _GNU_SOURCE
#include "../utils/logger.h"
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

void invoke_pwrite64_syscall(void) {
    const char *name = "pwrite64";
    const char *path = "testfile.txt";
    const char *msg = "Hello, pwrite64!\n";
    size_t len = strlen(msg);
    off_t offset = 0;

    log_request(name);

    log_step("SYS_open (O_CREAT|O_WRONLY)");
    int fd = syscall(SYS_open, path, O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        log_error(name, "open");
    }

    log_step("SYS_pwrite64");
    ssize_t n = syscall(SYS_pwrite64, fd, msg, len, offset);
    if (n < 0) {
        log_error(name, "pwrite64");
    }
    log_info(name, "Wrote %zd bytes at offset %jd to %s", n, (intmax_t)offset,
             path);

    log_step("SYS_close");
    if (syscall(SYS_close, fd) < 0) {
        log_error(name, "close");
    }

    log_step("SYS_unlink");
    if (syscall(SYS_unlink, path) < 0) {
        log_error(name, "unlink");
    }

    log_success(name);
}
