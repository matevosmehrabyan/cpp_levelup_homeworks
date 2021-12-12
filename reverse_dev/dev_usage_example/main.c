#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>


int main() {
    int fd = open("/dev/reverse", O_RDWR);
    char buff[] = "Hello";

    int val = write(fd, buff, 5);
    printf("Wrote %d\n", val);

    char out_buf[10];
    val = read(fd, out_buf, 3);
    printf("Read %d\n", val);
    printf("GOT: %.3s\n", out_buf);

    val = read(fd, out_buf, 2);
    printf("Read %d\n", val);
    printf("GOT: %.2s\n", out_buf);

    return 0;
}
