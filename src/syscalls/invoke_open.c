// src/syscalls/invoke_open.c
#define _GNU_SOURCE
#include "../utils/logger.h"
#include <fcntl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * Invokes the raw open syscall to create a file.
 *
 * This function demonstrates how to use the raw syscall interface
 * to open a file with specific flags and mode.
 */
void invoke_open_syscall(void) {
    const char *name = "open";
    const char *path = "testfile.txt";
    int flags = O_CREAT | O_WRONLY;
    mode_t mode = 0644;
    log_request(name);

    // raw open syscall
    int fd = syscall(SYS_open, path, flags, mode);
    log_step("open");
    if (fd < 0) {
        log_error(name, "open");
    }

    // raw close syscall
    log_step("close");
    if (syscall(SYS_close, fd) < 0) {
        log_error(name, "close");
    }

    // raw unlink syscall
    log_step("unlink");
    if (syscall(SYS_unlink, path) < 0) {
        log_error(name, "unlink");
    }

    log_success(name);
}
