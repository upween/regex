#include "myconst.h"
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
	List *allowed_char;
} NPath;

NFA* make_nfa(char* regex) {
	NNode* current_node;

	NFA* nfa = new_nfa();
	CtrlString* ctr_regex = strctr_init(regex);

	current_node = new_nnode(START);
	nfa -> start_node = current_node;
	ilib_list_add(nfa -> nodes, nfa -> start_node, 0);

	char prec;
	char c = '\0';
	while(TRUE) {
		prec = c;
		c = strctr_next(ctr_regex);
		if ( c == '*') {

		} else if ( c == '|') {

		} else if ( c == '(') {

		} else if ( c == ')') {

		} else if ( (c <= '9' && c >= '0') || (c <= 'Z' && c >= 'a') ) {
			
		} else if ( c == '\0') {

		}
	}
}

NFA* new_nfa() {
	NFA* nfa = malloc(sizeof(NFA));
	nfa -> nodes = ilib_list_newlist();
}

void destory_nfa(NFA* nfa) {
	if (nfa -> nodes != NULL) {
		while (nfa -> nodes -> list_size != 0) {
			NNode* node = ilib_list_get(nfa -> nodes, 0);
			destory_nnode(node);
			ilib_list_remove(nfa -> nodes, 0, FALSE)
		}
		ilib_list_destroylist(nfa -> nodes, FALSE);
	}
	free(nfa);
}

NNode* new_nnode(int node_type) {
	NNode* node = malloc(sizeof(NNode));
	node -> node_type = node_type;
	node -> path_list = ilib_list_newlist();
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

NPath* new_npath() {
	NPath* path = malloc(sizeof(NPath));
	path -> allowed_char = ilib_list_newlist();
}

void destory_npath(NPath* path) {
	if (path -> allowed_char != NULL) {
		ilib_list_destroylist(path -> allowed_char, FALSE);
	}
	free(path);
}