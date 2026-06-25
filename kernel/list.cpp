#include "list.h"
#include "memory.h"
#include "vga.h"
static ListNode* head = 0;

void list_push(int value)
{
    ListNode* node =
        (ListNode*)kmalloc(sizeof(ListNode));

    node->value = value;
    node->next = 0;

    if(head == 0)
    {
        head = node;
        return;
    }

    ListNode* cur = head;

    while(cur->next)
    {
        cur = cur->next;
    }

    cur->next = node;
}

void list_print()
{
    ListNode* cur = head;

    while(cur)
    {
        print_char((char)cur->value);
        print(" ");

        cur = cur->next;
    }

    print("\n");
}
int list_count()
{
    int count = 0;

    ListNode* cur = head;

    while(cur)
    {
        count++;
        cur = cur->next;
    }

    return count;
}
bool list_find(int value)
{
    ListNode* cur = head;

    while(cur)
    {
        if(cur->value == value)
        {
            return true;
        }

        cur = cur->next;
    }

    return false;
}
void list_clear()
{
    head = 0;
}
