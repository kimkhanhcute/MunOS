#include "stack.h"
#include "memory.h"
#include "vga.h"

struct StackNode
{
    char value;
    StackNode* next;
};

static StackNode* top = 0;
void stack_push(char value)
{
    StackNode* node =
        (StackNode*)kmalloc(sizeof(StackNode));

    node->value = value;
    node->next = top;

    top = node;
}
char stack_pop()
{
    if(top == 0)
    {
        return 0;
    }

    char value = top->value;

    top = top->next;

    return value;
}
void stack_show()
{
    StackNode* cur = top;

    while(cur)
    {
        print_char(cur->value);
        print(" ");

        cur = cur->next;
    }

    print("\n");
}
int stack_count()
{
    int count = 0;

    StackNode* cur = top;

    while(cur)
    {
        count++;
        cur = cur->next;
    }

    return count;
}
bool stack_empty()
{
    return top == 0;
}
void stack_clear()
{
    top = 0;
}
