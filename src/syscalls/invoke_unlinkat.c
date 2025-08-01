// src/syscalls/invoke_unlinkat.c
#define _GNU_SOURCE
#include "../utils/logger.h"
#include <fcntl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

void invoke_unlinkat_syscall(void) {
    const char *name = "unlinkat";
    const char *path = "tmp_unlinkat.txt";

    log_request(name);

    log_step("SYS_open (O_CREAT|O_WRONLY)");
    int fd = syscall(SYS_open, path, O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        log_error(name, "open");
    }
    if (syscall(SYS_close, fd) < 0) {
        log_error(name, "close");
    }

    log_step("SYS_unlinkat");
    if (syscall(SYS_unlinkat, AT_FDCWD, path, 0) < 0) {
        log_error(name, "unlinkat");
    }

    log_success(name);
}
