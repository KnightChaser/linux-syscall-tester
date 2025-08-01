// src/syscalls/invoke_link.c
#define _GNU_SOURCE
#include "../utils/logger.h"
#include "invoke_syscalls.h"
#include <fcntl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

void invoke_link_syscall(void) {
    const char *name = "link";
    const char *orig = "orig.txt";
    const char *alias = "alias.txt";

    // create the original file
    log_request(name);
    log_step("SYS_open (O_CREAT|O_WRONLY)");
    int fd = syscall(SYS_open, orig, O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        log_error(name, "open(orig)");
    }
    if (syscall(SYS_close, fd) < 0) {
        log_error(name, "close(orig)");
    }

    // perform link()
    log_step("SYS_link");
    if (syscall(SYS_link, orig, alias) < 0) {
        log_error(name, "link");
    }

    // clean up both paths
    log_step("SYS_unlink alias");
    if (syscall(SYS_unlink, alias) < 0) {
        log_error(name, "unlink(alias)");
    }
    log_step("SYS_unlink orig");
    if (syscall(SYS_unlink, orig) < 0) {
        log_error(name, "unlink(orig)");
    }

    log_success(name);
}
