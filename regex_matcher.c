#include "nodemaker.c"

//this test is uncorrect. 
//* here is +, can only match 0 or 1 preCharactor, more preCharactor will match fail.
bool simple_match(char* pattern, char* str) {
	int strIdx = 0;
	NFA* nfa = make_nfa(pattern);

	NNode* node = nfa -> start_node;
	char strChar = str[strIdx];
	while(node -> node_type != END) {
		for (int i = 0; i < node -> path_list -> list_size; i++) {
			NNode* bak_node_for_epsilon = NULL;

			NPath* path = ilib_list_get(node -> path_list, i);
			if (path -> allowed_char == strChar) {
				node = path -> target_node;
				strIdx++;
				strChar = str[strIdx];
				break;
			} else if (path -> allowed_char == EPSILON) {
				bak_node_for_epsilon = path -> target_node;
			}
			if (i == node -> path_list -> list_size - 1) {
				if (bak_node_for_epsilon != NULL) {
					node = bak_node_for_epsilon;
					break;
				} else {
					return FALSE;
				}
			}
		}
	}

	if (strChar == '\0') {
		return TRUE;
	} else {
		return FALSE;
	}
}
