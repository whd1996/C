#include "util.h"

//���ߺ���
//1.�����û���������
char* getLine(char* pwd, int len)
{
	int i = 0;
	char ch;
	COORD c;//COORD��Windows API�ж����һ�ֽṹ����ʾһ���ַ��ڿ���̨��Ļ�ϵ����ꡣ
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	fflush(stdin);
	while (i < len - 1)
	{
		if (0 != _kbhit())
		{//��⵽�м�������
			ch = _getch();//��ȡ�������븳ֵ��ch
			if (ch == '\r') break; //����ǻس������˳�whileѭ��������������
			if (ch == '\b') //����������˸��
			{
				if (i == 0)//����˸�ͷ�� ��������
				{
					printf("\a");
					continue;
				}
				printf("\b");//�˸�
				putchar(' ');
				GetConsoleScreenBufferInfo(hConsole, &csbi);//��ȡ����̨������Ϣ�浽csbi��
				c.X = csbi.dwCursorPosition.X - 1;//�˸�һ�� x��������һλ y���겻��
				c.Y = csbi.dwCursorPosition.Y;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
				i--;
				continue;
			}
			putchar('*');
			pwd[i] = ch;//�������������ַ�������
			++i;
		}
		pwd[i] = '\0';
	}
	return pwd;
}
//2.��ȡ��������
char get_cmd(char start, char end)
{
	color(4);
	printf("����������:");
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
//3.һ����������ѡ��ӡ��ɫ�ĺ���
void color(int x) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}
//4.������ܺ���
void encode(char* password)
{
	int i;
	for (i = 0;i < (int)strlen(password);i++)
	{
		if (i <= (int)strlen(password) / 2)
		{
			password[i] = (password[i] + 7);//ǰ�벿������ÿ���ַ�anscii��+7
		}
		if (i > (int)strlen(password) / 2) {
			password[i] = (password[i] - 9);//��벿������ÿ���ַ�anscii��-9
		}
	}
	password[i] = '\0';
}
//5.������ܺ���
void decode(char* password)
{
	int i;
	for (i = 0;i < (int)strlen(password);i++)
	{
		if (i <= (int)strlen(password) / 2)
		{
			password[i] = (password[i] - 7);//ǰ�벿������ÿ���ַ�anscii��-7
		}
		if (i > (int)strlen(password) / 2)
		{
			password[i] = (password[i] + 9);//��벿������ÿ���ַ�anscii��+9
		}
	}
	password[i] = '\0';
}
//6.�����ַ���У���Ƿ�Ϊ�������ĺϷ���
double get_double()
{
	int i = 0;//����������ַ���
	int count = 0;//��¼С�������
	int flag = 0;//��־�û������Ƿ�Ϊ�Ϸ��� ��������������� ��������
	char str[20] = { 0 };
	double salary = 0;
	while (1)//�Ϸ���У��
	{
		count = 0;
		color(2);
		scanf("%s", str);//�û�����һ���ַ���  ���и������Ϸ����ж�
		for (i = 0;i < (int)strlen(str);i++)
		{
			//����û������ַ������ַ���һ������0-9���ֻ�С���� �����벻�Ϸ�
			if (str[i] > '9' || str[i] < '.')//anscii ���� 46��'.' 47��'/'������Ϊ����0-9
			{//����û������ַ�����ͷ���β��С���� ���������� 
				flag = 0;	break;
			} //����û������ַ�����ͷ���β��С���� �����벻�Ϸ�
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
		if (flag == 1 && count <= 1)//��С���㳬��2�� Ҳ���Ϸ�
		{
			salary = atof(str);//atof�������ַ���ת���ɸ�����
			break;
		}
		color(4);  printf("���벻�Ϸ�������������\n");
	}
	return  salary;
}
//����û������ţ�ֱ���Ϸ�Ϊֹ
int get_int()
{
	int i;
	char str[20] = { 0 };
	int pid;
	int flag = 0;//��־�û������Ƿ�Ϊ�Ϸ��� ��������������� ��������
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
			pid = atoi(str);//�⺯�� �ַ���תint����
			break;
		}
		color(4);
		printf("����Ƿ�������������\n");
		color(7);
	}
	return pid;
}
//����û������ֻ���Ϊ���֣�ֱ���Ϸ�Ϊֹ
char* get_phoneNum()
{
	int i;
	char str[20];
	int flag = 0;//��־�û������Ƿ�Ϊ�Ϸ��� ��������������� ��������
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
		printf("����Ƿ�������������\n");
		color(7);
	}
	//str[i] = '\0';
	return str;
}