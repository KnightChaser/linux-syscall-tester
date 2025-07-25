// src/dispatch.c
#include "dispatch.h"
#include "syscalls/invoke_syscalls.h"
#include "utils/logger.h"
#include <stdio.h>
#include <string.h>

// signature for all invoke_*.c modules
typedef void (*invoke_fn)(void);

typedef struct {
    const char *name;
    invoke_fn fn;
} syscall_entry;

// Table of syscall names and their corresponding invoke functions
// Expand this if more syscalls are added! >_<
static const syscall_entry table[] = {{"open", invoke_open_syscall},
                                      /* { "unlink", invoke_unlink_syscall }, */
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
