#include "../drivers/screen.h"
#include "utils.h"

void kmain() {
	clear_screen();

	print_at("Hello World!!!\n", 0, 24);
	print("Hello World!!!\n");
	print("Hello World With Scroll!!!\n");
}