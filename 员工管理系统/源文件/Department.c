#include "Department.h"
#include "Util.h"
//尾插法建立部门表——部门信息
DepartmentList* createDepartmentList()
{
	int dCount = 0;   //链表中元素个数 即员工总数
	DepartmentList* head;
	DepartmentList* p1, * p2;
	int num = 0;
	FILE* dfrp = fopen("../员工管理系统/资源文件/department.txt", "r");
	if (NULL == dfrp)
	{
		printf("部门信息文件 打开失败!\n");
		exit(0);
	}
	p1 = p2 = (DepartmentList*)malloc(sizeof(struct DNode));
	//人事部 貂蝉 3 2300
	num = fscanf(dfrp, "%s %s %d %lf\n", p1->department.dname, p1->department.mname,
		&p1->department.dnum, &p1->department.sumsalary);
	head = NULL;
	while (1)
	{
		dCount++;
		if (dCount == 1) head = p1;
		else p2->next = p1;
		p2 = p1;
		p1 = (DepartmentList*)malloc(sizeof(struct DNode));
		if (feof(dfrp) != 0)break;//文件读取结束 跳出循环
		num = fscanf(dfrp, "%s %s %d %lf\n", p1->department.dname, p1->department.mname,
			&p1->department.dnum, &p1->department.sumsalary);
	}
	p2->next = NULL;
	return head;
}
// 2.查询业务
void showAllInfo(void)
{
	char department[10];    //部门
	int pid;                //员工编号
	char address[20];       //员工籍贯
	char name[15];          //员工姓名
	EmployeeList* p = Emp;  //员工链表的头指针

	if (online == 1)    //如果总经理已经登录
	{
		color(3);
		printf("1.显示所有员工信息\n2.显示部门概况\n3.按姓名查询\n4.按员工号查询\n5.按部门查询\n6.按籍贯查询\n0.返回\n");
		switch (get_cmd('0', '6'))
		{
		case '1':
			showAllEmployeesInfo();//显示所有员工信息
			break;
		case '2':
			showALLDepartmentInfo();//显示所有部门概况  包含薪资和
			break;
		case '3':
			//按姓名查
			color(2);
			printf("请输入姓名： ");
			scanf("%s", name);          //输入姓名
			selectEmployeeByName(name); //依据姓名查询
			break;
		case '4':
			//按员工号查
			color(2);
			printf("请输入员工号： ");
			pid = get_int();
			selectEmployeeByPid(pid);   //依据员工号查
			break;
		case '5':
			//输入部门查
			color(3);
			printf("\n请选择员工部门：\n1.人事部\n2.财务部\n3.销售部\n4.市场部\n");//部门
			switch (get_cmd('1', '4'))
			{
			case '1':   strcpy(department, "人事部");break;
			case '2':   strcpy(department, "财务部");break;
			case '3':   strcpy(department, "销售部");break;
			case '4':   strcpy(department, "市场部");break;
			}
			selectEmployeesByDep(department);
			break;
		case '6':
			//输入籍贯 直辖市或省市 如 “北京”，“陕西西安”等
			color(2);
			printf("请输入籍贯： ");
			scanf("%s", address);       //输入籍贯
			selectEmployeesByAddress(address);
			break;
		case '0':return;
		}
	}
	else if (online == 2)//如果某个部门经理登录
	{
		color(3);
		printf("1.显示本部门员工信息\n2.显示本部门概况\n3.按姓名查询\n4.按员工号查询\n5.按籍贯查询\n6.查询本人信息\n0.返回\n");
		switch (get_cmd('0', '6'))
		{
		case '1':
			while (p != NULL)//找到登录者所在的部门  便于查询相同部门的员工
			{
				if (p->employee.pid == online_pid)
					break;
				p = p->next;
			}
			selectEmployeesByDep(p->employee.department);//按经理所在部门查员工信息
			break;
		case '2':
			showALLDepartmentInfo();//显示本部门概况  包含薪资和
			break;
		case '3':
			//按姓名查
			color(2);
			printf("请输入姓名： ");
			scanf("%s", name);          //输入姓名
			selectEmployeeByName(name); //依据姓名查询
			color(2);
			break;
		case '4':
			//按员工号查
			color(2);
			printf("请输入员工号： ");
			pid = get_int();
			selectEmployeeByPid(pid);   //依据员工号查
			break;
		case '5':
			color(2);
			printf("请输入员工籍贯： ");
			scanf("%s", &address);
			selectEmployeesByAddress(address);//输入籍贯查员工信息 直辖市或省市 如 “北京”，“陕西西安”等
			break;
		case '6'://查询本人信息时  当做普通员工 便于显示密码
			online = 3;
			selectEmployeeByPid(online_pid);
			online = 2;
			break;
		case '0':return;
		}

	}
	else if (online == 3)//普通员工登录
	{
		color(3);
		printf("1.显示本人信息\n2.显示公司部门概况\n0.返回\n");

		switch (get_cmd('0', '2'))
		{
		case '1':
			selectEmployeeByPid(online_pid);    //按登录者的编号
			break;
		case '2':
			showALLDepartmentInfo();//显示公司部门概况  不包含薪资和
			break;
		case '0':return;
		}
	}
	else if (online == 0)
	{
		//未登录时  展示所有部门信息  即显示部门人数和部门经理姓名
		showALLDepartmentInfo();
		color(4);
		printf("您好,若想查询更多信息,请先登录!");

	}
	else if (online == -1)
	{
		color(4);
		printf("当前系统已经被锁定，目前无法使用\n");
	}
	else
	{
		printf("您还没有登录\n");
	}
}

//查询部门表信息
void showALLDepartmentInfo()
{
	DepartmentList* p = Dep;
	EmployeeList* e = Emp;
	int count = 0;//查询记录数
	double sum = 0;//薪资总和

	if (online == 1) //如果是总经理查  则显示部门人数 经理姓名 所有部门总应发薪资总额
	{
		color(6);
		printf("部门名称  部门经理  部门人数  应发薪资和\n");
		color(7);
		while (p != NULL)
		{
			printf("%-10s%-14s%-6d%-10.2lf\n", p->department.dname, p->department.mname,
				p->department.dnum, p->department.sumsalary);
			count++;
			sum += p->department.sumsalary;
			p = p->next;
		}
		color(6);
		printf("共有%d条记录,应发月薪总和为%.2lf￥", count, sum);
	}
	else if (online == 2)//如果是部门经理查  则显示部门名称 人数 该部门应发薪资总额
	{
		while (e != NULL)//首先从员工链表中找到经理所在的结点e
		{
			if (online_pid == e->employee.pid)
				break;
			e = e->next;
		}
		color(6);
		printf("部门名称  部门人数  应发薪资和\n");
		color(7);
		while (p != NULL)//再查询该部门数据
		{
			if (strcmp(p->department.dname, e->employee.department) == 0)
			{
				printf("%-14s%-6d%-10.2lf\n", p->department.dname,
					p->department.dnum, p->department.sumsalary);
				count++;
				sum += p->department.sumsalary;
			}
			p = p->next;
		}
		color(6);
		printf("应发月薪总和为%.2lf￥", sum);
	}
	else  //如果是普通员工或未登录者查  则只显示部门名称 人数 部门经理姓名
	{
		color(6);
		printf("部门名称  部门经理  部门人数\n");
		color(7);
		while (p != NULL)
		{
			printf("%-11s%-12s%-5d\n", p->department.dname, p->department.mname,
				p->department.dnum);
			count++;
			p = p->next;
		}
		color(6);
		printf("共有%d条记录!\n", count);
	}
}