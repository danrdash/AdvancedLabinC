#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Linked_list.h"

LinkedList* CreatNode(int data) 
{
	LinkedList* new_node = malloc(sizeof(LinkedList));
	new_node->data = data;
	new_node->next = NULL;
	return new_node;
}
void LinkedList_FreeList(LinkedList* head) 
{
	LinkedList* next_node;
	while (head != NULL) {
		next_node = head->next;
		free(head);
		head = next_node;
	 }
}

bool LinkedList_ElementNotInTheList(LinkedList* head, int element_to_search)
{
	LinkedList* current_node = head;
	while ((current_node != NULL) && (current_node->data != element_to_search))
		current_node = current_node->next;
	if (current_node == NULL)
		return true;
	return false;
}

int LinkedList_LastIndexInList(LinkedList* head) {
	int last_index = -1;
	while (head != NULL)
	{
		last_index++;
		head = head->next;
	}
	return last_index;
}

LinkedList* LinkedList_AddStart(LinkedList* head, int data)
{
	LinkedList* new_node = CreatNode(data);
	if (head != NULL) 
		new_node->next = head;
	return new_node;
}

LinkedList* LinkedList_AddEnd(LinkedList* head, int data)
{
	LinkedList* new_node = CreatNode(data);
	if (head == NULL) {
		head = new_node;
	}
	else {
		LinkedList* current_node = head;
		while (current_node->next != NULL) {
			current_node = current_node->next;
		}
		current_node->next = new_node;
	}
	return head;
}

void LinkedList_AddAfterFirstOccurrence(LinkedList* head, int element_to_add, int element_to_search)
{
	LinkedList* current_node = head;
	while ((current_node != NULL) && (current_node->data != element_to_search))
		current_node = current_node->next;
	LinkedList* new_node = CreatNode(element_to_add);
	new_node->next = current_node->next;
	current_node->next = new_node;
}

void LinkedList_PrintElementIndex(LinkedList* head, int  element_to_search)
{
	int index_to_print = 0;
	while ((head != NULL) && (head->data != element_to_search)) {
		head = head->next;
		index_to_print++;
	}
	if (head == NULL)
		index_to_print = -1;
	printf("%d\n",index_to_print);   
}

LinkedList* LinkedList_DelIndex(LinkedList* head, int element_index_to_dell)
{
	int node_index = 0;
	LinkedList* previos_node= NULL;
	LinkedList* current_node = head;
	if ((head != NULL) && (node_index == element_index_to_dell)) {
		head = head->next;
		free(current_node);
		return head;
	}
	while ((current_node != NULL) && (node_index != element_index_to_dell)) {
		previos_node = current_node;
		current_node = current_node->next;
		node_index++;
	}
	previos_node->next = current_node->next;
	free(current_node);
	return head;
}

void LinkedList_PrintList(LinkedList* head)
{
	printf("[");
	while (head != NULL)
	{
		printf("%d", head->data);
		if (head->next != NULL)
		{
			printf(", ");
		}
		head = head->next;
	}
	printf("]\n");
}