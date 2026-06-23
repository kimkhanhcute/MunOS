#pragma once

struct Command
{
    const char* name;
    const char* usage;
    const char* description;
};

extern Command commands[];
extern const int command_count;
