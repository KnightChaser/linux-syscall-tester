# src/meson.build

utils_soruce = files('utils/logger.c')
dispatch_sources = files('./dispatch.c')
syscall_sources = files(
  'syscalls/invoke_close.c',
  'syscalls/invoke_dup.c',
  'syscalls/invoke_fcntl.c',
  'syscalls/invoke_open.c',
  'syscalls/invoke_pread.c',
  'syscalls/invoke_read.c',
)

exe = executable(
  'LinuxSyscallTester',
  ['main.c'] + dispatch_sources + utils_soruce + syscall_sources,
  install: true,
)
