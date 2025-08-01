# src/meson.build

utils_soruce = files('utils/logger.c')
dispatch_sources = files('./dispatch.c')
syscall_sources = files(
  'syscalls/invoke_close.c',
  'syscalls/invoke_dup.c',
  'syscalls/invoke_fcntl.c',
  'syscalls/invoke_mkdir.c',
  'syscalls/invoke_mkdirat.c',
  'syscalls/invoke_open.c',
  'syscalls/invoke_pread64.c',
  'syscalls/invoke_preadv.c',
  'syscalls/invoke_pwrite64.c',
  'syscalls/invoke_pwritev.c',
  'syscalls/invoke_read.c',
  'syscalls/invoke_readv.c',
  'syscalls/invoke_write.c',
  'syscalls/invoke_writev.c',
)

exe = executable(
  'LinuxSyscallTester',
  ['main.c'] + dispatch_sources + utils_soruce + syscall_sources,
  install: true,
)
