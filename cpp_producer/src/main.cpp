#include <iostream>
#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FILE_PATH "/my_shm_file"

int main(int argc, char *argv[])
{
    void *addr;
    char data[256] = "Hello World";
    size_t shared_memory_size = 1024;

    // get shared memory file descriptor
    int file_descriptor = shm_open(FILE_PATH, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    // Increase the memory size.
    int res = ftruncate(file_descriptor, shared_memory_size);

    // Map shared memory
    // Let the system choose the address, specifying NULL as the value for the argument addr
    addr = mmap(NULL, shared_memory_size, PROT_READ | PROT_WRITE, MAP_SHARED, file_descriptor, 0);
    if (addr == MAP_FAILED)
        std::cout << "MAP FAILED!";

    // place data into memory
    int len = strlen(data) + 1;
    memcpy(addr, data, len);

    do 
    {
        std::cout << '\n' << "Press a key to continue...";
    } while (std::cin.get() != '\n');

    // mmap cleanup
    res = munmap(addr, 256);

    // shm_open cleanup
    file_descriptor = shm_unlink(FILE_PATH);

    return EXIT_SUCCESS;
}