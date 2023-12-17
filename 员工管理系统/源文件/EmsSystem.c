#include "EmsSystem.h"

// 系统初始化
void initSystem(void)
{
	//创建链表存储数据
	Emp = createEmployeeList();
	Dep = createDepartmentList();
	color(3);
	printf("系统运行中...\n");
}
// 系统开始运行
void startSystem(void)
{
	// 进入系统的业务流程控制
	while (1)
	{
		menu();
		switch (get_cmd('0', '6')) // 获取键盘输入
		{
		case '1': userLogin(); putchar('\n');color(5);system("pause");break;
		case '2': showAllInfo();putchar('\n');color(5);system("pause"); break;
		case '3': addEmployee(); putchar('\n');color(5);system("pause");break;
		case '4': updateEmployee();	putchar('\n');color(5);system("pause"); break;
		case '5': deleteEmployee(); putchar('\n');color(5);system("pause");break;
		case '6': userLogout();putchar('\n');color(5);system("pause"); break;
		case '0': return;
		}
	}
}
// 系统结束
void exitSystem()
{
	EmployeeList* emp = Emp;
	DepartmentList* dep = Dep;
	// 以只写方式打开文件employee.txt，文件存在则把内容清空。
	FILE* efwp = fopen("../员工管理系统/资源文件/employee.txt", "w");
	// 以只写方式打开文件department.txt，文件存在则把内容清空。
	FILE* dfwp = fopen("../员工管理系统/资源文件/department.txt", "w");
	if (online == 1)//总经理在线时 可排序保存所有数据
	{
		color(3);
		printf("1.排序保存退出\n0.直接退出\n");
		switch (get_cmd('0', '1'))
		{
		case '1':employeesSort();//排序
			showAllEmployeesInfo();//打印排序结果
			break;
		case '0':break;
		}
	}
	printf("数据录入:\n");

	color(3);
	printf("员工信息写入文件 employee.txt\n");
	printf("员工信息写入文件中...\n");
	while (emp != NULL)
	{
		int num = 0;
		if (strlen(emp->employee.name) != 0)
		{
			num = fprintf(efwp, "%d\t%s\t%s\t%s\t%-11s\t%.2lf\t  %s\t%d\t%s\n",
				emp->employee.pid, emp->employee.password, emp->employee.name, emp->employee.address, emp->employee.phonenum,
				emp->employee.salary, emp->employee.department, emp->employee.authority, emp->employee.position);
		}
		emp = emp->next;
	}
	printf("员工信息写入文件成功!\n");
	printf("部门信息写入文件 department.txt\n");
	printf("部门信息写入文件中...\n");
	while (dep != NULL)
	{
		int num = 0;
		if (strlen(dep->department.dname) != 0)
		{
			num = fprintf(dfwp, "%s \t%s \t%d \t%.2lf\n", dep->department.dname, dep->department.mname,
				dep->department.dnum, dep->department.sumsalary);
		}
		dep = dep->next;
	}
	printf("部门信息写入文件成功!\n");
	// 释放内存、保存数据
	free(Emp);
	free(Dep);
	color(2);
	printf("程序退出...\n");
	color(7);
}
// 生成主菜单
void menu(void)
{   //color:  0 黑色 1蓝色 2绿色 3青色 4红色 5紫色 6黄色 7白色 8灰白
	color(2);
	system("cls");
	printf("\n");
	printf("********************************\n");
	printf("|                              |\n");
	printf("|     员工雇佣情况管理系统     |\n\n");
	printf("*        1.登录                *\n");
	printf("|        2.查询                |\n");
	printf("|        3.新增                |\n");
	printf("|        4.修改                |\n");
	printf("*        5.删除                *\n");
	printf("*        6.登出                *\n");
	printf("|        0.保存退出            |\n");
	printf("|                              |\n");
	printf("********************************\n");
}

//业务函数实现
// 1.用户登录
void userLogin(void)
{
	EmployeeList* p = Emp;//员工链表头指针给p
	if (online == 0)    //如果没有登录
	{
		int pwdCount = 0;//密码输入次数
		color(4);
		printf("请先登录!\n");
		while (pwdCount < 3)
		{
			int entry_pid = 0; //账号 /员工号
			char entry_pw[20] = { 0 };  //密码
			color(7);
			printf("请输入员工号:");
			entry_pid = get_int();//检测输入是否为纯数字
			printf("请输入密码: ");
			getLine(entry_pw, 20);
			encode(entry_pw);//对输入字符先加密再比较  因为链表中密码是加密后的
			// 遍历所有员工
			while (p != NULL)
			{
				// 数据长度校验
				if (entry_pid == 0 || strlen(entry_pw) == 0)
				{
					printf("员工号或密码不能为空\n");
					pwdCount++;
					break;
				}
				// 成功匹配账号密码  密码解密decode(pwd);
				else if ((p->employee.pid == entry_pid) && strcmp(p->employee.password, entry_pw) == 0)
				{

					online_pid = entry_pid;
					if (p->employee.authority == 100)
					{
						online = 1;//登陆者为总经理
						printf("\n总经理，登陆成功!\n");
						return;
					}
					else if (p->employee.authority == 200)
					{
						online = 2;//登陆者为部门经理                       
						printf("\n%s经理 %s，登陆成功!\n", p->employee.department, p->employee.name);
						return;
					}
					else if (p->employee.authority == 300)
					{
						online = 3;//登陆者为普通员工               
						printf("\n%s职员 %s，登陆成功!\n", p->employee.department, p->employee.name);
						return;
					}
				}
				p = p->next;//遍历链表
			}
			p = Emp;//重新指向头结点 开始下一轮校验
			printf("\n登陆失败，用户id或密码错误\n");
			pwdCount++;
		}
		online = -1;//锁定系统
		color(4);
		printf("密码错误三次，当前系统已经被锁定，目前无法使用\n");
	}
	else if (online == 1)
	{
		printf("总经理您好，您已登录!\n");
	}
	else if (online == 2)
	{
		while (p != NULL)//找到当前登录者在链表中的位置
		{
			if (p->employee.pid == online_pid) break;
			p = p->next;
		}
		printf("%s经理%s您好，您已登录!\n", p->employee.department, p->employee.name);
	}
	else if (online == 3)
	{
		while (p != NULL)//找到当前登录者在链表中的位置
		{
			if (p->employee.pid == online_pid) break;
			p = p->next;
		}
		printf("%s职员%s您好，您已登录\n", p->employee.department, p->employee.name);
	}
	else
	{
		color(4);
		printf("当前系统已经被锁定，目前无法使用\n");
	}
}

// 6.用户登出
void userLogout(void)
{
	if (online == 1 || online == 2 || online == 3)  //如果已经登录
	{
		online = 0;
		printf("登出成功\n");
	}
	else if (online == -1)
	{
		color(4);
		printf("当前系统已经被锁定，目前无法使用！\n");
	}
	else
	{
		color(4);
		printf("您还未登录!\n");
	}
}

