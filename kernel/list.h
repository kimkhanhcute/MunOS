#pragma once

struct ListNode
{
    int value;
    ListNode* next;
};

void list_push(int value);
void list_print();
int list_count();
void list_clear();
bool list_find(int value);
