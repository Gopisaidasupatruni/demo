/*Task8:
In the remaining questions, we provide strace output for attempts at a shell running a two-process pipeline, echo foo | wc -c. For each question, you are to characterize the shell. This is Shell X1.*/
What is the process ID of the parent shell?

The process ID of the parent shell is 58797. This is the process making pipe(), fork(), and wait4() calls.
Does Shell X1 wait for the right-hand process, the left-hand process, or both?

wait4(58798, ...): This shows the shell is waiting for the echo process (left-hand side).
wait4(58799, ...): This shows the shell is waiting for the wc process (right-hand side).
Answer: The shell waits for both processes.
Does Shell X1 appear to implement two-process pipelines correctly?

pipe([3, 4]): A pipe is created with file descriptors 3 (read) and 4 (write).
dup2(4, 1): The echo process redirects its STDOUT to the pipe's write end.
dup2(3, 0): The wc process redirects its STDIN to the pipe's read end.
close() calls properly close unused pipe ends.
Answer: Yes, Shell X1 implements the pipeline correctly. The parent shell creates the pipe, connects the processes, and waits for both to finish.
