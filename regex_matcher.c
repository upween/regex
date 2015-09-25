#include "nodemaker.c"

//this test is uncorrect. 
//* here is +, can only match 0 or 1 preCharactor, more preCharactor will match fail.
bool simple_match(char* pattern, char* str) {
	int strIdx = 0;
	NFA* nfa = make_nfa(pattern);

	printf("nfa nodes size = %d\n", nfa -> nodes -> list_size);

	int PRINT_NODES = TRUE;
	if (PRINT_NODES) {
		for( int i = 0; i < nfa -> nodes -> list_size; i++) {
			NNode* temp_node = ilib_list_get(nfa -> nodes, i);
			if (temp_node -> node_type == START) {
				printf("~~~ START : [%d] ~~~\n", temp_node -> debug_node_idx);
			}
			for (int j = 0; j < temp_node -> path_list -> list_size; j++) {
				NPath* temp_path = ilib_list_get(temp_node -> path_list, j);
				int start_idx = temp_node -> debug_node_idx;
				int temp_char = temp_path -> allowed_char;
				int end_idx = temp_path -> target_node -> debug_node_idx;
				if (j == 0) {
					printf("[%d]-----(%c)------[%d]\n", start_idx, temp_char, end_idx);
				} else {
					printf("   -----(%c)------[%d]\n", temp_char, end_idx);
				}
			}
			if (temp_node -> node_type == END) {
				printf("~~~ END   : [%d] ~~~\n", temp_node -> debug_node_idx);
			}
		}
		printf("\n");
	}

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
