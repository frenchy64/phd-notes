# Named pipe

A named pipe (aka. a FIFO), is like a pipe except it is actually a file on the disk. 
This means we can `open` it from any process, unlike pipes which can only be opened from a child process.

Both ends will block as soon as they are opened until the other end is also opened.
