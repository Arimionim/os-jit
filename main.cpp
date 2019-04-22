#include <iostream>
#include <sys/mman.h>
#incldue <strdef>


/*
 * int zero(){
 *  return 0;
 * }
 */
unsigned const char code[] = {
        0x55,                          // push  rbp
        0x48, 0x89, 0xe5,              // mov   rbp, rsp
        0xb8, 0x00, 0x00, 0x00, 0x00,  // mov   eax, 0x0
        0x5d,                          // pop   rbp
        0xc3                           // ret
};

static int const size = 11;

void print_error(const char* reason) {
    std::cerr << "hij: " << reason;
    if (errno) {
        std::cerr << ": " << strerror(errno);
    }
    std::cerr << std::endl;
}

int main(int argc, char ** argv) {
    void* data = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);


    if (memory == MAP_FAILED) {
        print_error("can't allocate memory");
        return EXIT_FAILURE;
    }

    memcpy(memory, code, size);

    {
        int result = mprotect(memory, size, PROT_READ | PROT_EXEC);

        if (result == CALL_FAILED) {
            print_error("can't make data executable");
            munmap(memory, size);
            return EXIT_FAILURE;
        }
    }

    func f = (func)memory;

    std::cout << f() << std::endl;

    {
        int result = munmap(memory, size);
        if (result == CALL_FAILED) {
            print_error("can't deallocate memory");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}