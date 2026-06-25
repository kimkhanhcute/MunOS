#include "history.h"
#include "memory.h"
#include "string.h"
#include "vga.h"

struct HistoryNode
{
    char command[64];
    HistoryNode* next;
};

static HistoryNode* head = 0;
void history_add(const char* cmd)
{
    HistoryNode* node =
        (HistoryNode*)kmalloc(sizeof(HistoryNode));

    int i = 0;

    while(cmd[i] && i < 63)
    {
        node->command[i] = cmd[i];
        i++;
    }

    node->command[i] = '\0';
    node->next = 0;

    if(head == 0)
    {
        head = node;
        return;
    }

    HistoryNode* cur = head;

    while(cur->next)
    {
        cur = cur->next;
    }

    cur->next = node;
}
void history_show()
{
    HistoryNode* cur = head;

    while(cur)
    {
        print(cur->command);
        print("\n");

        cur = cur->next;
    }
}
int history_get_count()
{
    int count = 0;

    HistoryNode* cur = head;

    while(cur)
    {
        count++;
        cur = cur->next;
    }

    return count;
}
void history_clear()
{
    head = 0;
}
