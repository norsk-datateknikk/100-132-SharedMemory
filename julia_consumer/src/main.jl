using InterProcessCommunication

memory_size = 1024 # bytes

file_path = "/my_shm_file"

shared_memory = SharedMemory(file_path, readonly=false)

memory_start = pointer(shared_memory)

print(memory_start)

# To ensure that shared memory object is eventually destroyed.
rm(shared_memory)