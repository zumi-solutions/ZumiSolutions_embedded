#include <stdio.h>
#include <fcntl.h>   // File control definitions
#include <termios.h> // POSIX terminal control definitions
#include <unistd.h>  // UNIX standard function definitions

int main() {
    int fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY);
    if (fd == -1) {
        perror("open_port: Unable to open /dev/ttyUSB0");
        return 1;
    }

    struct termios options;
    tcgetattr(fd, &options);
    cfsetispeed(&options, B9600); // Set baud rate to 9600
    cfsetospeed(&options, B9600);
    options.c_cflag |= (CLOCAL | CREAD); // Enable receiver, local mode
    options.c_cflag &= ~PARENB;          // No parity
    options.c_cflag &= ~CSTOPB;          // 1 stop bit
    options.c_cflag &= ~CSIZE;           // Mask character size bits
    options.c_cflag |= CS8;              // 8 data bits
    tcsetattr(fd, TCSANOW, &options);

    char buf[] = "Hello UART\n";
    write(fd, buf, sizeof(buf)); // Send data

    close(fd);
    return 0;
}
