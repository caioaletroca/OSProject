#include "../drivers/screen.h"

void kmain() {
	clear_screen();
	print_at("Hello World!!!\n", 10, 10);
}