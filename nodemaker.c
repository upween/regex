#include "ilib.c"
#include "strctr.c"

#define START 0
#define MIDDLE 1
#define END 2

typedef struct _nfa_node{
	int node_type;
	List *path_list;
} NNode;

typedef struct _nfa{
	NNode *start_node;
	List *nodes;
} NFA;

typedef struct _nfa_path{
	NNode *target_node;
	char allowed_char;
} NPath;


NPath* new_npath() {
	NPath* path = malloc(sizeof(NPath));
	return path;
}

void destory_npath(NPath* path) {
	free(path);
}


NNode* new_nnode(int node_type) {
	NNode* node = malloc(sizeof(NNode));
	node -> node_type = node_type;
	node -> path_list = ilib_list_newlist();
	return node;
}

void destory_nnode(NNode* node) {
	if (node -> path_list != NULL) {
		while (node -> path_list -> list_size != 0) {
			NPath* path = ilib_list_get(node -> path_list, 0);
			destory_npath(path);
			ilib_list_remove(node -> path_list, 0, FALSE);
		}
		ilib_list_destroylist(node -> path_list, FALSE);
	}
	free(node);
}


NFA* new_nfa() {
	NFA* nfa = malloc(sizeof(NFA));
	nfa -> nodes = ilib_list_newlist();
	return nfa;
}

void destory_nfa(NFA* nfa) {
	if (nfa -> nodes != NULL) {
		while (nfa -> nodes -> list_size != 0) {
			NNode* node = ilib_list_get(nfa -> nodes, 0);
			destory_nnode(node);
			ilib_list_remove(nfa -> nodes, 0, FALSE);
		}
		ilib_list_destroylist(nfa -> nodes, FALSE);
	}
	free(nfa);
}

NNode* end_current_path(NFA* nfa, NNode* section_end_node, NNode* current_node) {
	if (section_end_node == NULL) {
		section_end_node = new_nnode(END);
		ilib_list_append(nfa -> nodes, section_end_node);
	}

	NPath* path = new_npath();
	path -> target_node = section_end_node;
	path -> allowed_char = EPSILON;
	ilib_list_append(current_node -> path_list, path);

	return section_end_node;
}

NFA* make_nfa(char* regex) {
	NNode* current_node = NULL;
	NNode* pre_node = NULL;
	NNode* section_start_node = NULL;
	NNode* section_end_node = NULL;
	Stack* stack_start_nodes = NULL;

	NFA* nfa = new_nfa();
	CtrlString* ctr_regex = strctr_init(regex);

	current_node = new_nnode(START);
	section_start_node = current_node;
	nfa -> start_node = current_node;
	ilib_list_add(nfa -> nodes, nfa -> start_node, 0);

	char prec;
	char c = '\0';
	while(TRUE) {
		prec = c;
		c = strctr_next(ctr_regex);

		if ( c == '*') {
			if (pre_node != NULL) {
				NPath* path = new_npath();
				path -> target_node = pre_node;
				path -> allowed_char = prec;
				ilib_list_append(pre_node -> path_list, path);

				NPath* path2 = new_npath();
				path2 -> target_node = current_node;
				path2 -> allowed_char = EPSILON;
				ilib_list_append(pre_node -> path_list, path2);
			} else {
				char* errmsg = "error regex, system will exit.";
				global_error_and_exit(errmsg);
			}
		} else if ( c == '|') {
			section_end_node = end_current_path(nfa, section_end_node, current_node);

			current_node = section_start_node;
			pre_node = NULL;
		} else if ( c == '(') {
			if (stack_start_nodes == NULL) {
				stack_start_nodes = ilib_stack_newstack();
			}
			ilib_stack_push(stack_start_nodes, section_start_node);
			section_start_node = current_node;
		} else if ( c == ')') {
			if (stack_start_nodes == NULL || stack_start_nodes -> list_size == 0) {
				char* errmsg = "error regex, ( ) not match, will exit. ";
				global_error_and_exit(errmsg);
			} else {
				section_end_node = end_current_path(nfa, section_end_node, current_node);
				section_end_node -> node_type = MIDDLE;
				current_node = section_end_node;
				section_start_node = ilib_stack_pop(stack_start_nodes);
				section_end_node = NULL;
			}
		} else if ( (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ) {

			NNode* temp_node = new_nnode(MIDDLE);
			ilib_list_append(nfa -> nodes, temp_node);

			NPath* path = new_npath();
			path -> target_node = temp_node;
			path -> allowed_char = c;
			ilib_list_append(current_node -> path_list, path);

			pre_node = current_node;
			current_node = temp_node;

		} else if ( c == '\0') {
			section_end_node = end_current_path(nfa, section_end_node, current_node);

			if (stack_start_nodes != NULL && stack_start_nodes -> list_size != 0) {
				global_error_and_exit("error regex, ( ) not match, will exit. ");
			}

			return nfa;

		} else {
			char* errmsg = "error regex, system will exit.";
			global_error_and_exit(errmsg);
		}
	}
}
