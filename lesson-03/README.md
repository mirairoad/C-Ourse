# Lesson 03: Integer Types and Overflow

## 1. What is overflow?

- Every C number type has a minimum and a maximum value.
- Overflow happens when a calculation goes outside that range.
- Unsigned integers wrap around using modulo arithmetic.
- Signed integer overflow is undefined behavior.
- A conversion can also change a value when the destination type cannot hold it.

## 2. Limits used in this lesson

- These are the common limits on this system.
- `char`: usually `-128` to `127` when it is signed.
- `unsigned char`: `0` to `255`.
- `short`: `-32,768` to `32,767`.
- `unsigned int`: `0` to `4,294,967,295`.
- `signed int`: `-2,147,483,648` to `2,147,483,647`.
- `float`: about `-3.4 × 10^38` to `3.4 × 10^38`.
- Exact integer limits are available from `<limits.h>`.
- Exact floating-point limits are available from `<float.h>`.

## 3. Global variables

### `unsigned int a = 0;`

1. `a` starts at `0`.
2. It cannot represent a negative number.
3. Its common range is `0` to `4,294,967,295`.
4. Going one above its maximum wraps back to `0`.

### `signed int b = 0;`

1. `b` starts at `0`.
2. It can hold negative, zero, and positive values.
3. Its common range is `-2,147,483,648` to `2,147,483,647`.
4. Going outside that range causes undefined behavior.

### `float c = 1.235;`

1. `c` stores a floating-point number.
2. A `float` has limited precision.
3. The stored value may be a close approximation of `1.235`.
4. This value is far inside the valid `float` range.

### `short d = 5000;`

1. `d` stores `5000`.
2. Its common range is `-32,768` to `32,767`.
3. `5000` is valid and does not overflow.
4. `d` is not used later in this program.

### `char e = 128;`

1. A signed 8-bit `char` can hold only `-128` to `127`.
2. `128` is one above `127`.
3. On this system, the conversion produces `-128`.
4. Plain `char` may be signed or unsigned on a different system.
5. The result of this out-of-range conversion is implementation-defined.

### `unsigned char f = 256;`

1. An 8-bit `unsigned char` can hold `0` to `255`.
2. `256` is one above `255`.
3. Unsigned conversion uses modulo `256` here.
4. `256 % 256` is `0`, so `f` stores `0`.

## 4. The `incr` function

### `void incr(int n)`

1. The function receives one `int` named `n`.
2. It does not return a value.

### `a = n + 1;`

1. Add `1` to `n`.
2. Store the result in the global unsigned integer `a`.
3. The four calls store `1`, `2`, `3`, and `4`.
4. These values do not overflow.

### `printf("%d\n", a);`

1. This prints the new value of `a`.
2. `%d` expects a signed `int`.
3. `a` is an `unsigned int`, so `%u` is the correct format.

## 5. The `decr` function

### `void decr(int n)`

1. The function receives one `int` named `n`.
2. It does not return a value.

### `b = n - 1;`

1. Subtract `1` from `n`.
2. Store the result in the global signed integer `b`.
3. The four calls store `-1`, `-2`, `-3`, and `-4`.
4. These values do not overflow.
5. Subtracting from `INT_MIN` would cause signed integer overflow.

### `printf("%d\n", b);`

1. `%d` prints a signed `int`.
2. This is the correct format for `b`.

## 6. Steps in `main`

1. Call `incr(a)` four times.
2. Print `1`, `2`, `3`, and `4`.
3. Call `decr(b)` four times.
4. Print `-1`, `-2`, `-3`, and `-4`.
5. Print `c` as `1.235000` with `%f`.
6. Print `e` as `-128` on this system.
7. Print `f` as `0`.
8. Return `0` to report success.

## 7. Program output on this system

```text
1
2
3
4
-1
-2
-3
-4
1.235000
-128
0
```

## 8. Main ideas

- The current additions and subtractions do not overflow.
- The values assigned to `e` and `f` do not fit their common 8-bit ranges.
- Unsigned values wrap in a defined way.
- Signed overflow must be avoided.
- Type sizes can differ between systems.
- Use the correct `printf` format for each type.
