#include <stdio.h>
#include <iostream>

#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FILE_PATH "/my_shm_file"

int main(int argc, char *argv[])
{
    void *addr;
    size_t shared_memory_size = 1024;
    char data[shared_memory_size];

    // Get shared memory file descriptor
    int file_descriptor = shm_open(FILE_PATH, O_RDONLY, S_IRUSR | S_IWUSR);
    if (file_descriptor == -1)
    {
        perror("open");
        return 10;
    }

    // Map shared memory.
    addr = mmap(NULL, shared_memory_size, PROT_READ, MAP_SHARED, file_descriptor, 0);

    // Read data from shared memory.
    memcpy(data, addr, shared_memory_size);

    printf("Read from shared memory: \"%s\"\n", data);

    return EXIT_SUCCESS;
}