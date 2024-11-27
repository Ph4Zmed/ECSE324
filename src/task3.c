// Drivers //

// Reads a byte from a specific memory address
char read_byte(unsigned int address) {
    char value;
    __asm__ __volatile__ (
        "ldrb %0, [%1]"
        : "=r" (value)
        : "r" (address)
    );
    return value;
}

// Writes a byte to a specific memory address
void write_byte(unsigned int address, char value) {
    __asm__ __volatile__ (
        "strb %1, [%0]"
        :
        : "r" (address), "r" (value)
    );
}

// Reads a halfword (2 bytes) from a specific memory address
short read_halfword(unsigned int address) {
    short value;
    __asm__ __volatile__ (
        "ldrh %0, [%1]"
        : "=r" (value)
        : "r" (address)
    );
    return value;
}

// Writes a halfword (2 bytes) to a specific memory address
void write_halfword(unsigned int address, short value) {
    __asm__ __volatile__ (
        "strh %1, [%0]"
        :
        : "r" (address), "r" (value)
    );
}   

// Reads a word (4 bytes) from a specific memory address
int read_word(unsigned int address) {
    int value;
    __asm__ __volatile__ (
        "ldr %0, [%1]"
        : "=r" (value)
        : "r" (address)
    );
    return value;
}

// Writes a word (4 bytes) to a specific memory address
void write_word(unsigned int address, int value) {
    __asm__ __volatile__ (
        "str %1, [%0]"
        :
        : "r" (address), "r" (value)
    );
}

// Draws a pixel at the specified (x, y) coordinate with the specified color
void VGA_draw_point(int x, int y, short c) {
	unsigned int address = 0xC8000000 | (y << 10) | (x << 1);
    write_halfword(address, c);
}

// Writes a character to the specified (x, y) coordinate
void VGA_write_char(int x, int y, char c) {
	unsigned int address = 0xC9000000 | (y << 7) | x;
    write_byte(address, c);
}

// Clears the pixel buffer
void VGA_clear_pixelbuff() {
    for (int y = 0; y < 240; y++)
    {
        for (int x = 0; x < 320; x++)
        {
            VGA_draw_point(x, y, 0);
        }
    }
}

// Clears the character buffer
void VGA_clear_charbuff() {
    for (int y = 0; y < 60; y++)
    {
        for (int x = 0; x < 80; x++)
        {
            VGA_write_char(x, y, 0);
        }
    }
}

// Reads the data from the PS2 controller
int read_PS2_data(char *data) {
	unsigned int address = 0xFF200100;
    int ps2 = read_word(address);
    int RVALID = (ps2 & 0x8000) >> 15;
    if (RVALID) {
        *data = ps2 & 0xFF;
    }
    return RVALID;
}




int main() {
    
}