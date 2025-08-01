// src/syscalls/invoke_mkdir.c
#define _GNU_SOURCE
#include "../utils/logger.h"
#include "invoke_syscalls.h"
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

void invoke_mkdir_syscall(void) {
    const char *name = "mkdir";
    const char *path = "testdir";
    mode_t mode = 0755;

    log_request(name);

    log_step("SYS_mkdir");
    if (syscall(SYS_mkdir, path, mode) < 0) {
        log_error(name, "mkdir");
    }

    // cleanup
    log_step("SYS_rmdir");
    if (syscall(SYS_rmdir, path) < 0) {
        log_error(name, "rmdir");
    }

    log_success(name);
}
