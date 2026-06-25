#include "task.h"
#include "memory.h"
#include "string.h"
#include "vga.h"

struct Task
{
    int id;
    char name[32];
    bool running;
    Task* next;
};

static Task* head = 0;
static int next_id = 1;
void task_add(const char* name)
{
    Task* task = (Task*)kmalloc(sizeof(Task));

    task->id = next_id++;
    task->next = 0;
	task->running = false;
    int i = 0;
    while(name[i] && i < 31)
    {
        task->name[i] = name[i];
        i++;
    }

    task->name[i] = 0;

    if(head == 0)
    {
        head = task;
        return;
    }

    Task* cur = head;

    while(cur->next)
    {
        cur = cur->next;
    }

    cur->next = task;
}
void task_list()
{
    Task* cur = head;

    while(cur)
    {
        print_char('0' + cur->id);
        print(" ");

        print(cur->name);
        print(" ");

        if(cur->running)
        {
            print("RUNNING");
        }
        else
        {
            print("READY");
        }

        print("\n");

        cur = cur->next;
    }
}
int task_count()
{
    int count = 0;

    Task* cur = head;

    while(cur)
    {
        count++;
        cur = cur->next;
    }

    return count;
}
void task_clear()
{
    head = 0;
    next_id = 1;
}
bool task_kill(int id)
{
    if(head == 0)
        return false;

    if(head->id == id)
    {
        head = head->next;
        return true;
    }

    Task* cur = head;

    while(cur->next)
    {
        if(cur->next->id == id)
        {
            cur->next = cur->next->next;
            return true;
        }

        cur = cur->next;
    }

    return false;
}
static Task* current_task = 0;

void task_schedule()
{
    if(head == 0)
        return;

    if(current_task == 0)
    {
        current_task = head;
        current_task->running = true;
        return;
    }

    current_task->running = false;

    if(current_task->next)
        current_task = current_task->next;
    else
        current_task = head;

    current_task->running = true;

    print("Running: ");
    print(current_task->name);
    print("\n");
}
void task_current()
{
    if(current_task == 0)
    {
        print("No current task\n");
        return;
    }

    print("Current: ");
    print(current_task->name);
    print("\n");
}
