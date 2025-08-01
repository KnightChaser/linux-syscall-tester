// src/syscalls/invoke_mkdirat.c
#define _GNU_SOURCE
#include "../utils/logger.h"
#include "invoke_syscalls.h"
#include <fcntl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

void invoke_mkdirat_syscall(void) {
    const char *name = "mkdirat";
    const char *path = "testdir_at";
    mode_t mode = 0755;

    log_request(name);

    log_step("SYS_mkdirat");
    if (syscall(SYS_mkdirat, AT_FDCWD, path, mode) < 0) {
        log_error(name, "mkdirat");
    }

    // cleanup
    log_step("SYS_rmdir");
    if (syscall(SYS_rmdir, path) < 0) {
        log_error(name, "rmdir");
    }

    log_success(name);
}
