58969 wait4(58970, NULL, 0, NULL)       = 58970
58969 --- SIGCHLD {si_signo=SIGCHLD, si_code=CLD_EXITED, si_pid=58970, si_uid=1000, si_status=0, si_utime=0, si_stime=0} ---
58969 wait4(58971, NULL, 0, NULL)       = 58971
58969 --- SIGCHLD {si_signo=SIGCHLD, si_code=CLD_EXITED, si_pid=58971, si_uid=1000, si_status=0, si_utime=0, si_stime=0} ---
In the current trace, the wait4(58971, NULL, 0, NULL) is being interrupted by a SIGINT, and the parent process (shell) is killed by this signal before it can wait for both child processes. This suggests that the shell may not be properly waiting for both child processes or handling the signal correctly. so wait for both process to terminate
