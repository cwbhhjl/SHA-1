#include "stdafx.h"

void listAdd(List list, uint8_t item) {

	if (list->date == NULL)
	{
		list->date = item;
		return;
	}

	while (list->next != NULL)
	{
		list = list->next;
	}

	ListItem temp = (List)malloc(sizeof(ListNode));
	temp->date = item;
	temp->next = NULL;

	list->next = temp;
}