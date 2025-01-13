The main issue with Shell X3 is its sequential handling of processes, where it waits for each child to finish before creating the next one. This is fine for a simple two-process pipeline like echo foo | wc -c, but it doesn't scale well to more complex pipelines.
