#define _GNU_SOURCE
#include "../utils/logger.h"
#include "invoke_syscalls.h"
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

void invoke_pwritev_syscall(void) {
    const char *name = "pwritev";
    const char *path = "testfile.txt";
    char part1[] = "Hello, ";
    char part2[] = "pwritev!\n";
    off_t offset = 0;

    log_request(name);

    log_step("SYS_open (O_CREAT|O_WRONLY)");
    int fd = syscall(SYS_open, path, O_CREAT | O_WRONLY, 0644);
    if (fd < 0) {
        log_error(name, "open");
    }

    log_step("SYS_pwritev");
    struct iovec iov[2] = {{.iov_base = part1, .iov_len = sizeof(part1) - 1},
                           {.iov_base = part2, .iov_len = sizeof(part2) - 1}};
    ssize_t n = syscall(SYS_pwritev, fd, iov, 2, offset);
    if (n < 0) {
        log_error(name, "pwritev");
    }
    log_info(name, "Wrote %zd bytes via pwritev at offset %jd to %s", n,
             (intmax_t)offset, path);

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
