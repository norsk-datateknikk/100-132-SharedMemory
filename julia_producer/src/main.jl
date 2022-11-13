using InterProcessCommunication
using Printf

function wait_for_key(; prompt="Press any key.", io=stdin)
    setraw!(raw) = ccall(:jl_tty_set_mode, Int32, (Ptr{Cvoid}, Int32), io.handle, raw)
    print(io, prompt)
    setraw!(true)
    read(io, 1)
    setraw!(false)
    nothing
end

shared_memory_size = 1024 # bytes

file_path = "/my_shm_file"

shared_memory = SharedMemory(file_path, shared_memory_size; perms=0o777, volatile=true)

memory_start = pointer(shared_memory)
@printf "Memory start is at %s\n" memory_start

# TODO add char array to memory to enable reading from consumer.
#unsafe_store!(memory_start, "Hello World!")
# use unsafe_load to read from memory.

wait_for_key(prompt="Press any key to exit.")

# To ensure that shared memory object is eventually destroyed.
rm(shared_memory)