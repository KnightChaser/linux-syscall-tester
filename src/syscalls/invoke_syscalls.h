// src/syscalls/invoke_syscalls.h
#pragma once
#include <fcntl.h>

void invoke_close_syscall(void);
void invoke_dup_syscall(void);
void invoke_fcntl_syscall(void);
void invoke_open_syscall(void);
void invoke_read_syscall(void);
void invoke_pread64_syscall(void);
