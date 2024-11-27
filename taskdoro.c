// IN-LINE ASSEMBLY FUNCTIONS ------------------------
// Reads a byte from a specific memory address
char read_byte(unsigned int address){
	char y = 0;
	__asm__ __volatile__(
		"ldrsb %0, [%1]"
		:"=r"(y)
		:"r"(address)
	);
	return y;
}

// Writes a byte to a specific memory address
void write_byte(unsigned int address, char value){
	__asm__ __volatile__(
		"strb %0, [%1]"
		:"+r"(value) // value is the input to be stored
		:"r"(address)
		:"r1"
	);
}

// Reads a halfword (2 bytes) from a specific memory address
short read_halfword(unsigned int address){
	short y = 0;
	__asm__ __volatile__(
		"ldrsh %0, [%1]"
		:"=r"(y)
		:"r"(address)
	);
	return y;
}

// Writes a halfword (2 bytes) to a specific memory address
void write_halfword(unsigned int address, short value){
	__asm__ __volatile__(
		"strh %0, [%1]"
		:"+r"(value)
		:"r"(address)
		:"r1"
	);
}
// Reads a word (4 bytes) from a specific memory address
int read_word(unsigned int address){
	int y = 0;
	__asm__ __volatile__(
		"ldr %0, [%1]"
		:"=r"(y)
		:"r"(address)
	);
	return y;
}

// Writes a word (4 bytes) to a specific memory address
void write_word(unsigned int address, int value){
	__asm__ __volatile__(
		"str %0, [%1]"
		:"+r"(value)
		:"r"(address)
		:"r1"
	);
}

// VGA DRIVERS ----------------------------------
// check if coordinates are valid
char valid_coords(int x, int y, char type) {
	// type: 0 for pixel, 1 for character
	// returns: 0 for invalid, 1 for valid
	if (x < 0 || y < 0){
		return 0; // lower lim not satisfied
	}
	int xlim, ylim;
	switch (type){
		case 0:
			xlim = 319;
			ylim = 239;
			break;
		case 1:
			xlim = 79;
			ylim = 59;
			break;
		default:
			return 0;
	}
	if (x <= xlim && y <= ylim){
		return 1; // within bounds
	}
	return 0;
}

// draw a point at (x, y) of colour c
void VGA_draw_point(int x, int y, short c) {
	char is_valid = valid_coords(x, y, 0);
	if (!is_valid){
		return;
	}
	unsigned int addr = 3355443200;
	addr += x*2;
	addr += y*1024;
	
	write_halfword(addr, c);	
}

// clear all valid points in memory of the pixel buffer to 0
void VGA_clear_pixelbuff() {
	short reset_c = 0;
	for (int x = 0; x < 320; x++){
		for (int y = 0; y < 240; y++){
			VGA_draw_point(x, y, reset_c);
		}
	}
}

// write char c at point (x, y)
void VGA_write_char(int x, int y, char c) {
	char is_valid = valid_coords(x, y, 1);
	if (!is_valid){
		return;
	}
	unsigned int addr = 3372220416;
	addr += x;
	addr += y*128;
	
	write_byte(addr, c);
}

// clear all valid points in memory of char buffer to 0
void VGA_clear_charbuff() {
	short reset_c = 0;
	for (int x = 0; x < 80; x++){
		for (int y = 0; y < 60; y++){
			VGA_write_char(x, y, reset_c);
		}
	}
}

// PS2 DRIVER -----------------------------------------
int read_PS2_data(char *data) {
	unsigned int addr = 0xff200100;
	int ps2_reg_data = read_word(addr);
	char RVALID = (ps2_reg_data & 0x8000) >> 15;
	if (RVALID){
		*data = ps2_reg_data & 0xFF;
	}
	return RVALID;
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
