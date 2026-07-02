#pragma once
enum TaskState
{
    TASK_READY,
    TASK_RUNNING,
    TASK_SLEEPING,
    TASK_TERMINATED,
    TASK_BLOCKED
};

struct Task
{
    int id;
    char name[32];

    TaskState state;

    unsigned int sleep_ticks;

    Task* next;
};
void task_add(const char* name);
void task_list();
int task_count();
void task_clear();
bool task_kill(int id);
void task_schedule();
void task_current();
bool task_sleep(int id, unsigned int ticks);
void task_update_sleep();
