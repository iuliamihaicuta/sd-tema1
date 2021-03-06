// Copyright Mihaicuta Iulia-Andreea-Naomi 314CAb 2021-2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doubly_linked_list.h"

#define uint unsigned int

// allocate memory for a node
dll_node_t*
new_node(uint data_size)
{
	dll_node_t *node = (dll_node_t *)malloc(sizeof(dll_node_t));

	node->data = malloc(data_size);

	node->next = NULL;
	node->prev = NULL;

	return node;
}

// create a doubly linked list
doubly_linked_list_t*
dll_create(uint data_size)
{
	doubly_linked_list_t *list =
		(doubly_linked_list_t *)malloc(sizeof(doubly_linked_list_t));

	list->size = 0;
	list->head = NULL;
	list->data_size = data_size;

	return list;
}

// returns a given node
dll_node_t *
dll_get_nth_node(doubly_linked_list_t *l, uint n)
{
	dll_node_t *tmp = l->head;
	if (n >= l->size)
		n = l->size - 1;

	uint i = 0;
	while(i < n && tmp->next != NULL) {
		tmp = tmp->next;
		++i;
	}

	return tmp;
}

// add a node to the list
void
dll_add_nth_node(doubly_linked_list_t* list, unsigned int n, const void* data)
{
	if ( n > list->size)
		n = list->size;

	// create the new node and save the data
	dll_node_t *node = new_node(list->data_size);
	memcpy(node->data, data, list->data_size);

	if (list->size == 0) {
		list->head = node;
	} else if (n == 0) {
		// set the node as the list->head if n == 0
		node->next = list->head;
		list->head->prev = node;
		list->head = node;
	} else {
		dll_node_t *tmp = dll_get_nth_node(list, n - 1);

		node->next = tmp->next;
		node->prev = tmp;
		if (tmp->next)
			tmp->next->prev = node;
		tmp->next = node;
	}

	(list->size)++;
}

// remove the node from the list
dll_node_t *
dll_remove_nth_node(doubly_linked_list_t* list, unsigned int n)
{
	dll_node_t *node;

	if (!list || !list->head) {
		return NULL;
	}

	/* n >= list->size - 1 inseamna eliminarea nodului de la finalul listei. */
	if (n > list->size - 1) {
		n = list->size - 1;
	}

	node = dll_get_nth_node(list, n);

	if(n == 0) {
		// change the list->head if n == 0
		list->head = node->next;
		if(node->next != NULL)
			node->next->prev = NULL;
	} else {
		if(node->prev != NULL)
			node->prev->next = node->next;
		if(node->next != NULL)
    		node->next->prev = node->prev;
	}

	list->size--;

	return node;
}

// move a node at the end of the list
void
dll_move_last(doubly_linked_list_t* list, uint n)
{
	dll_node_t *node = dll_remove_nth_node(list, n);
	dll_node_t *tail = dll_get_nth_node(list, list->size);

	node->prev = tail;
	tail->next = node;
	node->next = NULL;

	(list->size)++;
}

// free a doubly linked list
void
dll_free_list(doubly_linked_list_t** pp_list)
{
	dll_node_t* node;

	if (!pp_list || !*pp_list) {
		return;
	}

	// remove the nodes and free up the used memory
	while ((*pp_list)->size > 0) {
		node = dll_remove_nth_node(*pp_list, 0);
		if (node != NULL) {
			if(node->data != NULL) {
				free(node->data);
				node->data = NULL;
			}
			free(node);
			node = NULL;
		} else {
			break;
		}
	}

	// free the list
	free(*pp_list);
	*pp_list = NULL;
}

