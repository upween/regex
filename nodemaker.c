#include "myconst.h"
#include "strctr.c"

#define START 0
#define MIDDLE 1
#define END 2

typedef struct _nfa_node{
	int node_type;
	List *path_list;
} NNode;

typedef struct _nfa_path{
	NNode *target_node;
	List *allowed_char;
} NPath;