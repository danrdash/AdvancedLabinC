#ifndef LINKED_LIST
#define  LINKED_LIST
#include <stdbool.h>

typedef struct LinkedList {
	int data;
	struct LinkedList *next;
} LinkedList;

void LinkedList_FreeList(LinkedList* head);
bool LinkedList_ElementNotInTheList(LinkedList* head, int element_to_search);
int LinkedList_LastIndexInList(LinkedList* head);
LinkedList* LinkedList_AddStart(LinkedList* head, int data);
LinkedList* LinkedList_AddEnd(LinkedList* head, int data);
void LinkedList_AddAfterFirstOccurrence(LinkedList* head, int element_to_add, int element_to_search);
void LinkedList_PrintElementIndex(LinkedList* head, int  element_to_search);
LinkedList* LinkedList_DelIndex(LinkedList* head, int elemet_index_to_dell);
void LinkedList_PrintList(LinkedList* head);
#endif 

