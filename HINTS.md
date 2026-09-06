# C Pro Tips

## Compiling

Compile one C source file:

```bash
gcc hello-world.c -o hello-world
```

> **Pro tip:** Always use `-o` to give the executable a useful name.

Compile with helpful warnings:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic hello-world.c -o hello-world
```

| Option | Purpose |
|---|---|
| `-std=c17` | Use the C17 language standard. |
| `-Wall` | Enable many common warnings. |
| `-Wextra` | Enable additional warnings. |
| `-Wpedantic` | Warn about code outside strict ISO C. |
| `-o name` | Set the output filename. |

> **Pro tip:** Treat warnings as problems to understand, even when GCC still
> creates the executable.

## Running Programs

Run an executable from the current directory:

```bash
./hello-world
```

Run a program and print its exit status:

```bash
./hello-world; echo $?
```

| Exit status | Common meaning |
|---:|---|
| `0` | Success |
| Nonzero | An error or another special result |

> **Pro tip:** `$?` contains the exit status of the most recently completed
> command.

## Shell Short-Circuiting

Run the second command only if the program succeeds:

```bash
./hello-world && ls
```

Run the second command only if the program fails:

```bash
./hello-world || echo "The program failed"
```

| Operator | Behavior |
|---|---|
| `;` | Run the next command regardless of success. |
| `&&` | Run the next command only after success. |
| `||` | Run the next command only after failure. |

> **Pro tip:** Use `&&` after compilation so an old executable is not run when
> the new compilation fails.

```bash
gcc -Wall -Wextra program.c -o program && ./program
```

## Optimization

| Level | Purpose |
|---|---|
| `-O0` | Disable optimization; straightforward for debugging. |
| `-O1` | Enable basic optimization. |
| `-O2` | Enable stronger, widely used optimization. |
| `-O3` | Enable aggressive optimization; code may become larger. |
| `-Os` | Optimize for a smaller binary. |
| `-Og` | Optimize while keeping debugging practical. |
| `-Ofast` | Enable aggressive changes that may relax some guarantees. |

> **Pro tip:** Optimization uses an uppercase letter `O`, not the number zero.
> Start with `-O0` or `-Og` while debugging.

## Generating Assembly

Generate unoptimized assembly:

```bash
gcc -O0 -S hello-world.c -o hello-world.s
```

Generate optimized assembly:

```bash
gcc -O2 -S hello-world.c -o hello-world-O2.s
```

| Option | Purpose |
|---|---|
| `-S` | Stop compilation after producing assembly. |
| `-O0` | Disable optimization. |
| `-O2` | Enable level 2 optimization. |

> **Pro tip:** Compare the two `.s` files to see how optimization changes the
> generated instructions. Assembly files are ignored by this repository.

## Debug Information

Compile with debugging symbols:

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic -g program.c -o program
```

Start the GNU debugger:

```bash
gdb ./program
```

| GDB command | Purpose |
|---|---|
| `break main` | Stop when `main` begins. |
| `run` | Start the program. |
| `next` | Execute the next source line. |
| `print variable` | Display a variable's value. |
| `backtrace` | Show the active function calls. |
| `quit` | Leave GDB. |

> **Pro tip:** Use `-g` with `-O0` or `-Og` when learning to debug.

## Finding Memory Errors

Compile with AddressSanitizer and UndefinedBehaviorSanitizer:

```bash
gcc -std=c17 -Wall -Wextra -g \
  -fsanitize=address,undefined program.c -o program
```

Run the instrumented executable normally:

```bash
./program
```

Sanitizers can help detect:

- Out-of-bounds memory access
- Use after free
- Some memory leaks
- Signed integer overflow
- Other undefined behavior

> **Pro tip:** A sanitizer report points near the bug, but you still need to
> understand why the invalid operation happened.

## Reading Manual Pages

Open the C library manual page for `printf`:

```bash
man 3 printf
```

| Manual section | Contents |
|---:|---|
| `1` | Shell commands and programs |
| `2` | Linux system calls |
| `3` | C library functions |

Useful keys inside `man`:

| Key | Action |
|---|---|
| `/word` | Search for `word`. |
| `n` | Open the next search result. |
| `q` | Quit. |

> **Pro tip:** Read the `SYNOPSIS`, return value, and error sections before
> using an unfamiliar function.

## Formatting and Readability

- Use consistent indentation.
- Give variables names that explain their purpose.
- Put spaces around operators: `a + b`.
- Initialize variables before reading them.
- Keep functions focused on one job.
- Comment why something is done, not only what the syntax says.

> **Pro tip:** Compile frequently. Small changes produce smaller, clearer error
> messages.

## Cleaning Generated Files

Remove a named executable when it is no longer needed:

```bash
rm ./hello-world
```

> **Pro tip:** Check the filename before removing anything. Source files use
> `.c`; generated assembly files use `.s`; executables may have no extension.
