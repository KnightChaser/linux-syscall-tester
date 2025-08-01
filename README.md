# `linux-syscall-tester`

> A lightweight C program to invoke and test Linux system calls via the raw syscall interface, complete with step-by-step logging.

<img width="600" height="400" alt="image" src="https://github.com/user-attachments/assets/75d7d909-0efc-4e63-80f1-f57e86706489" />


## Requirements

* Linux x86\_64
* Meson (C/C++ build system)
* Clang

## Building

```bash
meson setup builddir --native-file=clang.ini
cd builddir
meson compile
```

## Usage

```bash
./LinuxSyscallTester -s <syscall>
```

Replace `<syscall>` with one of the supported names (You can find the full list at `/src/syscalls/*.c`):

* `open`
* `close`
* `dup`
* `fcntl`
* `read`
* ...

## Logging

Each invocation logs its progress using ANSI color codes:

* `[+]` Request start
* `[~]` Syscall execution
* `[*]` Informational messages
* `[✔]` Success (exit 0)
* `[✘]` Error (exit 1)

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.
