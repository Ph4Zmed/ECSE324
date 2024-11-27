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


void VGA_draw_point(int x, int y, short c) {
	unsigned int address = 0xC8000000 | (y << 10) | (x << 1);
    write_halfword(address, c);
}

void VGA_write_char(int x, int y, char c) {
	unsigned int address = 0xC9000000 | (y << 7) | x;
    write_byte(address, c);
}

void VGA_clear_pixelbuff() {
    for (int y = 0; y < 240; y++)
    {
        for (int x = 0; x < 320; x++)
        {
            VGA_draw_point(x, y, 0);
        }
    }
}

void VGA_clear_charbuff() {
    for (int y = 0; y < 60; y++)
    {
        for (int x = 0; x < 80; x++)
        {
            VGA_write_char(x, y, 0);
        }
    }
}
void draw_test_screen ()
{
    VGA_clear_pixelbuff();
    VGA_clear_charbuff();
	int SCREEN_HEIGHT=240;
	int SCREEN_WIDTH=320;
   for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            // Calculate color components to create a smooth gradient
            unsigned int red = (x * 31 / SCREEN_WIDTH) << 11;      // Horizontal red gradient
            unsigned int green = (y * 63 / SCREEN_HEIGHT) << 5;    // Vertical green gradient
            unsigned int blue = ((x + y) * 31 / (SCREEN_WIDTH + SCREEN_HEIGHT));  // Diagonal blue gradient

            // Combine red, green, and blue into a 16-bit color
            unsigned int color = red | green | blue;

            // Draw the pixel at (x, y) with the calculated color
            VGA_draw_point(x, y, color);
        }
    }


    const char *message = "Hello World!";
    int x = 20;
    int y = 5;
    
    for (int i = 0; message[i] != '\0'; i++) {
        VGA_write_char(x++, y, message[i]);
    }
}

int main() {
	draw_test_screen();
	return 0;
}