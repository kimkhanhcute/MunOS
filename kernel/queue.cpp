#include "queue.h"
#include "memory.h"
#include "vga.h"

struct QueueNode
{
    char value;
    QueueNode* next;
};

static QueueNode* front = 0;
static QueueNode* rear  = 0;
void queue_push(char value)
{
    QueueNode* node =
        (QueueNode*)kmalloc(sizeof(QueueNode));

    node->value = value;
    node->next = 0;

    if(rear == 0)
    {
        front = node;
        rear = node;
        return;
    }

    rear->next = node;
    rear = node;
}
char queue_pop()
{
    if(front == 0)
    {
        return 0;
    }

    char value = front->value;

    front = front->next;

    if(front == 0)
    {
        rear = 0;
    }

    return value;
}
void queue_show()
{
    QueueNode* cur = front;

    while(cur)
    {
        print_char(cur->value);
        print(" ");

        cur = cur->next;
    }

    print("\n");
}
int queue_count()
{
    int count = 0;

    QueueNode* cur = front;

    while(cur)
    {
        count++;
        cur = cur->next;
    }

    return count;
}
bool queue_empty()
{
    return front == 0;
}
void queue_clear()
{
    front = 0;
    rear = 0;
}
