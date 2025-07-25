// src/syscalls/invoke_dup.c
#define _GNU_SOURCE
#include "../utils/logger.h"
#include "invoke_syscalls.h"
#include <fcntl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * Invokes the raw dup syscall to duplicate a file descriptor.
 *
 * This function demonstrates how to use the raw syscall interface
 * to duplicate a file descriptor and then close both the original
 * and the duplicated file descriptors.
 */
void invoke_dup_syscall(void) {
    const char *name = "dup";
    const char *path = "testfile.txt";
    int flags = O_CREAT | O_RDWR;
    mode_t mode = 0644;
    log_request(name);

    log_step("SYS_open");
    int fd = syscall(SYS_open, path, flags, mode);
    if (fd < 0) {
        log_error(name, "open");
    }

    log_step("SYS_dup");
    int newfd = syscall(SYS_dup, fd);
    if (newfd < 0) {
        log_error(name, "dup");
    }

    log_step("SYS_close original");
    if (syscall(SYS_close, fd) < 0) {
        log_error(name, "close(orig)");
    }

    log_step("SYS_close dup");
    if (syscall(SYS_close, newfd) < 0) {
        log_error(name, "close(dup)");
    }

    log_step("SYS_unlink");
    if (syscall(SYS_unlink, path) < 0) {
        log_error(name, "unlink");
    }

    log_success(name);
}
