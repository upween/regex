#include "myconst.h"

typedef struct _ctr_string {
	int idx;
	char * str;
} CtrlString;

CtrlString* strctr_init(char * str) {
	if (str == NULL) {
		return NULL;
	}

	CtrlString* string_struct = malloc(sizeof(CtrlString));
	string_struct -> idx = 0;

	int size = strlen(str);
	string_struct -> str = malloc(size + 1);
	strcpy(string_struct -> str, str);

	return string_struct;
}

void strctr_recycle(CtrlString* str) {
	free(str -> str);
	free(str);
}

char strctr_next(CtrlString* str) {
	return *(str -> str + str -> idx++);
}

void strctr_rollback(CtrlString* str) {
	if (str -> idx > 0) {
		str -> idx--;
	}
}