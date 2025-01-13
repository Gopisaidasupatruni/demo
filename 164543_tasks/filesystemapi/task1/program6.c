simpcat1.c - Uses Standard I/O Functions (getchar and putchar):

getchar() reads a character from standard input (stdin), and putchar() writes a character to standard output (stdout).
Standard I/O functions are buffered, meaning they store data in a temporary area before reading or writing it all at once, reducing the number of system calls.


simpcat2.c - Uses System Calls (read and write):

read(0, &c, 1) reads one byte directly from the file descriptor 0 (standard input), and write(1, &c, 1) writes one byte to file descriptor 1 (standard output).
System calls are unbuffered; each read and write operation immediately accesses the file descriptor.


simpcat3.c - Uses Buffered I/O Functions (fread and fwrite):

fread(&c, 1, 1, stdin) reads one byte from stdin using buffered I/O, and fwrite(&c, 1, 1, stdout) writes one byte to stdout.
Buffered I/O (fread and fwrite) offers a middle ground, allowing bulk reading and writing internally, reducing the number of system calls.
