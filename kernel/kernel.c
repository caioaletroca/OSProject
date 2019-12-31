#include "../drivers/screen.h"

void kmain() {
	char test[] = "Hello World!!!\n";

	clear_screen();
	print(test);
	print("Hello Nice Day!!!");
}