#include "defs.h"
#include "commands.h"
#include "users.h"
#include "tools.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	commands();
	users();
	tools();
	printf("%s\n", NAME);

	return EXIT_SUCCESS;
}
