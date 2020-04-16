#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFFERSIZE 4096
#define COPYMODE 0644 /* rw-r--r-- */

int exception(const char *r1, char *r2)
{
    fprintf(stderr, "Error: %s", r1);
    perror(r2);
    exit(1);
}

int main(int argc, char const *argv[])
{
    int in_fd, out_fd, n_chars;
    char buf[BUFFERSIZE];
    if (argc != 3)
    {
        fprintf(stderr, "usage: %s source destination\n", *argv);
        exit(1);
    }

    if ((in_fd = open(argv[1], O_RDONLY)) == -1)
        exception("Cannot open", argv[1]);
    if ((out_fd = open(argv[2], O_CREAT | O_RDWR)) == -1)
        exception("Cannot crate", argv[2]);
    while ((n_chars = read(in_fd, buf, BUFFERSIZE)) > 0)
        if (write(out_fd, buf, n_chars) != n_chars)
            exception("Write error to ", argv[2]);
    if (n_chars == -1)
        exception("Read error from ", argv[1]);
    if (close(in_fd) == -1 || close(out_fd) == -1)
        exception("Error cloing Files", "");

    return 0;
}
