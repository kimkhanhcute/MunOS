#pragma once

void task_add(const char* name);
void task_list();
int task_count();
void task_clear();
bool task_kill(int id);
void task_schedule();
void task_current();
