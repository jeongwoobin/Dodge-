#include <stdio.h>
#include "show.h"
#include "console.h"

int main(void) {
	updateConsoleSize();
	disappearConsoleCursor();

	menu();
	
	return 0;
}