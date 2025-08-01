// src/syscalls/invoke_linkat.c
#define _GNU_SOURCE
#include "../utils/logger.h"
#include <fcntl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

void invoke_linkat_syscall(void) {
    const char *name = "linkat";
    const char *orig = "orig_at.txt";
    const char *alias = "alias_at.txt";

    log_request(name);

    // create the original file
    log_step("SYS_open (O_CREAT|O_WRONLY)");
    int fd = syscall(SYS_open, orig, O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        log_error(name, "open(orig_at)");
    }
    if (syscall(SYS_close, fd) < 0) {
        log_error(name, "close(orig_at)");
    }

    // perform linkat()
    log_step("SYS_linkat");
    if (syscall(SYS_linkat, AT_FDCWD, orig, AT_FDCWD, alias, 0) < 0) {
        log_error(name, "linkat");
    }

    // clean up both paths
    log_step("SYS_unlink alias_at");
    if (syscall(SYS_unlink, alias) < 0) {
        log_error(name, "unlink(alias_at)");
    }
    log_step("SYS_unlink orig_at");
    if (syscall(SYS_unlink, orig) < 0) {
        log_error(name, "unlink(orig_at)");
    }

    log_success(name);
}
