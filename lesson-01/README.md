### HOW TO COMPILE
gcc ./hello-world.c o ./hello-world (bin output)
gcc -S ./hello-world.c -o ./hello-world.s (assembly output)
gcc -S 02 ./hello-world.c -o ./hello-world-02.s (assembly output)


-O0 — no optimization; best for straightforward debugging
-O1 — basic optimization
-O2 — strong, generally safe optimization; common production default
-O3 — more aggressive optimization, potentially larger binaries
-Os — optimize for binary size
-Og — optimize while preserving a good debugging experience
-Ofast — very aggressive; may relax language and floating-point guarantees


man 3 printf // man is the manual and 3 stands for C.
