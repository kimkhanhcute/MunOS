#include "vga.h"
#include "keyboard.h"
#include "string.h"
#include "io.h"
#include "rtc.h"
#include "idt.h"
#include "irq.h"
#include "fs.h"

char history[32][128];
int history_count = 0;
extern "C" void isr0_handler()
{
    print("\n");
    print("EXCEPTION: DIVIDE BY ZERO\n");

    while(true)
    {
        asm volatile("hlt");
    }
}
extern "C" void irq0_handler()
{
    static int ticks = 0;
    ticks++;

    if(ticks % 100 == 0)
    {
        print(".");
    }
}
void save_history(const char* cmd)
{
    if(cmd[0] == 0)
        return;

    if(history_count >= 32)
        return;

    int i = 0;

    while(cmd[i])
    {
        history[history_count][i] = cmd[i];
        i++;
    }

    history[history_count][i] = 0;

    history_count++;
}

void print_int(int value)
{
    char buffer[16];
    int_to_string(value, buffer);
    print(buffer);
}

void print_2digit(int value)
{
    if(value < 10)
        print("0");

    print_int(value);
}

void cmd_banner()
{
    print(" __  __             ____   _____\n");
    print("|  \\/  |           / __ \\ / ____|\n");
    print("| \\  / |_   _ _ __| |  | | (___\n");
    print("| |\\/| | | | | '__| |  | |\\___ \\\n");
    print("| |  | | |_| | |  | |__| |____) |\n");
    print("|_|  |_|\\__,_|_|   \\____/|_____/\n");
}

void cmd_history()
{
    for(int i = 0; i < history_count; i++)
    {
        print("[");

        char num[3];

        num[0] = '0' + ((i + 1) / 10);
        num[1] = '0' + ((i + 1) % 10);
        num[2] = 0;

        if(i + 1 < 10)
        {
            print(num + 1);
        }
        else
        {
            print(num);
        }

        print("] ");
        print(history[i]);
        print("\n");
    }
}

void cmd_time()
{
    print_2digit(rtc_get_hour());
    print(":");
    print_2digit(rtc_get_minute());
    print(":");
    print_2digit(rtc_get_second());
    print("\n");
}

void cmd_date()
{
    print_2digit(rtc_get_day());
    print("/");
    print_2digit(rtc_get_month());
    print("/");
    print_int(rtc_get_year());
    print("\n");
}
void cmd_neofetch() {
	print("OS: MunOS\n");
	print("Version: v0.8\n");
	print("Architecture: x86\n");
	print("Kernel: Monolithic\n");
	print("Shell: MunShell\n");
}
void cmd_sysinfo() {
	print("OS: MunOS\n");
	print("Version: v0.8\n");
	print("Architecture: x86\n");
	print("Kernel: Monolithic\n");
	print("Shell: MunShell\n");
}
extern "C" void kernel_main()
{
    clear();
    fs_init();
	idt_init();
	pic_remap();
	asm volatile("sti");
	print("IDT loaded\n");
	print("PIC remapped\n");
    print("====================\n");
    print("      MunOS\n");
    print("====================\n\n");

    char buffer[128];
    int len = 0;

    print("mun> ");

    while(true)
    {
        char c = keyboard_getchar();

        if(c == '\b')
        {
            if(len > 0)
            {
                len--;
                print_char('\b');
            }

            continue;
        }

        if(c == '\n')
        {
            buffer[len] = 0;

            save_history(buffer);

            print("\n");

            if(strcmp(buffer, "help"))
            {
                print("Commands:\n");
                print("help\n");
                print("about\n");
                print("clear\n");
                print("echo\n");
                print("version\n");
                print("banner\n");
                print("history\n");
                print("time\n");
                print("date\n");
                print("reboot\n");
                print("shutdown\n");
                print("now\n");
                print("neofetch\n");
                print("sysinfo\n");
                print("uname or uname -a\n");
                print("calc\nwhoami\nhostname\npwd\n");
                print("fortune\njoke\nquote");
            }
            else if(strcmp(buffer, "about"))
            {
                print("MunOS Hobby Operating System\n");
                print("Created by Duc\n");
            }
            else if(strcmp(buffer, "version"))
            {
                print("MunOS v0.7\n");
                print("Architecture: x86\n");
                print("Kernel: Monolithic\n");
            }
            else if(strcmp(buffer, "banner"))
            {
                cmd_banner();
            }
            else if(strcmp(buffer, "history"))
            {
                cmd_history();
            }
            else if(strcmp(buffer, "time"))
            {
                cmd_time();
            }
            else if(strcmp(buffer, "date"))
            {
                cmd_date();
            }
            else if(strcmp(buffer, "clear"))
            {
                clear();
            }
            else if(strcmp(buffer, "reboot"))
            {
                print("Rebooting...\n");

                outb(0x64, 0xFE);

                while(true)
                {
                    asm volatile("hlt");
                }
            }
            else if(strcmp(buffer, "shutdown"))
            {
                print("Shutting down...\n");

                outw(0x604, 0x2000);

                while(true)
                {
                    asm volatile("hlt");
                }
            }
            else if(starts_with(buffer, "echo "))
            {
                print(buffer + 5);
                print("\n");
            }
            else if (strcmp(buffer, "now")) {
            	cmd_date();
            	print(" ");
            	cmd_time();
            }
            else if (strcmp(buffer, "neofetch")) {
            	cmd_banner();
            	print("\n");
            	cmd_neofetch();
            }
            else if (strcmp(buffer, "sysinfo")) {
            	cmd_sysinfo();
            }
            else if (strcmp(buffer, "uname")) {
				print("MunOS\n");
            }
            else if (strcmp(buffer, "uname -a")) {
            	print("MunOS v0.8 x86\n");
            }
            //else if (strcmp(buffer, "calc")) {
			//	int a = read_int();
			//	char op = keyboard_getchar();
			//	int b = read_int();
				
			//	int result = 0;
				
			//	if(op == '+')
			//	    result = a + b;
			//	else if(op == '-')
			//	    result = a - b;
			//	else if(op == '*')
			//	    result = a * b;
			//	else if(op == '/')
			//	    result = a / b;
				
			//	print_int(result);
			//	print("\n");
            //}
            else if (strcmp(buffer, "whoami")) {
            	print("root\n");
            }
            else if (strcmp(buffer, "whoami")) {
                print("MunOS-PC\n");
            }
            else if (strcmp(buffer, "pwd")) {
                print("/home/nguyenduc/MunOS");
            }
             else if (strcmp(buffer, "fortune")) {
                print("keep coding\n");
            }
             else if (strcmp(buffer, "joke")) {
                print("are you gay?\n");
            }
             else if (strcmp(buffer, "quote")) {
                print("be quote\n");
            }
            else if(starts_with(buffer, "touch "))
            {
                if(fs_create(buffer + 6))
                {
                    print("File created\n");
                }
                else
                {
                    print("Cannot create file\n");
                }
            }
            else if(strcmp(buffer, "ls"))
            {
                fs_list();
            }
            else if(starts_with(buffer, "rm "))
            {
                if(fs_delete(buffer + 3))
                {
                    print("File removed\n");
                }
                else
                {
                    print("File not found\n");
                }
            }
            else if(starts_with(buffer, "cat "))
            {
                if(!fs_read(buffer + 4))
                {
                    print("File not found\n");
                }
            }
            else if(starts_with(buffer, "write "))
            {
                char* p = buffer + 6;
            
                while(*p && *p != ' ')
                    p++;
            
                if(*p == 0)
                {
                    print("Usage: write <file> <text>\n");
                }
                else
                {
                    *p = 0;
            
                    const char* filename = buffer + 6;
                    const char* content = p + 1;
            
                    if(fs_write(filename, content))
                    {
                        print("Written\n");
                    }
                    else
                    {
                        print("File not found\n");
                    }
                }
            }
            else if(starts_with(buffer, "append "))
            {
                char* p = buffer + 7;
            
                while(*p && *p != ' ')
                    p++;
            
                if(*p == 0)
                {
                    print("Usage: append <file> <text>\n");
                }
                else
                {
                    *p = 0;
            
                    if(fs_append(buffer + 7, p + 1))
                        print("Appended\n");
                    else
                        print("File not found\n");
                }
            }
            else if(starts_with(buffer, "rename "))
            {
                char* p = buffer + 7;
            
                while(*p && *p != ' ')
                    p++;
            
                if(*p == 0)
                {
                    print("Usage: rename <old> <new>\n");
                }
                else
                {
                    *p = 0;
            
                    if(fs_rename(buffer + 7, p + 1))
                        print("Renamed\n");
                    else
                        print("File not found\n");
                }
            }
            else if(starts_with(buffer, "stat "))
            {
                if(!fs_stat(buffer + 5))
                {
                    print("File not found\n");
                }
            }
            else if(starts_with(buffer, "cp "))
            {
                char* p = buffer + 3;
            
                while(*p && *p != ' ')
                    p++;
            
                if(*p == 0)
                {
                    print("Usage: cp <src> <dst>\n");
                }
                else
                {
                    *p = 0;
            
                    const char* src = buffer + 3;
                    const char* dst = p + 1;
            
                    if(fs_copy(src, dst))
                    {
                        print("Copied\n");
                    }
                    else
                    {
                        print("Copy failed\n");
                    }
                }
            }
            else if(strcmp(buffer, "tree"))
            {
                fs_tree();
            }
            else if(starts_with(buffer, "mkdir "))
            {
                if(fs_mkdir(buffer + 6))
                {
                    print("Directory created\n");
                }
                else
                {
                    print("Cannot create directory\n");
                }
            }
            else if(starts_with(buffer, "rmdir "))
            {
                if(fs_rmdir(buffer + 6))
                {
                    print("Directory removed\n");
                }
                else
                {
                    print("Directory not found\n");
                }
            }
            else if(len != 0)
            {
                print("Unknown command\n");
            }
			
            len = 0;

            print("\nmun> ");
        }
        else
        {
            if(len < 127)
            {
                buffer[len++] = c;
                print_char(c);
            }
        }
    }
}
