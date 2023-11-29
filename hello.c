#include <stdio.h>

int count = 0;

// this function should not be called by other files, only this file
// so it is not defined in the header...
void increment() {
	count++;
}

void say_hello() {
	increment();
	if (count == 1) {
		printf("Hello, world!\n");
	} else {
		printf("Hello, world! x%d\n", count);
	}
}
