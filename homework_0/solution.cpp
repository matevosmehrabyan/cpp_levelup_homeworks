#include <iostream>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int stdout_fd = 1;
    close(stdout_fd);
    int fd = open("stdout", O_CREAT | O_WRONLY);

    if (fd < 0) {
        std::cout << "Failed to open file." << std::endl;
    }

    std::cout << "Hello World!" << std::endl;
    return 0;
}
