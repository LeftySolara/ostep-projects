# Intro to Kernel Hacking

To develop a better sense of how an operating system works, we will do a few projects inside a real OS kernel.

The kernel we'll be using is called xv6, a port of the original Unix (version 6). It is a small and relatively understandable OS and thus is excellent for use in simple projects.

This first project is just a warmup. The goal is simple: to add a system call to xv6. This system call, called **getreadcount()**, sinply returns how many times that the **read()** system call has been called by user processes since the time that the kernel was booted.

## Background

Watch this [discussion video](https://www.youtube.com/watch?v=vR6z2QGcoo8) and read this [background section](https://github.com/remzi-arpacidusseau/ostep-projects/blob/master/initial-xv6/background.md).

More information about xv6, including a very useful book written by the MIT folks who built xv6, can be found [here](https://pdos.csail.mit.edu/6.828/2017/xv6.html).

## Our System Call

Our system call will have the following signature:

```
int getreadcount(void)
```

This system call returns the value of a counter which is incremented every time any process calls the **read()** system call. That's it!

## Tips

One good way to start hacking inside a large codebase is to find something similar to what we want to do and to carefully copy/modify that. For example, we could take **gitpid()**, copy it in all the ways we think are needed, and then modify it to do what we need.

Most of the time will be spent on understanding the code. There shouldn't be a whole lot of code added.

## Links

- [Guide and test scripts](https://github.com/remzi-arpacidusseau/ostep-projects/tree/master/initial-xv6)
- [xv6 (x86) source code](https://github.com/mit-pdos/xv6-public)
- [xv6 (RISC-V) source code](https://github.com/mit-pdos/xv6-riscv)
