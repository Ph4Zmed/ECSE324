
// TODO: PS/2 driver.

void write_byte_ASM(unsigned int address, char value)
{
	// From task 0
}

char read_byte(unsigned int address)
{
 	// From task 0
}
int read_PS2_data(char *data) {
 	// TODO
}


void write_byte_kbrd(unsigned int x,unsigned int y, unsigned int c) {
	unsigned int address = 0xfff0;
	write_word(address, c&0xff);
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
