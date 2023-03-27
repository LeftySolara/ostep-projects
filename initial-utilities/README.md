# Unix Utilities

In this project, we'll build a few different UNIX utilities. These will be simple versions of commonly-used commands such as `cat`, `ls`, etc. We'll call each of them a slightly different name to avoid confusion.

Objectives:

- Re-familiarize ourselves with the C programming language
- Re-familiarize ourselves with command-line UNIX
- Learn a little about how UNIX utilities are implemented

## wcat

The program **wcat** is simple. It reads a file specified by the user and prints its contents. A typical usage is as follows:

```
prompt> ./wcat main.c
#include <stdio.h>
...
```

As shown, **wcat** reads the file **main.c** and prints out its contents.

To create the **wcat** binary, we'll create a single source file **wcat.c** and write a little code to implement the program. To compile it, we'll do the following:

```
prompt> gcc -o wcat wcat.c -Wall -Werror
```

This will create a single executable binary which we can then run as above.

For this project, it's recommended we use the following routines to do file input and output: `fopen()`, `fgets()`, and `fclose()`. If these functions are new to us, then we should read the **man pages**. To access the man page for `fopen()`, for example, just type the following into your shell:

```
prompt> man fopen
```

Then, read!

### Details

- To print the file contents, we just use `printf()`. Note that we do _not_ add a newline character to the `printf()` call. That would be changing the output to have extra newlines. We just want to print the exact contents of the file(s).
- Our program can be invoked with one or more files on the command line; it just prints each file in turn.
- In all non-error cases, **wcat** exits with status code `0`.
- If no files are specified on the command line, **wcat** just exits and returns `0`. Note that this is different from the behavior of normal UNIX **cat**.
- If the program tries to `fopen()` a file and fails, it prints the exact message "wcat: cannot open file" (followed by a newline) and exits with status code `1`. If multiple files are specified, the files are printed out in order until the end of the file list is reached or an error opening a file is reached.

## wgrep

The second utility we'll build is called **wgrep**, a variant of the UNIX tool **grep**. This tool looks through a file, line by line, trying to find a user-specified search term in the line. If a line has the word within it, the line is printed out.

Here is how a user would look for the term **foo** in the file **bar.txt**:

```
prompt> ./wgrep foo bar.txt
this line has foo int it
so does this foolish line; do you see where?
even this line, which has barfood in it, will be printed.
```

### Details

- The program will always be passed a search term and zero or more files to grep through. It goes through each line and sees if the search term is in it.
- The matching is case-sensitive.
- Lines can be arbitrarily long.
- If passed no command-line arguments, the program prints "wgrep: searchterm [file...]" (followed by a newline) and exits with status 1.
- In all other cases, **wgrep** should exit with return code `0`.
- If a search term, but no file, is specified, **wgrep** instead reads from standard input.
- If passed the empty string as a search term, then **wgrep** will match NO lines.

## wzip and wunzip

The next tools come in a pair, because one (**wzip**) is a file compression tool, and the other (**wunzip**) is a file decompression tool.

The type of compression we're using here if a simple form of compression called _run-length encoding (RLE)_. RLE is simple: when we encounter **n** characters of the same type in a row, the compression tool will turn that into the number **n** and a single instance of the character.

Thus, if we had a file with the following contents:

```
aaaaaaaaaabbbb
```

the tool would turn it into:

```
10a4b
```

The exact format of the compressed file is important. Here, we write out a 4-byte integer in binary format followed by the single character in ASCII. Thus, a compressed file will consist of some number of 5-byte entries, each of which is comprised of a 4-byte integer (the run length) and the single character.

To write out an integer in binary format, we use `fwrite()`. For **wzip**, all output is written to standard output. Thus, we would need to use shell redirection in order to write the compressed output to a file. For example, to compress the file **file.txt** into **file.z**, we would type:

```
prompt> ./wzip file.txt > file.z
```

The **wunzip** tool simply does the reverse of the **wzip** tool, taking in a compressed file and writing (to standard output) the uncompressed results. For example, to see the contents of **file.txt**, we would type:

```
prompt> ./wunzip file.z
```

**wunzip** will read in the compressed file and print out the uncompressed output using `printf()`.

### Details

- Correct invocation will pass one or more files via the command line to the program; if no files are specified, the program exits with return code `1` and prints "wzip: file1 [file2 ...]" (followed by a newline) for **wzip** and **wunzip** respectively.
- The format of the compressed files must match the description above exactly (a 4-byte integer followed by a character for each run).
- If multiple files are passed to **wzip**, they are compressed into a single compressed output. When unzipped, they are turned into a single uncompressed stream of text. The same holds true for **wunzip**.
