#include "screen.h"
#include "ports.h"

// Private Methods Declaration
int get_cursor_offset();
void set_cursor_offset(int offset);
int print_char(char character, int col, int row, char attribute_byte);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

void print(char *message) {
	print_at(message, -1, -1);
}

void print_at(char *message, int col, int row) {
	int offset;

	// Update the cursor if col and row not negative.
	if(col >= 0 && row >= 0) {
		set_cursor_offset(get_offset(col, row));
	}
	//print_char((char)message[0], 1, 1, WHITE_ON_BLACK);
	int i = 0;
	while(message[i] != 0) {
		offset = print_char(message[i++], col, row, WHITE_ON_BLACK);
		
		row = get_offset_row(offset);
        col = get_offset_col(offset);
	}
}

/**
 * Prints a character on the screen
 * @param character      [description]
 * @param col            [description]
 * @param row            [description]
 * @param attribute_byte [description]
 */
int print_char(char character, int col, int row, char attribute_byte) {
	/* Create a byte ( char ) pointer to the start of video memory */
	unsigned char *vidmen = (unsigned char *)VIDEO_ADDRESS;

	/* If attribute byte is zero, assume the default style. */
	if(!attribute_byte)
		attribute_byte = WHITE_ON_BLACK;

	/* Get the video memory offset for the screen location */
	int offset;
	/* If col and row are non-negative , use them for offset. */
	if(col >= 0 && row >= 0) {
		offset = get_offset(col, row);
	}
	/* Otherwise, use the current cursor position. */
	else {
		offset = get_cursor_offset();
	}

	// If we see a newline character, set offset to the end of
	// current row, so it will be advanced to the first col
	// of the next row.
	if(character == '\n') {
		row = get_offset_row(offset);
		offset = get_offset(0, row + 1) - 1;
	}
	// Otherwise, write the character and its attribute byte to
	// video memory at our calculated offset.
	else {
		vidmen[offset] = character;
		vidmen[offset + 1] = attribute_byte;
	}

	// Update the offset to the next character cell, which is
	// two bytes ahead of the current cell.
	offset += 2;

	// Make scrolling adjustment, for when we reach the bottom
	// of the screen.
	//offset = handle_scrolling(offset);

	// Update the cursor position on the screen device.
	set_cursor_offset(offset);
	return offset;
}

/**
 * Gets the current position of the cursos on screen memory
 * @param  col [description]
 * @param  row [description]
 * @return     [description]
 */
int get_cursor_offset() {
	/* Use the VGA ports to get the current cursor position
	* 1. Ask for high byte of the cursor offset (data 14)
	* 2. Ask for low byte (data 15)
	*/
	port_byte_out(REG_SCREEN_CTRL, 14);
	int offset = port_byte_in(REG_SCREEN_DATA) << 8; // Gets the high byte
	port_byte_out(REG_SCREEN_CTRL, 15);
	offset += port_byte_in(REG_SCREEN_DATA);
	return offset * 2;
}

/**
 * Sets the cursor position as screen memory
 * @param offset [description]
 */
void set_cursor_offset(int offset) {
	/* Similar to get_cursor_offset, but instead of reading we write data */
	offset /= 2;
	port_byte_out(REG_SCREEN_CTRL, 14);
	port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
	port_byte_out(REG_SCREEN_CTRL, 15);
	port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

/**
 * Clears the screen with black chars
 */
void clear_screen() {
	int screen_size = MAX_COLS * MAX_ROWS;
	unsigned char *screen = (unsigned char *) VIDEO_ADDRESS;

	for(int i = 0; i < screen_size; i++) {
		screen[i * 2] = ' ';
		screen[i * 2 + 1] = WHITE_ON_BLACK;
	}
	set_cursor_offset(get_offset(0, 0));
}

/**
 * Converts coordinates position to memory position
 * @param  col [description]
 * @param  row [description]
 * @return     [description]
 */
int get_offset(int col, int row) {
	return 2 * (row * MAX_COLS + col);
}
int get_offset_row(int offset) {
	return offset / (2 * MAX_COLS);
}
int get_offset_col(int offset) {
	return (offset - (get_offset_row(offset) * 2 * MAX_COLS))/2;
}