# src/meson.build

utils_soruce = files('utils/logger.c')
syscall_sources = files('syscalls/invoke_open.c')

exe = executable(
  'LinuxSyscallTester',
  ['main.c'] + syscall_sources + utils_soruce,
  install: true,
)
