#include <iostream>
#include <sys/mman.h>


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

void print_error(std::string const & reason) {
    std::err << "OS_jit: " + reason << std::endl;
    if (errno){
        std::err << "OS_jit: " + strerror(errno) << std::endl;
    }
}

int clearData(void *data){
    int result = munmap(data, size);
    if (result == CALL_FAILED) {
        print_error("can't deallocate data");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

template <typename T>
bool check(T data, T def, std::string const & errorMessage){
    if (data == def){
        print_error(errorMessage);
        return 0;
    }
    return 1;
}

int main(int argc, char ** argv) {
    void* data = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);


    if (!check(data, MAP_FAILED, "cant alloc data")) {
        return EXIT_FAILURE;
    }

    memcpy(data, code, size);

    int result = mprotect(data, size, PROT_READ | PROT_EXEC);

    if (!check(result, CALL_FAILED, "cant make data exec")) {
        munmap(data, size);
        return EXIT_FAILURE;
    }

    std::cout << reinterpret_cast<int(*)()>(data) << std::endl;

    return clearData(data);;
}