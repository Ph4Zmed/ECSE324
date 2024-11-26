// From task 0 copy all functions
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
}

// Writes a word (4 bytes) to a specific memory address
void write_word(unsigned int address, int value) {
    __asm__ __volatile__ (
        "str %1, [%0]"
        :
        : "r" (address), "r" (value)
    );
}

void VGA_write_char(int x, int y, char c) {
	unsigned int address = 0xC9000000 | (y << 7) | x;
    write_byte(address, c);
}

void VGA_draw_point(int x, int y, short c) {
	unsigned int address = 0xC8000000 | (y << 10) | (x << 1);
    write_halfword(address, c);
}

void VGA_clear_pixelbuff() {
	unsigned int address;
    int x, y = 0;
    for (int y = 0; y < 240; y++)
    {
        for (int x = 0; x < 320; x++)
        {
            address = 0xC8000000 | (y << 10) | (x << 1);
            write_halfword(address, 0);
            address += 2;
        }
    }
}

void VGA_clear_charbuff() {
	unsigned int address;
    int x, y = 0;
    for (int y = 0; y < 60; y++)
    {
        for (int x = 0; x < 80; x++)
        {
            address = 0xC9000000 | (y << 7) | x;
            write_byte(address, 0);
            address += 2;
        }
    }
}

int read_PS2_data(char *data) {
	unsigned int address = 0xFF200100;
    char status = read_byte(address) >> 15;
    if ((status & 0x01) == 0) {
        return 0;
    }
    *data = read_halfword(address);
    return 1;
}

void write_hex_digit(unsigned int x,unsigned int y, char c) {
    if (c > 9) {
        c += 55;
    } else {
        c += 48;
    }
    c &= 255;
    VGA_write_char(x,y,c);
}
void write_byte_kbrd(unsigned int x,unsigned int y, unsigned int c) {
   char lower=c>>4 &0x0F;
   write_hex_digit(x,y,lower);
   char upper=c&0x0F;
   write_hex_digit(x+1,y,upper);
   return;
}

void input_loop_fun() {
    unsigned int x = 0;
    unsigned int y = 0;
	VGA_clear_pixelbuff();
    VGA_clear_charbuff();

    while (y<=59) {
    
        char data;
        char r2 = read_PS2_data(&data);

        if (r2 != 0) {  // Check if data is available

            write_byte_kbrd(x,y,data); 
            x += 3;
            if (x > 79) {
                y++;
                x = 0;
            }

            if (y > 59) {  // Check if loop should exit
                return;  // End of input loop
            }
        }
    }
}


int main() {
	input_loop_fun();
	return 0;
}
