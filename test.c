#include "strctr.c"
#include "myconst.h"

int main() {
	char *string = "1234567890";
	CtrlString* str = strctr_init(string);

	char c;
	char opt;
	while (TRUE) {
		scanf("%c", &opt);
		if (opt == 'n') {
			if ((c = strctr_next(str)) != '\0') {
				printf("%c\n", c);
			} else {
				break;
			}
		} else if (opt == 'b') {
			strctr_rollback(str);
		}
	}

	strctr_recycle(str);
	return 0;
}