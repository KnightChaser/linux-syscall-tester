// invoke_write.c
#define _GNU_SOURCE
#include "../utils/logger.h"
#include "invoke_syscalls.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

void invoke_write_syscall(void) {
    const char *name = "write";
    const char *path = "testfile.txt";
    const char *msg = "Hello, syscalls!\n";
    size_t len = strlen(msg);

    log_request(name);

    log_step("SYS_open (O_CREAT|O_WRONLY)");
    int fd = syscall(SYS_open, path, O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        log_error(name, "open");
    }

    log_step("SYS_write");
    ssize_t n = syscall(SYS_write, fd, msg, len);
    if (n < 0) {
        log_error(name, "write");
    }
    log_info(name, "Wrote %zd bytes to %s", n, path);

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
