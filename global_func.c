#include "myconst.h"

void global_error_and_exit(char* msg) {
	if (msg != NULL) {
		printf("%s\n", msg);
	} else {
		printf("runtime error, exit.\n");
	}
	
	exit(0);
}