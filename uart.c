#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY);
    if (fd == -1) {
        perror("Error: Unable to open /dev/ttyUSB0");
        return 1;
    }

    printf("UART device opened successfully\n");

    struct termios options;
    tcgetattr(fd, &options);

    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);

    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;

    tcsetattr(fd, TCSANOW, &options);

    char buf[] = "Hello UART V2\n";
    int bytes_written = write(fd, buf, strlen(buf));

    if (bytes_written < 0) {
        perror("Write failed");
    } else {
        printf("Data sent successfully\n");
    }

    close(fd);
    return 0;
}
