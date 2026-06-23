#include "fs.h"
#include "string.h"
#include "vga.h"

File files[32];
char current_directory[32] = "/";
void fs_init()
{
    for(int i = 0; i < 32; i++)
    {
        files[i].used = false;
        files[i].is_directory = false;
    }
}

bool fs_create(const char* name)
{
    for(int i = 0; i < 32; i++)
    {
        if(files[i].used &&
           strcmp(files[i].name, name))
        {
            return false;
        }
    }

    for(int i = 0; i < 32; i++)
    {
        if(!files[i].used)
        {
            int j = 0;

            while(name[j] && j < 31)
            {
                files[i].name[j] = name[j];
                j++;
            }

            files[i].name[j] = 0;
            files[i].content[0] = 0;
            files[i].used = true;

            return true;
        }
    }

    return false;
}

bool fs_delete(const char* name)
{
    for(int i = 0; i < 32; i++)
    {
        if(files[i].used &&
           strcmp(files[i].name, name))
        {
            files[i].used = false;
            return true;
        }
    }

    return false;
}
bool fs_write(const char* name, const char* content)
{
    for(int i = 0; i < 32; i++)
    {
        if(files[i].used &&
           strcmp(files[i].name, name))
        {
            int j = 0;

            while(content[j] && j < 255)
            {
                files[i].content[j] = content[j];
                j++;
            }

            files[i].content[j] = 0;

            return true;
        }
    }

    return false;
}
bool fs_read(const char* name)
{
    for(int i = 0; i < 32; i++)
    {
        if(files[i].used &&
           strcmp(files[i].name, name))
        {
            print(files[i].content);
            print("\n");

            return true;
        }
    }

    return false;
}
bool fs_append(const char* name, const char* content)
{
    for(int i = 0; i < 32; i++)
    {
        if(files[i].used &&
           strcmp(files[i].name, name))
        {
            int len = 0;

            while(files[i].content[len])
                len++;

            int j = 0;

            while(content[j] && len < 255)
            {
                files[i].content[len++] = content[j++];
            }

            files[i].content[len] = 0;

            return true;
        }
    }

    return false;
}
bool fs_rename(const char* oldname, const char* newname)
{
    for(int i = 0; i < 32; i++)
    {
        if(files[i].used &&
           strcmp(files[i].name, oldname))
        {
            int j = 0;

            while(newname[j] && j < 31)
            {
                files[i].name[j] = newname[j];
                j++;
            }

            files[i].name[j] = 0;

            return true;
        }
    }

    return false;
}
bool fs_stat(const char* name)
{
    for(int i = 0; i < 32; i++)
    {
        if(files[i].used &&
           strcmp(files[i].name, name))
        {
            print("Name: ");
            print(files[i].name);
            print("\n");

            int size = 0;

            while(files[i].content[size])
                size++;

            print("Size: ");

            char buf[16];
            int_to_string(size, buf);

            print(buf);
            print(" bytes\n");

            return true;
        }
    }

    return false;
}
bool fs_copy(const char* src, const char* dst)
{
    int src_index = -1;

    for(int i = 0; i < 32; i++)
    {
        if(files[i].used &&
           strcmp(files[i].name, src))
        {
            src_index = i;
            break;
        }
    }

    if(src_index == -1)
        return false;

    for(int i = 0; i < 32; i++)
    {
        if(files[i].used &&
           strcmp(files[i].name, dst))
        {
            return false;
        }
    }

    for(int i = 0; i < 32; i++)
    {
        if(!files[i].used)
        {
            int j = 0;

            while(files[src_index].name[j])
                j++;

            j = 0;

            while(dst[j] && j < 31)
            {
                files[i].name[j] = dst[j];
                j++;
            }

            files[i].name[j] = 0;

            j = 0;

            while(files[src_index].content[j] && j < 255)
            {
                files[i].content[j] =
                    files[src_index].content[j];

                j++;
            }

            files[i].content[j] = 0;

            files[i].used = true;

            return true;
        }
    }

    return false;
}
bool fs_mkdir(const char* name)
{
    for(int i = 0; i < 32; i++)
    {
        if(files[i].used &&
           strcmp(files[i].name, name))
        {
            return false;
        }
    }

    for(int i = 0; i < 32; i++)
    {
        if(!files[i].used)
        {
            int j = 0;

            while(name[j] && j < 31)
            {
                files[i].name[j] = name[j];
                j++;
            }

            files[i].name[j] = 0;

            files[i].content[0] = 0;
            files[i].used = true;
            files[i].is_directory = true;

            return true;
        }
    }

    return false;
}
bool fs_rmdir(const char* name)
{
    for(int i = 0; i < 32; i++)
    {
        if(files[i].used &&
           files[i].is_directory &&
           strcmp(files[i].name, name))
        {
            files[i].used = false;
            return true;
        }
    }

    return false;
}
void fs_tree()
{
    print("/\n");
    
        for(int i = 0; i < 32; i++)
        {
            if(files[i].used)
            {
                print("├── ");
                print(files[i].name);
    
                if(files[i].is_directory)
                {
                    print("/");
                }
    
                print("\n");
            }
        }
}
bool fs_cd(const char* name)
{
    if(strcmp(name, "/"))
    {
        current_directory[0] = '/';
        current_directory[1] = 0;

        return true;
    }

    for(int i = 0; i < 32; i++)
    {
        if(files[i].used &&
           files[i].is_directory &&
           strcmp(files[i].name, name))
        {
            int j = 0;

            while(name[j] && j < 31)
            {
                current_directory[j] = name[j];
                j++;
            }

            current_directory[j] = 0;

            return true;
        }
    }

    return false;
}
bool fs_mv(const char* oldname, const char* newname)
{
    for(int i = 0; i < 32; i++)
    {
        if(files[i].used &&
           strcmp(files[i].name, oldname))
        {
            int j = 0;

            while(newname[j] && j < 31)
            {
                files[i].name[j] = newname[j];
                j++;
            }

            files[i].name[j] = 0;

            return true;
        }
    }

    return false;
}
bool fs_find(const char* name)
{
    for(int i = 0; i < 32; i++)
    {
        if(files[i].used &&
           strcmp(files[i].name, name))
        {
            return true;
        }
    }

    return false;
}
void fs_pwd()
{
    print(current_directory);
    print("\n");
}
void fs_list()
{
    for(int i = 0; i < 32; i++)
    {
        if(files[i].used)
        {
            print(files[i].name);
            print("\n");
        }
    }
}
