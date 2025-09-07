#include <windows.h>
#include <iostream>
#include <stdio.h>

// this shellcode to call the hello function from the code below
unsigned char output_example_hello_world_bin[] = {
  0x48, 0x89, 0xc8, 0x48, 0x89, 0xd1, 0xff, 0xd0, 0xc3
};
unsigned int output_example_hello_world_bin_len = 9;

// own function
void hello(long long num) {
    printf("num = %lld\n", num);
}

// we can bypass some "static" analysis
int main() {

    // allocating space for shellcode
    void* addrMemExec = VirtualAlloc(0, output_example_hello_world_bin_len, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    if (!addrMemExec) {
        std::cout << "Memory allocation failed." << std::endl;
        return 1;
    }

    // copy shellcode in memory allocated
    memcpy(addrMemExec, output_example_hello_world_bin, output_example_hello_world_bin_len);

    // we define a function from shellcode
    using ShellFunc = void(*)(void(*)(long long), long long);
    ShellFunc f = (ShellFunc)addrMemExec;

    f(hello, 123); // we are doing the same as hello(123)

    return 0;
}
