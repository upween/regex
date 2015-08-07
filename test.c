#include "strctr.c"
#include "ilib.c"
#include "myconst.h"

int main() {
	return test_list();
}

int test_list(){
	List * list = ilib_list_newlist();
	char *str1 = "abc\n";
	char *str2 = "def\n";
	char *str3 = "ghi\n";

	ilib_list_add(list, str1, 0);
	ilib_list_add(list, str3, 1);
	ilib_list_add(list, str2, 1);

	printf(ilib_list_get(list, 0));
	printf(ilib_list_get(list, 1));
	printf(ilib_list_get(list, 2));
	printf(ilib_list_get(list, 0));
}

int test_strctr() {
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