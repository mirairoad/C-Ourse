# Lesson 01: Hello World

## 1. Goal

1. Write a small C program.
2. Compile the source code into an executable program.
3. Run the executable.
4. Ask GCC to show the generated assembly.
5. Learn what each line of the C program does.

## 2. The source file

The source code is in `hello-world.c`.

### `#include <stdio.h>`

1. `#include` asks the preprocessor to include a header file.
2. `stdio.h` means standard input/output header.
3. It declares the `printf` function used below.

### `int main()`

1. `main` is the program's entry point.
2. Execution begins here.
3. `int` means `main` returns an integer to the operating system.
4. Writing `int main(void)` states clearly that the function takes no arguments.
5. The opening `{` starts the function body.

### `printf("Hello world\n");`

1. `printf` writes formatted text to standard output.
2. `"Hello world\n"` is a string literal.
3. `\n` adds a newline after the words.
4. The semicolon ends the statement.
5. This line displays `Hello world` in the terminal.

### `return 0;`

1. Stop running `main`.
2. Return status code `0` to the operating system.
3. Status `0` normally means success.

### `}`

1. The closing brace ends the `main` function.

## 3. Compile the program

Run this command inside the `lesson-01` directory:

```bash
gcc hello-world.c -o hello-world
```

1. `gcc` starts the GNU C compiler.
2. `hello-world.c` is the input source file.
3. `-o hello-world` names the output executable `hello-world`.

## 4. Run the program

```bash
./hello-world
```

Expected output:

```text
Hello world
```

1. `./` means to look in the current directory.
2. `hello-world` is the executable created by GCC.

## 5. Generate assembly

Generate assembly without optimization:

```bash
gcc -O0 -S hello-world.c -o hello-world.s
```

Generate assembly with level 2 optimization:

```bash
gcc -O2 -S hello-world.c -o hello-world-02.s
```

1. `-S` tells GCC to stop after generating assembly.
2. Uppercase `-O` selects an optimization level.
3. `-O0` disables optimization.
4. `-O2` enables a useful set of optimizations.
5. The `.s` files contain assembly text, not executable programs.

## 6. Important assembly lines

### `.string "Hello world"`

1. Store the program's text in a read-only data section.
2. `.LC0` is the label used to find that text.

### `.globl main`

1. Make the `main` symbol visible to the linker.

### `main:`

1. Mark the beginning of the machine instructions for `main`.

### `leaq .LC0(%rip), %rax`

1. Find the address of the `Hello world` string.
2. Store that address in the `rax` register.

### `movq %rax, %rdi`

1. Copy the string address into the `rdi` register.
2. On this system, `rdi` carries the first function argument.

### `call puts@PLT`

1. Call the C library function `puts`.
2. GCC can replace this simple `printf` call with `puts`.
3. `puts` prints the string and adds a newline.

### `movl $0, %eax`

1. Put `0` in the register used for the return value.
2. This matches `return 0;` in the C source.

### `ret`

1. Return control to the code that started `main`.

## 7. GCC optimization levels

- `-O0`: no optimization; useful for direct debugging.
- `-O1`: basic optimization.
- `-O2`: stronger optimization suitable for many programs.
- `-O3`: aggressive optimization that may create larger code.
- `-Os`: optimize for a smaller binary.
- `-Og`: optimize while keeping debugging practical.
- `-Ofast`: aggressive optimization that may relax some guarantees.

## 8. Read the manual

```bash
man 3 printf
```

1. `man` opens the system manual.
2. Section `3` contains C library function documentation.
3. `printf` selects the page for the `printf` function.
4. Press `q` to close the manual.

## 9. Main ideas

- C execution begins in `main`.
- Header files provide function declarations.
- Statements normally end with a semicolon.
- `printf` writes text to standard output.
- `return 0` reports successful completion.
- GCC turns C source into an executable or assembly output.
