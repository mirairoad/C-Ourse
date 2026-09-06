# Lesson 02: Functions, the Stack, and the Heap

## 1. Goal

1. Declare local variables.
2. Pass values to a function.
3. Return a value from a function.
4. Understand what a function call needs in memory.
5. Learn the job of the stack pointer.
6. Compare automatic stack storage with dynamic heap allocation.

## 2. Memory used by a running program

| Area | Common contents | Managed by | Lifetime |
|---|---|---|---|
| Code | Compiled instructions | Operating system | Entire program |
| Static data | Global and `static` variables | Program/runtime | Entire program |
| Stack | Function calls and local variables | Compiler/runtime | Until a function returns |
| Heap | Dynamically allocated objects | Programmer | Until `free` is called |

## 3. The `sum` function

### `int sum(int a, int b)`

1. `sum` is the function name.
2. The first `int` is the return type.
3. The function receives two integer parameters.
4. The parameters are named `a` and `b`.
5. These parameter names are separate from the `a` and `b` in `main`.

### `return a + b;`

1. Read the two parameter values.
2. Add them together.
3. Return the result to the caller.
4. For `sum(10, 10)`, the result is `20`.

## 4. What happens during a function call?

For this expression:

```c
sum(10, 10)
```

| Step | Action |
|---:|---|
| 1 | `main` prepares the argument values `10` and `10`. |
| 2 | The CPU transfers control to `sum`. |
| 3 | The return address records where execution must continue. |
| 4 | `sum` adds its parameters and produces `20`. |
| 5 | Control returns to `main`. |
| 6 | `printf` receives `20` as its first `%d` value. |

On common 64-bit systems, the first arguments are usually passed in CPU
registers. A compiler may still use the stack when it needs more storage.

## 5. The stack pointer

| Term | Meaning |
|---|---|
| Stack | Memory used to support active function calls. |
| Stack pointer | A CPU register that marks the current top of the stack. |
| Stack frame | The stack space used by one active function call. |
| Return address | The instruction address where execution continues afterward. |

On x86-64, the stack pointer register is named `rsp`.

### Why is a stack pointer needed?

1. Many functions can be active at the same time.
2. Each call may need its own temporary storage.
3. The stack pointer helps locate the current call's stack data.
4. A function can reserve stack space when it begins.
5. It releases that space before it returns.
6. This last-in, first-out order supports nested function calls.

### Simplified call stack during `sum`

| Top of stack | Active call | Possible data |
|---|---|---|
| Newest | `sum` | Return information and temporary values |
| Older | `main` | Local variables `a`, `b`, and `c` |

After `sum` returns, its stack frame is no longer active.

The exact stack layout is not guaranteed by C:

- The compiler chooses the real layout.
- Arguments may remain in registers.
- Local variables may remain in registers.
- An optimized `sum` may need no separate stack frame.

## 6. Local variables in `main`

| Source | Meaning | State before printing |
|---|---|---|
| `int a = 5;` | Declare and initialize `a`. | Safely contains `5`. |
| `int b, c;` | Declare `b` and `c` without values. | Both are indeterminate. |
| `b = 8;` | Assign a value to `b`. | `b` safely contains `8`. |
| `c` | No assignment is made. | Reading it is undefined behavior. |

Local variables commonly use stack storage, but the compiler may keep them in
registers instead.

## 7. The `printf` calls

### `printf("Hello world %d %d\n", sum(10, 10), 199);`

1. Call `sum(10, 10)`.
2. `sum` returns `20`.
3. The first `%d` prints `20`.
4. The second `%d` prints `199`.

Expected line:

```text
Hello world 20 199
```

### `printf("COMBO %d %d\n", a, b);`

1. The first `%d` prints `a`, which is `5`.
2. The second `%d` prints `b`, which is `8`.

Expected line:

```text
COMBO 5 8
```

### `printf("Unassigned %d\n", c);`

1. `c` was declared but never initialized.
2. Reading `c` causes undefined behavior.
3. The program may print any value.
4. The output is not reliable.
5. Initialize it, for example with `int c = 0;`, before reading it.

## 8. Stack versus heap

| Question | Stack/local storage | Heap/dynamic storage |
|---|---|---|
| How is it created? | Declare a local variable. | Call `malloc`, `calloc`, or `realloc`. |
| Who manages it? | Compiler/runtime. | Programmer. |
| When does it end? | When its block or function ends. | When the programmer calls `free`. |
| Typical speed | Very fast to reserve and release. | More management overhead. |
| Typical use | Small local values and temporary data. | Data with dynamic size or longer lifetime. |
| Main danger | Large use can overflow the stack. | Leaks, use-after-free, or invalid access. |

The variables in `functions.c` do not use explicit heap allocation.

## 9. How heap allocation works

Include the required header:

```c
#include <stdlib.h>
```

Allocate space for one integer:

```c
int *number = malloc(sizeof *number);
```

| Part | Meaning |
|---|---|
| `int *number` | A pointer that can hold the address of an integer. |
| `sizeof *number` | The number of bytes needed for one integer. |
| `malloc(...)` | Request that many bytes from the heap. |
| Return value | Address of the allocation, or `NULL` on failure. |

Always check whether allocation succeeded:

```c
if (number == NULL) {
    return 1;
}
```

Use the allocated integer:

```c
*number = 20;
printf("%d\n", *number);
```

Release it when finished:

```c
free(number);
number = NULL;
```

### Allocation steps

1. `malloc` requests a block of heap memory.
2. The returned pointer itself is a local variable.
3. The pointer may be stored on the stack.
4. The memory it points to is on the heap.
5. Dereference the pointer with `*` to access the heap object.
6. Call `free` exactly once when the object is no longer needed.
7. Do not dereference the pointer after `free`.

## 10. Allocation functions

| Function | Purpose | Initial contents |
|---|---|---|
| `malloc(bytes)` | Allocate a block of bytes. | Indeterminate |
| `calloc(count, size)` | Allocate space for an array. | All bits zero |
| `realloc(pointer, bytes)` | Resize an existing allocation. | Old data preserved when possible |
| `free(pointer)` | Release an allocation. | The pointer becomes invalid to dereference |

## 11. Common memory mistakes

| Mistake | Problem | Defense |
|---|---|---|
| Uninitialized local variable | Reading an indeterminate value | Initialize every variable before use |
| Missing `NULL` check | Allocation failure may be dereferenced | Check every allocation result |
| Memory leak | Heap memory is never released | Pair successful allocations with `free` |
| Use after free | Code accesses an expired object | Stop using the pointer after `free` |
| Double free | The same allocation is released twice | Define clear ownership and free once |
| Out-of-bounds access | Code reads or writes outside an object | Track and validate sizes and indexes |

## 12. Compile with warnings

```bash
gcc -std=c17 -Wall -Wextra -Wpedantic functions.c -o functions
```

1. `-Wall` enables many useful warnings.
2. `-Wextra` enables additional warnings.
3. `-Wpedantic` checks stricter ISO C rules.
4. The compiler warns that `c` may be used uninitialized.

## 13. Main ideas

- A function can receive parameters and return a value.
- Each call has its own parameters.
- The stack pointer helps manage active function calls.
- Stack frames and local-variable placement are compiler details.
- Heap memory must be checked, used within bounds, and freed.
- The stack and heap have different lifetimes.
- Never read an uninitialized variable.
