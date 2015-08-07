#include "myconst.h"

typedef struct _listnode{
	struct _listnode *pre_node;
	struct _listnode *next_node;
	void *content;
} ListNode;

typedef struct _list{
	ListNode *first_node;
	ListNode *last_node;
	int list_size;
} List;

List* ilib_list_newlist(){
	List* list = malloc(sizeof(List));
	list -> list_size = 0;
	list -> first_node = NULL;
	list -> last_node = NULL;
	return list;
}

int ilib_list_add(List *list, void *node, int index) {
	if (list == NULL || node == NULL || index > list -> list_size) {
		return -1;
	}

	ListNode *add_node = malloc(sizeof(ListNode));
	if (add_node == NULL) {
		return -1;
	}

	add_node -> content = node;

	if (list -> list_size == 0) {
		list -> first_node = add_node;
		list -> last_node = add_node;
		list -> list_size++;
		return list -> list_size;
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
	list -> list_size ++;
	return list -> list_size;
} 

void* ilib_list_get(List * list, int index) {
	if (list == NULL || index >= (list -> list_size) || index < 0) {
		return NULL;
	}

	ListNode *node = list -> first_node;
	for (int i = 0; i < index; i++) {
		node = node -> next_node;
	}

	return node -> content;
}