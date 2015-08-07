#include "myconst.h"

typedef struct _list{
	ListNode *first_node;
	ListNode *last_node;
	int list_size;
} List;

typedef struct _listnode{
	ListNode *pre_node;
	ListNode *next_node;
	void *content;
} ListNode;

int ilib_list_add(List *list, void *node, void index) {
	if (list == NULL || node == NULL || index > list -> list_size) {
		return -1;
	}

	ListNode *list_node = malloc(sizeof(ListNode));
	if (list_node == NULL) {
		return -1;
	}

	if (index == 0) {
		
	} else if (index == list -> list_size) {

	} else {
		
	}
}