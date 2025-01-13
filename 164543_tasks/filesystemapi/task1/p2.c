time simpcat1 < large > /dev/null

This version uses getchar and putchar, which are buffered through the standard I/O library.
Buffered I/O reduces the number of system calls by accumulating data before performing input or output operations, which should make this version relatively fast.
time simpcat2 < large > /dev/null

This version uses the system calls read and write directly, which are unbuffered.
Since simpcat2 makes a system call for every single character, it results in a much higher number of system calls for large files. Each call involves kernel-space operations, which adds overhead, making simpcat2 the slowest.
time simpcat3 < large > /dev/null

This version uses fread and fwrite, which are buffered functions like getchar and putchar but are more optimized for bulk operations.
fread and fwrite typically handle larger chunks of data at a time, reducing the number of system calls, making it more efficient than simpcat2 and comparable to or faster than simpcat1.
