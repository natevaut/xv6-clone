#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: filetest <file> <offset>\n");
        exit(-1);
    }

    char *file = argv[1];
    int offset = atoi(argv[2]);

    // read file
    int fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        printf("Cannot open file\n");
        exit(-2);
    }

    // run lseek
    int newoffset = lseek(fd, offset);
    if (newoffset < 0)
    {
        printf("Not successful\n");
        exit(-3);
    }

    // check file at this new offset
    char buffer[8];
    int nc = read(fd, buffer, sizeof(buffer) - 1);
    if (nc <= 0)
    {
        printf("File error\n");
        exit(-4);
    }

    // finish
    close(fd);
    exit(0);
}
