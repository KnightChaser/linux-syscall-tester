// src/syscalls/invoke_open.c
#define _GNU_SOURCE
#include <fcntl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

int invoke_open_syscall(const char *path, int flags, mode_t mode) {
    return syscall(SYS_open, path, flags, mode);
}
