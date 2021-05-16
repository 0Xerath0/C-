/*
 * @Author: your name
 * @Date: 2020-09-26 12:39:18
 * @LastEditTime: 2020-09-30 13:01:06
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \undefinede:\Code_Test\Banner\bannner.c
 */

#include<stdio.h>
#include<string.h>
#include<windows.h>
int banner_length;
#define bannner_increment 1

#define print_length 20
char x1[]=" _       __     __                             __________    _______________________   __  __                 _ __        __    __  ___                                                  __    _____            __                      ";
char x2[]="| |     / /__  / /________  ____ ___  ___     /_  __/ __ \\  / ____/ ____/ ___/_  __/  / / / /___  _________  (_) /_____ _/ /   /  |/  /___ _____  ____ _____ ____  ____ ___  ___  ____  / /_  / ___/__  _______/ /____  ____ ___       ";
char x3[]="| | /| / / _ \\/ / ___/ __ \\/ __ `__ \\/ _ \\     / / / / / / / /   / /    \\__ \\ / /    / /_/ / __ \\/ ___/ __ \\/ / __/ __ `/ /   / /|_/ / __ `/ __ \\/ __ `/ __ `/ _ \\/ __ `__ \\/ _ \\/ __ \\/ __/  \\__ \\/ / / / ___/ __/ _ \\/ __ `__ \\      ";
char x4[]="| |/ |/ /  __/ / /__/ /_/ / / / / / /  __/    / / / /_/ / / /___/ /___ ___/ // /    / __  / /_/ (__  ) /_/ / / /_/ /_/ / /   / /  / / /_/ / / / / /_/ / /_/ /  __/ / / / / /  __/ / / / /_   ___/ / /_/ (__  ) /_/  __/ / / / / /       ";
char x5[]="|__/|__/\\___/_/\\___/\\____/_/ /_/ /_/\\___/    /_/  \\____/  \\____/\\____//____//_/    /_/ /_/\\____/____/ .___/_/\\__/\\__,_/_/   /_/  /_/\\__,_/_/ /_/\\__,_/\\__, /\\___/_/ /_/ /_/\\___/_/ /_/\\__/  /____/\\__, /____/\\__/\\___/_/ /_/ /_/         ";
char x6[]="                                                                                                   /_/                                               /____/                                      /____/                                 ";
char* banner[6]={x1,x2,x3,x4,x5,x6};

HANDLE console_buffer1, console_buffer2;
COORD coord = { 0,0 };
//双缓冲区

#define console_buffer_height 30
#define console_buffer_width 120
DWORD bytes = 0;
char data[console_buffer_height][console_buffer_width];


void PrintInLength(char* s, int start, int length);
void ShowBanner();

int main(){

    //创建新的控制台缓冲区
    console_buffer1 = CreateConsoleScreenBuffer(
        GENERIC_WRITE,//定义进程可以往缓冲区写数据
        FILE_SHARE_WRITE,//定义缓冲区可共享写权限
        NULL,
        CONSOLE_TEXTMODE_BUFFER,
        NULL
    );
    console_buffer2 = CreateConsoleScreenBuffer(
        GENERIC_WRITE,//定义进程可以往缓冲区写数据
        FILE_SHARE_WRITE,//定义缓冲区可共享写权限
        NULL,
        CONSOLE_TEXTMODE_BUFFER,
        NULL
    );
    //隐藏两个缓冲区的光标
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible = 0;
    cci.dwSize = 1;
    SetConsoleCursorInfo(console_buffer2, &cci);
    SetConsoleCursorInfo(console_buffer1, &cci);
    banner_length=strlen(banner[1]);
    /*char a;
    int start=0;
    while(start<banner_length-5){
        for(int i=0;i<7;i++){
                move(0,i);
                printf("                                                                                                    ");
        }
        move(0,0);
        for(int i=0;i<6;i++){
            PrintInLength(banner[i],start,100);
            printf("\n");
        }
        Sleep(30);
        //system("pause");
        start=(start+5)%banner_length;
    }*/
    ShowBanner();

    CloseHandle(console_buffer1);
    CloseHandle(console_buffer2);
    system("pause");

    return 0;


}

void PrintInLength( char* s, int start, int length){
    for(int i=0;i<length;i++){
        printf ("%c",s[(start+i)%banner_length]);
    }
}

void ShowBanner()
{
    int i, j;
    int start=0;
    int l=strlen(banner[0]);
    for(i=0;i<console_buffer_height;i++){
        for(j=0;j<console_buffer_width;j++){
            data[i][j]=32;//32为空格
        }
    }
    while (start<l+1)
    {
        for (i = 10; i < 16; i++)
        {
            for (j = 10; j < console_buffer_width-10; j++)
            {
                data[i][j]=banner[i-10][(start+j)%l];
                //data[i][j]='*';          
            }
        }
        start+=bannner_increment;
        for (i = 0; i < console_buffer_height; i++)
        {
            coord.Y = i;
            WriteConsoleOutputCharacterA(console_buffer2, data[i], console_buffer_width, coord, &bytes);
        }
        //设置新的缓冲区为活动显示缓冲
        SetConsoleActiveScreenBuffer(console_buffer1);
        Sleep(66);
        for (i = 10; i < 16; i++)
        {
            for (j = 10; j < console_buffer_width-10; j++)
            {
                data[i][j] = banner[i-10][(start+j)%l];
                //data[i][j]='-';
            }
        }
        start+=bannner_increment;
        for (i = 0; i < console_buffer_height; i++)
        {
            coord.Y = i;
            WriteConsoleOutputCharacterA(console_buffer1, data[i], console_buffer_width, coord, &bytes);
        }
        //设置新的缓冲区为活动显示缓冲
        SetConsoleActiveScreenBuffer(console_buffer2);
        Sleep(66);
        }
    

}