# Native x86-64 version

This is a native rewrite of the original Python password generator.

- `password_native.c` is the source used for native compilation.
- `password_text.hex` contains the raw hexadecimal bytes from the compiled executable's `.text` section. Those bytes are x86-64 CPU instructions.
- The downloadable `password_native` executable produced alongside this branch is an x86-64 Linux ELF executable.

Build:

```sh
clang -O2 -s password_native.c -o password_native
```

Extract only the machine-code section:

```sh
llvm-objcopy -O binary --only-section=.text password_native password_text.bin
```

The Python `hash()` function is runtime-salted, so the native rewrite uses FNV-1a for the favorite-number-derived character pool. The original behavior where shirt input is collected but not used in the password pool is preserved.
