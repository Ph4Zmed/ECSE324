#include <stdint.h>

// Reads a byte from a specific memory address
char read_byte(unsigned int address) {
    char value;
    asm volatile (
        "ldrb %0, [%1]"
        : "=r" (value)
        : "r" (address)
    );
    return value;
}

// Writes a byte to a specific memory address
void write_byte(unsigned int address, char value) {
    asm volatile (
        "strb %1, [%0]"
        :
        : "r" (address), "r" (value)
    );
}

// Reads a halfword (2 bytes) from a specific memory address
short read_halfword(unsigned int address) {
    short value;
    asm volatile (
        "ldrh %0, [%1]"
        : "=r" (value)
        : "r" (address)
    );
}

// Writes a halfword (2 bytes) to a specific memory address
void write_halfword(unsigned int address, short value) {
    asm volatile (
        "strh %1, [%0]"
        :
        : "r" (address), "r" (value)
    );
}   

// Reads a word (4 bytes) from a specific memory address
int read_word(unsigned int address) {
    int value;
    asm volatile (
        "ldr %0, [%1]"
        : "=r" (value)
        : "r" (address)
    );
}

// Writes a word (4 bytes) to a specific memory address
void write_word(unsigned int address, int value) {
    asm volatile (
        "str %1, [%0]"
        :
        : "r" (address), "r" (value)
    );
}

// Main Function
int main() {
    write_byte(0x20000000, 0x14);
    // Read a byte from address 0x20000000
    char byte = read_byte(0x20000000);
    // Write a byte to address 0x20000000
    write_byte(0x20000000, 0x12);

    // Read a halfword from address 0x20000000
    short halfword = read_halfword(0x20000000);
    // Write a halfword to address 0x20000000
    write_halfword(0x20000000, 0x1234);

    // Read a word from address 0x20000000
    int word = read_word(0x20000000);
    // Write a word to address 0x20000000
    write_word(0x20000000, 0x12345678);

    return 0;
}