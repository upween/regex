#include "regex_matcher.c"

int main() {
	return test_nfa();
}

int test_nfa() {
	bool b = simple_match("abc|de*ff|ghi", "def");
	if (b == TRUE) {
		printf("simple_match success. \n");
	} else {
		printf("simple_match fail. \n");
	}
	return 0;
}

int test_list(){
	List * list = ilib_list_newlist();

	char *str1 = "111\n";
	char *str2 = "222\n";
	char *str3 = "333\n";
	char *str4 = "444\n";

	ilib_list_add(list, str1, 0);
	ilib_list_add(list, str2, 1);
	ilib_list_add(list, str3, 2);
	ilib_list_add(list, str4, 3);

	for (int i = 0; i < list -> list_size; i++) {
		printf(ilib_list_get(list, i));
	}
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
