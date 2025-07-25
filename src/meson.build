# src/meson.build

utils_soruce = files('utils/logger.c')
dispatch_sources = files('./dispatch.c')
syscall_sources = files(
  'syscalls/invoke_close.c',
  'syscalls/invoke_open.c',
)

exe = executable(
  'LinuxSyscallTester',
  ['main.c'] + syscall_sources + dispatch_sources + utils_soruce,
  install: true,
)
