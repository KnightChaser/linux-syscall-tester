// src/syscalls/invoke_fcntl.c
#define _GNU_SOURCE
#include "../utils/logger.h"
#include "invoke_syscalls.h"
#include <fcntl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * Invokes the raw fcntl syscall to manipulate file descriptors.
 *
 * This function demonstrates how to use the raw syscall interface
 * to open a file, get its flags using F_GETFL, set new flags using
 * F_SETFL, and then close the file descriptor.
 */
void invoke_fcntl_syscall(void) {
    const char *name = "fcntl";
    const char *path = "testfile.txt";
    int flags = O_CREAT | O_RDWR;
    mode_t mode = 0644;
    log_request(name);

    log_step("SYS_open");
    int fd = syscall(SYS_open, path, flags, mode);
    if (fd < 0) {
        log_error(name, "open");
    }

    log_step("SYS_fcntl(F_GETFL)");
    int fl = syscall(SYS_fcntl, fd, F_GETFL, 0);
    if (fl < 0) {
        log_error(name, "fcntl GETFL");
    }

    log_step("SYS_fcntl(F_SETFL)");
    if (syscall(SYS_fcntl, fd, F_SETFL, fl | O_NONBLOCK) < 0) {
        log_error(name, "fcntl SETFL");
    }

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
