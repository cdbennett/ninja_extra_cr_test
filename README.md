Test case for Ninja adding extra CR to output
=============================================

Apparently Ninja 1.4.0 on Windows is adding an extra CR character to any
CRLF line endings in output produced by a subprocess, so that lines are
terminated with CR CR LF.  This is causing Eclipse (CodeWarrior 10.5, to
be precise) to have trouble parsing the compiler warning and error
messages.

This test case has two .c programs designed to be compiled with MinGW
gcc which print "Hello, World" with a newline.  But one program changes
the mode of stdout to binary so that the MinGW stdio library does not convert the \n to a \r\n.

The result is that Ninja adds a CR before an LF character in the tool
output.  In the case of the tool that produces output having only LF
newlines (Unix-style), this means that Ninja yields a CRLF line ending
on its output.  But if the subprocess that Ninja calls produces line
endings of CRLF already, Ninja still adds a CR before the LF and this
means that Ninja produces lines with CR CR LF endings.

Test results
------------

    $ ninja
    [4/4] gcc  hello_lf.o -o hello_lf.exe

    $ ninja -f test.ninja -j1 | cat -v
    [1/2] hello  hello1^M
    Hello, World!^M^M
    [2/2] hello_lf  hello2^M
    Hello, World!^M

Note the appearance of ^M^M on the output produced by `hello`, which uses text mode and thus is producing CRLF line endings itself.

    $ ./hello | cat -v
    Hello, World!^M

    $ ./hello_lf | cat -v
    Hello, World!

The test environment is Windows 7 64-bit, Ninja 1.4.0, MinGW gcc 4.8.1.
The test was performed in a Git MSYS Bash shell.

