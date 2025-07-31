// src/dispatch.c
#include "dispatch.h"
#include "syscalls/invoke_syscalls.h"
#include "utils/logger.h"
#include <string.h>

// signature for all invoke_*.c modules
typedef void (*invoke_fn)(void);

typedef struct {
    const char *name;
    invoke_fn fn;
} syscall_entry;

// Table of syscall names and their corresponding invoke functions
// Expand this if more syscalls are added! >_<
static const syscall_entry table[] = {{"close", invoke_close_syscall},
                                      {"dup", invoke_dup_syscall},
                                      {"fcntl", invoke_fcntl_syscall},
                                      {"open", invoke_open_syscall},
                                      {"pread64", invoke_pread64_syscall},
                                      {"preadv", invoke_preadv_syscall},
                                      {"pwrite64", invoke_pwrite64_syscall},
                                      {"read", invoke_read_syscall},
                                      {"readv", invoke_readv_syscall},
                                      {"write", invoke_write_syscall},
                                      {NULL, NULL}};

/**
 * Dispatches a syscall by name.
 *
 * @param name The name of the syscall to dispatch.
 * @return 0 on success, -1 if the syscall is not found.
 */
int dispatch_syscall(const char *name) {
    for (const syscall_entry *e = table; e->name; ++e) {
        if (strcmp(e->name, name) == 0) {
            e->fn();
            return 0;
        }
    }
    log_error(name, "unsupported syscall");
    return -1;
}
