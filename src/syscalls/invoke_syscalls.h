// src/syscalls/invoke_syscalls.h
#pragma once
#include <fcntl.h>

int invoke_open_syscall(const char *path, int flags, mode_t mode);
