# Pipes

Pipes have independent write and read endpoints.

In practice, this means a pipe returns two file descriptors, one to write to (grow) the pipe,
one to read from (consume) the pipe. This is similar to a queue.

# Inter-process communication

Pipes are a simple way to communicate between processes. If one process writes to the pipe, the
other one can consume it like a server.
