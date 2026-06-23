#include "command.h"

Command commands[] =
{
    {"help",   "help [command]",      "Show help"},
    {"time",   "time",                "Show current time"},
    {"date",   "date",                "Show current date"},
    {"now",    "now",                 "Show date and time"},
    {"touch",  "touch <file>",        "Create file"},
    {"rm",     "rm <file>",           "Remove file"},
    {"cat",    "cat <file>",          "Show file content"},
    {"write",  "write <file>",        "Write file"},
    {"mkdir",  "mkdir <dir>",         "Create directory"},
    {"rmdir",  "rmdir <dir>",         "Remove directory"},
    {"cd",     "cd <dir>",            "Change directory"},
    {"pwd",    "pwd",                 "Print current directory"},
    {"tree",   "tree",                "Show filesystem tree"},
    {"cp",     "cp <src> <dst>",      "Copy file"},
    {"mv",     "mv <old> <new>",      "Move or rename file"},
};
const int command_count = sizeof(commands) / sizeof(commands[0]);
