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

	ListNode *add_node = malloc(sizeof(ListNode));
	if (add_node == NULL) {
		return -1;
	}

	if (index == 0) {
		add_node -> pre_node = NULL;
		add_node -> next_node = list -> first_node;
		list -> first_node -> pre_node = add_node;
		list -> first_node = add_node;
	} else if (index == list -> list_size) {
		add_node -> pre_node = list -> last_node;
		add_node -> next_node = NULL;
		list -> last_node -> next_node = add_node;
		list -> last_node = add_node;
	} else {
		add_node -> pre_node = list -> first_node;
		add_node -> next_node = list -> first_node ->next_node;
		for (int i = 1; i < index; i ++) {
			add_node -> pre_node = add_node -> next_node;
			add_node -> next_node = add_node -> next_node -> next_node;
		}
		add_node -> pre_node -> next_node = add_node;
		add_node -> next_node -> pre_node = add_node;
	}
	list -> index ++;
	return list -> index;
}