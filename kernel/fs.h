#pragma once

struct File
{
    char name[32];
    char content[256];
    bool used;
    bool is_directory;
};

void fs_init();
bool fs_create(const char* name);
bool fs_delete(const char* name);
bool fs_write(const char* name, const char* content);
bool fs_read(const char* name);
bool fs_append(const char* name, const char* content);
bool fs_rename(const char* oldname, const char* newname);
bool fs_stat(const char* name);
bool fs_copy(const char* src, const char* dst);
bool fs_mkdir(const char* name);
bool fs_rmdir(const char* name);
bool fs_cd(const char* name);
void fs_pwd();
void fs_tree();
void fs_list();
