#pragma once

struct ListNode {
	uint8_t date;
	ListNode* next;
};

typedef struct ListNode ListNode;

typedef ListNode* List;
typedef ListNode* ListItem;

void listAdd(List list, uint8_t item);