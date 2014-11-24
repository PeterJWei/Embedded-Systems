#include "include.h"
#include "write.h"

//extern void exit_handler(int exit_status);
// write function to replace the system's write function
ssize_t write_handler(int fd, const void *buf, size_t count) {

    // Check for invalid memory range or file descriptors
    if (check_mem((char *) buf, (int) count, SDRAM_START, SDRAM_END) == FALSE &&
        check_mem((char *) buf, (int) count, SFROM_START, SFROM_END) == FALSE) {
//        exit_handler(-EFAULT);
    } else if (fd != STDOUT_FILENO) {
//        exit_handler(-EBADF);
    }

    char *buffer = (char *) buf;
    int i;
    char read_char;
    for (i = 0; (size_t)i < count; i++) {
        // put character into buffer and putc
        read_char = buffer[i];
        putc(read_char);
    }
    return i;
}
