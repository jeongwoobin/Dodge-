#include <stdio.h>
#include "show.h"
#include "console.h"

int main(void) {
	updateConsole();
	disappearConsoleCursor();

	menu();
	
	return 0;
}