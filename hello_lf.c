/* Print a message to stdout using *binary* mode.
 * This results in an LF line ending. */

#include <stdio.h>

/* _setmode, _O_BINARY */
#include <io.h>
#include <fcntl.h>

int main()
{
    _setmode(1,_O_BINARY);  /* Set stdout to binary mode */
    printf("Hello, World!\n");
    return 0;
}
