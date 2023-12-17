#include "util.h"

//工具函数
//1.隐藏用户输入密码
char* getLine(char* pwd, int len)
{
	int i = 0;
	char ch;
	COORD c;//COORD是Windows API中定义的一种结构，表示一个字符在控制台屏幕上的坐标。
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	fflush(stdin);
	while (i < len - 1)
	{
		if (0 != _kbhit())
		{//检测到有键盘输入
			ch = _getch();//读取键盘输入赋值给ch
			if (ch == '\r') break; //如果是回车键则退出while循环结束密码输入
			if (ch == '\b') //如果输入是退格键
			{
				if (i == 0)//如果退格到头了 蜂鸣警告
				{
					printf("\a");
					continue;
				}
				printf("\b");//退格
				putchar(' ');
				GetConsoleScreenBufferInfo(hConsole, &csbi);//获取控制台坐标信息存到csbi中
				c.X = csbi.dwCursorPosition.X - 1;//退格一次 x坐标左移一位 y坐标不变
				c.Y = csbi.dwCursorPosition.Y;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
				i--;
				continue;
			}
			putchar('*');
			pwd[i] = ch;//存入接收密码的字符数组中
			++i;
		}
		pwd[i] = '\0';
	}
	return pwd;
}
//2.获取输入命令
char get_cmd(char start, char end)
{
	color(4);
	printf("请输入命令:");
	while (1)
	{
		char val = _getch();
		if (val >= start && val <= end)
		{
			printf("%c\n", val);
			return val;
		}
	}
}
//3.一个可以自由选打印颜色的函数
void color(int x) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}
//4.密码加密函数
void encode(char* password)
{
	int i;
	for (i = 0;i < (int)strlen(password);i++)
	{
		if (i <= (int)strlen(password) / 2)
		{
			password[i] = (password[i] + 7);//前半部分密码每个字符anscii码+7
		}
		if (i > (int)strlen(password) / 2) {
			password[i] = (password[i] - 9);//后半部分密码每个字符anscii码-9
		}
	}
	password[i] = '\0';
}
//5.密码解密函数
void decode(char* password)
{
	int i;
	for (i = 0;i < (int)strlen(password);i++)
	{
		if (i <= (int)strlen(password) / 2)
		{
			password[i] = (password[i] - 7);//前半部分密码每个字符anscii码-7
		}
		if (i > (int)strlen(password) / 2)
		{
			password[i] = (password[i] + 9);//后半部分密码每个字符anscii码+9
		}
	}
	password[i] = '\0';
}
//6.输入字符串校验是否为浮点数的合法性
double get_double()
{
	int i = 0;//遍历输入的字符串
	int count = 0;//记录小数点个数
	int flag = 0;//标志用户输入是否为合法的 浮点数，如果不是 重新输入
	char str[20] = { 0 };
	double salary = 0;
	while (1)//合法性校验
	{
		count = 0;
		color(2);
		scanf("%s", str);//用户输入一个字符串  进行浮点数合法性判断
		for (i = 0;i < (int)strlen(str);i++)
		{
			//如果用户输入字符串中字符有一个不是0-9数字或小数点 则输入不合法
			if (str[i] > '9' || str[i] < '.')//anscii 编码 46是'.' 47是'/'接下来为数字0-9
			{//如果用户输入字符串开头或结尾是小数点 则输入有误 
				flag = 0;	break;
			} //如果用户输入字符串开头或结尾是小数点 则输入不合法
			else if (str[0] == '.' || str[strlen(str) - 1] == '.')
			{
				flag = 0;   break;
			}
			else if (str[i] == '/')
			{
				flag = 0;	break;
			}
			else flag = 1;
			if (str[i] == '.')  count++;
		}
		if (flag == 1 && count <= 1)//若小数点超过2个 也不合法
		{
			salary = atof(str);//atof函数把字符串转换成浮点数
			break;
		}
		color(4);  printf("输入不合法！请重新输入\n");
	}
	return  salary;
}
//检测用户输入编号，直至合法为止
int get_int()
{
	int i;
	char str[20] = { 0 };
	int pid;
	int flag = 0;//标志用户输入是否为合法的 浮点数，如果不是 重新输入
	while (1)
	{
		scanf("%s", str);
		for (i = 0;i < (int)strlen(str);i++)
		{
			if (str[i] > '9' || str[i] < '0')
			{
				flag = 0;
				break;
			}
			else flag = 1;
		}
		if (flag == 1)
		{
			pid = atoi(str);//库函数 字符串转int数字
			break;
		}
		color(4);
		printf("输入非法，请重新输入\n");
		color(7);
	}
	return pid;
}
//检测用户输入手机号为数字，直至合法为止
char* get_phoneNum()
{
	int i;
	char str[20];
	int flag = 0;//标志用户输入是否为合法的 浮点数，如果不是 重新输入
	while (1)
	{
		scanf("%s", str);
		for (i = 0;i < (int)strlen(str);i++)
		{
			if (str[i] > '9' || str[i] < '0')
			{
				flag = 0;
				break;
			}
			else flag = 1;
		}
		if (flag == 1) break;
		color(4);
		printf("输入非法，请重新输入\n");
		color(7);
	}
	//str[i] = '\0';
	return str;
}