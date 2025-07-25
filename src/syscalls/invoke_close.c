// src/syscalls/invoke_close.c
#define _GNU_SOURCE
#include "../utils/logger.h"
#include "invoke_syscalls.h"
#include <fcntl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * Invokes the raw close syscall to close a file.
 *
 * This function demonstrates how to use the raw syscall interface
 * to close a file that was previously opened.
 */
void invoke_close_syscall(void) {
    const char *name = "close";
    const char *path = "testfile.txt";
    int flags = O_CREAT | O_RDWR;
    mode_t mode = 0644;
    log_request(name);

    log_step("SYS_open");
    int fd = syscall(SYS_open, path, flags, mode);
    if (fd < 0) {
        log_error(name, "open");
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
