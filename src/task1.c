// From task 0 copy all functions
void VGA_clear_pixelbuff() {
	
}

void VGA_draw_point(int x, int y, short c) {
	int address = 0xC8000000 | (y << 10) | (x << 1);
    write_halfword(address, c);
}

void VGA_write_char(int x, int y, char c) {
	// TODO
}

void VGA_clear_charbuff() {
		// TODO
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