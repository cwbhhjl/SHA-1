#pragma once

struct ListNode {
	uint8_t date;
	ListNode* next;
};//��Ҫ���ö���

typedef struct ListNode ListNode;

typedef ListNode* List;
typedef ListNode* ListItem;

void listAdd(List list, uint8_t item);