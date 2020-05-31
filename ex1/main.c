#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "Linked_list.h"

#define LINE_SIZE 100
#define INITIAL_COMMAND 0
#define ERROR 1
#define ADD_END 2
#define ADD_START 3
#define ADD_AFTER 4
#define INDEX 5
#define DEL 6
#define PRINT 7
#define EXIT 8


typedef struct LinkedListCommandArguments {
	int  command;
	int	 argument_1;
	int  argument_2;
}LinkedListCommandArguments;

void convert_string_to_lowercase(char* string)
{
	int i = 0;
	for (i = 0; string[i] != '\0'; i++)
	{
		string[i] = tolower(string[i]);
		if (string[i] == '\n')
			string[i] = ' ';
	}
}

int Command_type_to_integer(char* command_pointer)
{
	if (strcmp(command_pointer, "add_end") == 0)
		return ADD_END;
	if (strcmp(command_pointer, "add_start") == 0)
		return ADD_START;
	if (strcmp(command_pointer, "add_after") == 0)
		return ADD_AFTER;
	if (strcmp(command_pointer, "index") == 0)
		return INDEX;
	if (strcmp(command_pointer, "del") == 0)
		return DEL;
	if (strcmp(command_pointer, "print") == 0)
		return PRINT;
	if (strcmp(command_pointer, "exit") == 0)
		return EXIT;
	return 0;
}
void insert_command_arguments(char* new_line, LinkedListCommandArguments* linked_list_command_arguments)
{
	char delimiter[2] = " ";
	char *token = NULL;
	token = strtok(new_line, delimiter);
	linked_list_command_arguments->command = Command_type_to_integer(token);
	token = strtok(NULL, delimiter);
	if (token == NULL)
		return;
	linked_list_command_arguments->argument_1 = atoi(token);
	token = strtok(NULL, delimiter);
	if (token == NULL)
		return;
	linked_list_command_arguments->argument_2 = atoi(token);
}

void CrashIfElementNotInLinkedList(LinkedList* head , int element_to_search)
{
	if (LinkedList_ElementNotInTheList(head,element_to_search)) {
		printf("ERROR: Element %d is not in the linked list. Exitting the program.", element_to_search);
		if (head != NULL)
			LinkedList_FreeList(head);
		exit(1);
	}
	return;
}

void CrashIfIndexNotInLinkedList(LinkedList* head, int element_index_to_del)
{
	if (element_index_to_del > LinkedList_LastIndexInList(head)) {
		printf("ERROR: Index %d is not in the linked list. Exitting the program.", element_index_to_del);
		if (head != NULL)
			LinkedList_FreeList(head);
		exit(1);
	}
}

LinkedList* compute_linked_list_command(LinkedList* head, LinkedListCommandArguments* linked_list_command_arguments) 
{
	switch (linked_list_command_arguments->command) {
		case ADD_END:
			head = LinkedList_AddEnd(head, linked_list_command_arguments->argument_1);
			break;
		case ADD_START:
			head = LinkedList_AddStart(head, linked_list_command_arguments->argument_1);
			break;
		case ADD_AFTER:
			CrashIfElementNotInLinkedList(head, linked_list_command_arguments->argument_2);
			LinkedList_AddAfterFirstOccurrence(head, 
linked_list_command_arguments->argument_1,linked_list_command_arguments->argument_2);
			break;
		case INDEX:
			LinkedList_PrintElementIndex(head, linked_list_command_arguments->argument_1);
			break;
		case DEL:
			CrashIfIndexNotInLinkedList(head, linked_list_command_arguments->argument_1);
			head = LinkedList_DelIndex(head, linked_list_command_arguments->argument_1);
			break;
		case PRINT:
			LinkedList_PrintList(head);
			break;
		case EXIT:
			LinkedList_FreeList(head);
			exit(0);
	}
	return head;
}

int main()
{
	char new_line[LINE_SIZE + 1];
	LinkedList* head = NULL;
	LinkedListCommandArguments linked_list_command_arguments, *linked_list_command_arguments_pointer;
	linked_list_command_arguments_pointer = &linked_list_command_arguments;
	linked_list_command_arguments_pointer->command = INITIAL_COMMAND;
	while (linked_list_command_arguments_pointer->command != EXIT)
	{
		fgets(new_line, LINE_SIZE, stdin);
		convert_string_to_lowercase(new_line);  //Also replace '\n' with ' '.
		insert_command_arguments(new_line, linked_list_command_arguments_pointer);
		head = compute_linked_list_command(head, linked_list_command_arguments_pointer);
	}
	return 0;
}
