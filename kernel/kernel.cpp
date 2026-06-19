#include "vga.h"
#include "keyboard.h"
#include "string.h"
#include "io.h"
#include "rtc.h"
#include "idt.h"
#include "irq.h"

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

extern "C" void kernel_main()
{
    clear();
	idt_init();
	pic_remap();
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
