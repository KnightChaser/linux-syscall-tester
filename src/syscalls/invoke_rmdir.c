// src/syscalls/invoke_rmdir.c
#define _GNU_SOURCE
#include "../utils/logger.h"
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

void invoke_rmdir_syscall(void) {
    const char *name = "rmdir";
    const char *path = "rmtestdir";
    mode_t mode = 0755;

    // first create the directory for removal
    if (syscall(SYS_mkdir, path, mode) < 0) {
        log_error(name, "mkdir (setup)");
    }

    log_request(name);

    log_step("SYS_rmdir");
    if (syscall(SYS_rmdir, path) < 0) {
        log_error(name, "rmdir");
    }

    log_success(name);
}
