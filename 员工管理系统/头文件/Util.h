#ifndef UTIL_H
#define UTIL_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>		//处理密码输入函数头文件
#include <Windows.h>	//修改控制台窗口颜色、控制输入退格时光标左移
//工具函数
void color(int x);//打印颜色修改 0 黑色 1蓝色 2绿色 3青色 4红色 5紫色 6黄色 7白色 8灰白
char* getLine(char* buf, int len);      //输入密码转换成*号 
char get_cmd(char start, char end);     // 控制台提示输入命令 业务逻辑控制
void encode(char* password);    //密码加密函数
void decode(char* password);    //密码解密函数
double get_double(void);        //校验用户输入直到为合法浮点数
int get_int(void);				//校验用户输入直到为合法整数
char* get_phoneNum(void);
#endif