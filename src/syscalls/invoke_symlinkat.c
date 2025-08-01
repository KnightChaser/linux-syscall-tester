#define _GNU_SOURCE
#include "../utils/logger.h"
#include <fcntl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * invoke_symlinkat_syscall:
 *   create "orig_at.txt", symlinkat to "symlink_at.txt", then clean both.
 */
void invoke_symlinkat_syscall(void) {
    const char *name = "symlinkat";
    const char *target = "orig_at.txt";
    const char *linkpath = "symlink_at.txt";

    log_request(name);

    log_step("SYS_open (O_CREAT|O_WRONLY)");
    int fd = syscall(SYS_open, target, O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {

        log_error(name, "open(target)");
    }
    if (syscall(SYS_close, fd) < 0) {

        log_error(name, "close(target)");
    }

    log_step("SYS_symlinkat");
    if (syscall(SYS_symlinkat, target, AT_FDCWD, linkpath) < 0) {
        log_error(name, "symlinkat");
    }

    log_step("SYS_unlink linkpath");
    if (syscall(SYS_unlink, linkpath) < 0) {
        log_error(name, "unlink(linkpath)");
    }

    log_step("SYS_unlink target");
    if (syscall(SYS_unlink, target) < 0) {
        log_error(name, "unlink(target)");
    }

    log_success(name);
}
