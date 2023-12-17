#include <Util.h>
#include "Employee.h"

//函数实现
//尾插法建立单链表——员工信息
EmployeeList* createEmployeeList()
{
	int eCount = 0;   //链表中元素个数 即员工总数
	EmployeeList* head;
	EmployeeList* p1, * p2;
	int num = 0;
	FILE* ffrp = fopen("../员工管理系统/资源文件/employee.txt", "r");
	if (NULL == ffrp)
	{
		printf("员工信息文件 打开失败!\n");
		exit(0);
	}
	p1 = p2 = (EmployeeList*)malloc(sizeof(struct ENode));
	//202101 123 张三 陕西西安 1008611 101.00 人事部 300 HR
	num = fscanf(ffrp, "%d %s %s %s %s %lf %s %d %s\n",
		&p1->employee.pid, p1->employee.password, p1->employee.name, p1->employee.address, p1->employee.phonenum,
		&p1->employee.salary, p1->employee.department, &p1->employee.authority, p1->employee.position);
	head = NULL;
	while (1)
	{
		eCount++;
		if (eCount == 1) head = p1;
		else p2->next = p1;

		p2 = p1;
		p1 = (EmployeeList*)malloc(sizeof(struct ENode));
		if (feof(ffrp) != 0)break;//文件读取结束 跳出循环
		num = fscanf(ffrp, "%d %s %s %s %s %lf %s %d %s\n",
			&p1->employee.pid, p1->employee.password, p1->employee.name, p1->employee.address, p1->employee.phonenum,
			&p1->employee.salary, p1->employee.department, &p1->employee.authority, p1->employee.position);
	}
	p2->next = NULL;
	return head;
}
//查询所有员工信息 不包含密码
void showAllEmployeesInfo()
{
	int count = 0;  //统计记录数
	EmployeeList* p = Emp;//找到链表的头结点
	color(6);
	printf("员工号    姓名    籍贯      手机号         薪资       部门       职位\n");
	color(7);
	while (p != NULL)
	{
		printf("%-10d%-8s%-10s%-15s%-11.2lf%-11s%-10s\n",
			p->employee.pid, p->employee.name, p->employee.address, p->employee.phonenum,
			p->employee.salary, p->employee.department, p->employee.position);
		p = p->next;
		count++;
	}
	color(6);
	printf("共查找到%d条记录！\n", count);
}
//根据部门查询员工信息
void selectEmployeesByDep(char* department)
{
	//首先根据登录者的员工号（全局变量online_pid）找到其所在结点
	//再根据结点查询部门一致的
	EmployeeList* p = Emp;//找到员工链表的头结点
	if (online == 2 || online == 1)
	{
		color(6);

		printf("员工号    姓名    籍贯      手机号         薪资       部门       职位\n");
		color(7);
		while (p != NULL)//遍历找到相同部门的员工并打印
		{
			if (strcmp(p->employee.department, department) == 0)
			{
				printf("%-10d%-8s%-10s%-15s%-11.2lf%-11s%-10s\n",
					p->employee.pid, p->employee.name, p->employee.address, p->employee.phonenum,
					p->employee.salary, p->employee.department, p->employee.position);
			}
			p = p->next;
		}
	}
}
//通过员工编号查询员工信息
void selectEmployeeByPid(int pid)
{
	EmployeeList* p = Emp;//找到员工链表的头结点
	int flag = 0;//标志有无查到
	if (online == 1)//总经理可查所有人
	{
		while (p != NULL)
		{
			if (pid == p->employee.pid)
			{
				color(6);
				printf("员工号    姓名    籍贯      手机号         薪资       部门       职位\n");
				color(7);
				printf("%-10d%-8s%-10s%-15s%-11.2lf%-11s%-10s\n",
					p->employee.pid, p->employee.name, p->employee.address, p->employee.phonenum,
					p->employee.salary, p->employee.department, p->employee.position);
				flag = 1;
			}
			p = p->next;
		}
		if (flag == 0)
		{
			color(4);
			printf("无此员工！\n");
		}
	}
	else if (online == 2)//部门经理可查自己部门人
	{
		EmployeeList* e = Emp;
		int flag = 0;
		while (p != NULL)//找到登录者的部门
		{
			if (online_pid == p->employee.pid) {
				break;
			}
			p = p->next;
		}
		while (e != NULL) //查找编号一致的员工
		{
			if (e->employee.pid == pid)
			{
				if (strcmp(e->employee.department, p->employee.department) == 0)
				{
					color(6);
					printf("员工号    姓名    籍贯      手机号         薪资       部门       职位\n");
					color(7);
					printf("%-10d%-8s%-10s%-15s%-11.2lf%-11s%-10s\n",
						e->employee.pid, e->employee.name, e->employee.address, e->employee.phonenum,
						e->employee.salary, e->employee.department, e->employee.position);
					flag = 1;//查到了 且是该部门的 则打印
				}
				else
				{
					flag = 1;//查到但是其他部门
					color(4);
					printf("该员工属于%s！您无权限查阅！\n", e->employee.department);
				}
			}
			e = e->next;
		}
		if (flag == 0)
		{
			color(4);
			printf("公司无此员工！\n");
		}
	}
	else //普通员工
	{
		char pwd[15] = { 0 };
		color(6);
		printf("员工号    姓名    密码        籍贯      手机号         薪资       部门       职位\n");
		color(7);
		while (p != NULL)
		{
			if (pid == p->employee.pid)
			{
				strcpy(pwd, p->employee.password);
				decode(pwd);    //对输出密码字符解密
				printf("%-10d%-8s%-12s%-10s%-15s%-11.2lf%-11s%-10s\n",
					p->employee.pid, p->employee.name, pwd, p->employee.address, p->employee.phonenum,
					p->employee.salary, p->employee.department, p->employee.position);
				break;
			}
			p = p->next;
		}
	}
}
//依据员工姓名查询员工信息
void selectEmployeeByName(char* name)
{
	EmployeeList* p = Emp;//找到员工链表的头结点
	int flag = 0;//标志有无查到
	if (online == 1)//总经理可查所有人
	{

		while (p != NULL)
		{
			if (strcmp(name, p->employee.name) == 0)
			{
				color(6);
				printf("员工号    姓名    籍贯      手机号         薪资       部门       职位\n");
				color(7);
				printf("%-10d%-8s%-10s%-15s%-11.2lf%-11s%-10s\n",
					p->employee.pid, p->employee.name, p->employee.address, p->employee.phonenum,
					p->employee.salary, p->employee.department, p->employee.position);
				flag = 1;
			}
			p = p->next;
		}
		if (flag == 0)
		{
			color(4);
			printf("无此员工！\n");
		}
	}
	else if (online == 2)//部门经理可查自己部门人
	{
		EmployeeList* e = Emp;
		int flag = 0;
		while (p != NULL)//找到登录者的部门
		{
			if (online_pid == p->employee.pid) {
				break;
			}
			p = p->next;
		}
		while (e != NULL) //查找编号一致的员工
		{
			if (strcmp(e->employee.name, name) == 0)
			{
				if (strcmp(e->employee.department, p->employee.department) == 0)
				{
					color(6);
					printf("员工号    姓名    籍贯      手机号         薪资       部门       职位\n");
					color(7);
					printf("%-10d%-8s%-10s%-15s%-11.2lf%-11s%-10s\n",
						e->employee.pid, e->employee.name, e->employee.address, e->employee.phonenum,
						e->employee.salary, e->employee.department, e->employee.position);
					flag = 1;//查到了 且是该部门的 则打印
				}
				else
				{
					flag = 1;//查到但是其他部门
					color(4);
					printf("该员工属于%s！您无权限查阅！\n", e->employee.department);
				}
			}
			e = e->next;
		}
		if (flag == 0)
		{
			color(4);
			printf("公司无此员工！\n");
		}
	}
}
//依据员工籍贯查询员工信息
void selectEmployeesByAddress(char* address)
{
	EmployeeList* p = Emp;//找到员工链表的头结点
	int flag = 0;//是否打印标题 控制标题只打印一次
	if (online == 1)
	{
		while (p != NULL)//遍历找到相同籍贯的员工并打印
		{
			if (strcmp(p->employee.address, address) == 0)
			{
				if (flag == 0)
				{
					flag = 1;
					color(6);
					printf("员工号    姓名    籍贯      手机号         薪资       部门       职位\n");
				}
				color(7);
				printf("%-10d%-8s%-10s%-15s%-11.2lf%-11s%-10s\n",
					p->employee.pid, p->employee.name, p->employee.address, p->employee.phonenum,
					p->employee.salary, p->employee.department, p->employee.position);
			}
			p = p->next;
		}
		if (p == NULL && flag == 0)
		{
			color(4);
			printf("无籍贯为%s的员工！\n", address);
		}
	}
	else if (online == 2)
	{
		EmployeeList* e = Emp;
		int flag = 0;
		int flag2 = 0;
		int f = 0;//一次计数器，使信息表只输出一次
		while (p != NULL)//找到登录者的部门
		{
			if (online_pid == p->employee.pid) {
				break;
			}
			p = p->next;
		}
		while (e != NULL) //查找籍贯一致的员工
		{
			if (strcmp(e->employee.address, address) == 0)
			{

				if (strcmp(e->employee.department, p->employee.department) == 0)//查到了 且是该部门的 则打印
				{
					if (f == 0)
					{
						color(6);
						printf("员工号    姓名    籍贯      手机号         薪资       部门       职位\n");
						f = 1;
					}
					color(7);
					printf("%-10d%-8s%-10s%-15s%-11.2lf%-11s%-10s\n",
						e->employee.pid, e->employee.name, e->employee.address, e->employee.phonenum,
						e->employee.salary, e->employee.department, e->employee.position);
					flag2 = 1;
				}
				flag = 1;
			}
			e = e->next;
		}
		if (flag == 1 && flag2 == 0)
		{
			color(4);
			printf("%s无籍贯为%s的员工！\n", p->employee.department, address);
		}
		if (flag == 0 && flag2 == 0)
		{
			color(4);
			printf("本公司无籍贯为%s的员工！\n", address);
		}
	}
}
//3.新增业务
void addEmployee()
{
	EmployeeList* e = Emp;
	if (online == 1)
	{
		printf("总经理您好,新增员工请联系人事部经理!\n");
		while (e != NULL)
		{
			if (strcmp(e->employee.position, "人事部经理") == 0)
			{
				color(6);
				printf("人事部经理:%s\t联系方式:%s", e->employee.name, e->employee.phonenum);
				break;
			}
			e = e->next;
		}
	}
	else if (online == 2 || online == 3)//经理或普通员工登录
	{
		while (e != NULL)//找到在线者在链表中的位置
		{
			if (e->employee.pid == online_pid) break;
			e = e->next;
		}
		if (strcmp(e->employee.department, "人事部") == 0)//如果是登录者属于人事部
		{
			//则可新增用户
			char pwd[15];
			int max = 202100; //取得最新员工编号  若无员工默认从202100开始新增
			DepartmentList* dep = Dep;
			EmployeeList* p = (EmployeeList*)malloc(sizeof(struct ENode));//申请新结点内存
			color(3);
			printf("新增员工开始: \n");
			e = Emp;
			while (e != NULL)//找到最新员工编号
			{
				if (max < e->employee.pid)
					max = e->employee.pid;
				e = e->next;
			}
			color(2);
			printf("请输入员工姓名：");
			scanf("%s", p->employee.name);      //姓名 
			p->employee.pid = ++max;            //员工编号  自增
			sprintf(pwd, "%d", max);				//密码(最大编号转换成字符串)
			encode(pwd);                        //加密密码 
			strcpy(p->employee.password, pwd);  //密码默认为当前员工编号
			p->employee.authority = 300;        //权限 为 职员 
			printf("请输入员工籍贯：");
			scanf("%s", p->employee.address);   //籍贯
			strcpy(p->employee.position, "职员");//职位 新员工均为职员
			printf("请输入员工手机号：");
			strcpy(p->employee.phonenum, get_phoneNum());
			color(3);
			printf("\n请选择员工部门：\n1.人事部\n2.财务部\n3.销售部\n4.市场部\n");//部门
			switch (get_cmd('1', '4'))
			{
			case '1':   strcpy(p->employee.department, "人事部");break;
			case '2':   strcpy(p->employee.department, "财务部");break;
			case '3':   strcpy(p->employee.department, "销售部");break;
			case '4':   strcpy(p->employee.department, "市场部");break;
			}
			while (dep != NULL)//遍历部门表  找到新增人员的对应部门
			{
				if (strcmp(p->employee.department, dep->department.dname) == 0)
					break;
				dep = dep->next;
			}
			if (online == 2)//如果是人事部经理登录  则可以增加工资
			{
				int i = 0;//遍历输入的字符串
				int count = 0;//记录小数点个数
				int flag = 0;//标志用户输入是否为合法的 浮点数，如果不是 重新输入
				color(2);
				printf("请输入薪资：");
				p->employee.salary = get_double();
				dep->department.sumsalary += p->employee.salary;//部门表对应工资增加
				dep->department.dnum++;//部门表对应人数增加
			}
			else
			{
				p->employee.salary = 0;
				dep->department.dnum++;//部门表对应人数增加
				printf("\n请联系%s经理%s!为新员工%s调整薪资!\n", dep->department.dname, dep->department.mname, p->employee.name);
			}
			e = Emp;//从头遍历链表找到尾结点  链表尾部添加新数据
			while (e != NULL)
			{
				if (e->next == NULL)//将新结点加入到链表尾
				{
					e->next = p;
					p->next = NULL;
				}
				e = e->next;
			}
			color(2);
			printf("员工新增成功!");
		}
		else//如果是其他部门员工  则无权限操作
		{
			color(4);
			printf("您不属于人事部，无权限操作!\n");
		}
	}
	else if (online == 0)//若未登录
	{
		userLogin();
	}
	else if (online == -1)
	{
		color(4);
		printf("当前系统已经被锁定，目前无法使用\n");
	}
}
//4.修改业务
void updateEmployee() {
	char name[20];
	int  pid;
	EmployeeList* e = Emp;
	if (online == 0)
	{ //未登录提示先登录
		userLogin();
	}
	else if (online == 1)
	{ //总经理登录 卸任/委任部门经理
		showAllEmployeesInfo();//展示所有信息
		color(3);
		printf("是否委任、卸任经理？\n1.是\n0.否\n");
		switch (get_cmd('0', '1')) {
		case '1':
			color(2);
			printf("输入你需要卸任的经理姓名：");
			scanf("%s", name);
			updateEmployeeByName(name);
			break;
		case '0':
			return;
		}
	}
	else if (online == 2) { //部门经理登录
		while (e != NULL) { //员工链表中找到经理位置
			if (online_pid == e->employee.pid) break;
			e = e->next;
		}
		selectEmployeesByDep(e->employee.department);//展示部门人员信息
		color(3);
		printf("修改员工薪资\n1.按员工编号修改\n2.按员工姓名修改\n3.修改本人信息\n0.返回\n");
		switch (get_cmd('0', '3'))
		{
		case '1':
			color(2);
			printf("输入需要修改薪资人员的id：");
			pid = get_int();
			updateEmployeeByPid(pid);
			break;
		case '2':
			color(2);
			printf("输入需要修改薪资人员的姓名：");
			scanf("%s", name);
			updateEmployeeByName(name);
			break;
		case '3':

			online = 3;//权限暂时改为普通员工
			selectEmployeeByPid(online_pid);
			updateEmployeeByPid(online_pid);
			online = 2;//权限改回经理
			break;
		case '0':
			return;
		}
	}
	else if (online == 3)
	{ //普通员工登录
		selectEmployeeByPid(online_pid);
		color(3);
		printf("是否修改本人信息？\n1.是\n0.否\n");
		switch (get_cmd('0', '1')) {
		case '1':
			updateEmployeeByPid(online_pid);
			break;
		case '0':
			return;
		}
	}
	else if (online == -1) {
		color(4);
		printf("当前系统已经被锁定，目前无法使用\n");
	}
}
//4.1根据员工id来修改
void updateEmployeeByPid(int pid) {
	double newsalary = 0;
	EmployeeList* e = Emp;
	EmployeeList* e1 = Emp;
	DepartmentList* d = Dep;
	char key1[15] = { 0 };
	char key2[15] = { 0 };
	int flag = 0;
	if (online == 2)
	{
		while (e != NULL)
		{
			if (online_pid == e->employee.pid)
				break;
			e = e->next;
		}
		selectEmployeeByPid(pid);//展示该员工信息
		while (e1 != NULL)
		{
			if (pid == e1->employee.pid)
			{
				break;
			}
			e1 = e1->next;
		}
		if (e1 == NULL) return;
		if (strcmp(e1->employee.department, e->employee.department) == 0)
		{
			if (e1->employee.pid == e->employee.pid)
			{
				color(4);
				printf("%s您好，无法修改自己工资！\n", e->employee.name);
				return;
			}
			color(2);
			printf("请输入该员工新的薪资\n");
			newsalary = get_double();//校验 合法输入
			while (d != NULL)//修改该部门总工资
			{
				if (strcmp(e->employee.department, d->department.dname) == 0)
					d->department.sumsalary += (newsalary - e1->employee.salary);
				d = d->next;
			}
			e1->employee.salary = newsalary;//覆盖工资
			flag = 1;
		}
		else
		{
			color(4);
			printf("%s属于%s,您无修改其薪资的权限！", e1->employee.name, e1->employee.department);
			return;
		}
		if (flag == 1)
			selectEmployeesByDep(e->employee.department);//查到该经理所在部门的所有员工
		else
			printf("薪资修改失败");
	}
	else if (online == 3) {
		while (e != NULL) {
			if (online_pid == e->employee.pid)
				break;
			e = e->next;
		}
		color(3);
		printf("修改的信息：\n1.手机号\n2.籍贯\n3.密码\n0.退出\n");
		switch (get_cmd('0', '3')) {
		case '1':
			color(2);
			printf("输入您的新的手机号：");
			strcpy(e->employee.phonenum, get_phoneNum());
			flag = 1;
			break;
		case'2':
			color(2);
			printf("输入您修改后的籍贯：");
			scanf("%s", e->employee.address);
			flag = 1;
			break;
		case'3':
			while (1)
			{
				color(2);
				printf("请输入你的新密码：");
				getLine(key1, 15);
				printf("\n请再次输入你的新密码：");
				getLine(key2, 15);
				if (strcmp(key1, key2) == 0)
				{
					encode(key2);   //密码加密函数
					strcpy(e->employee.password, key2);
					flag = 1;
					break;
				}
				color(4);
				printf("\n俩次密码输入不一致\n");
			}
			break;
		case '0': return;
		}
	}
	if (flag == 1)
	{
		color(6);
		printf("\n您修改后的信息如下：\n");
		selectEmployeeByPid(pid);
		color(2);
		printf("信息修改成功!\n");
	}
}
//4.2根据员工姓名修改(总经理委任、卸任经理)
void updateEmployeeByName(char* name)
{
	char newname[15];//新委任人姓名
	char dep1name[20];//新委任人所在的部门 也用于拼接字符串“xx部经理”
	char dep2name[10];//被卸任了的经理所在的部门
	EmployeeList* e = Emp;
	EmployeeList* e1 = NULL;// 要委任人在链表中的结点位置
	DepartmentList* d = Dep;
	int flag = 0; //表示没查到
	if (online == 1)//总经理登录时可委任卸任经理
	{
		while (e != NULL)
		{
			if (strcmp(name, e->employee.name) == 0)
			{
				if (strcmp(e->employee.position, "总经理") == 0)//总经理无法卸任自己
				{
					color(4);
					printf("该用户为总经理，无法卸任!\n");
					return;
				}
				if (strcmp(e->employee.position, "职员") == 0) //如果此人是职员，则提示此人为职员 不用卸任
				{
					color(4);
					printf("%s为职员，无法卸任!\n", name);
					return;
				}
				else //如果此人是经理  则卸任
				{
					strcpy(e->employee.position, "职员");//职位从xx经理改为职员
					e->employee.authority = 300;//降低其权限
					printf("卸任成功!\n");
					flag = 1;
					break;
				}
			}
			e = e->next;
		}
		if (e == NULL)
		{
			color(4);
			printf("查无此人!\n卸任失败!\n");
			return;
		}
		selectEmployeesByDep(e->employee.department);//展示该经理所在部门的所有员工
		strcpy(dep2name, e->employee.department);//dep2保存被卸任经理的部门名
		flag = 0;
		while (1)
		{
			color(2);
			printf("请输入要委任的新经理姓名: ");
			scanf("%s", newname);
			e1 = Emp;
			while (e1 != NULL)
			{
				if (strcmp(newname, e1->employee.name) == 0)
				{
					//找到新姓名在链表中的位置,便于对比部门是否一致
					break;
				}
				e1 = e1->next;
			}
			if (e1 == NULL)
			{
				color(4);
				printf("公司查无此人\n");
				continue;
			}
			e = Emp;//e重新指向链表头
			while (e != NULL)
			{
				if (strcmp(newname, e->employee.name) == 0) //链表中若有此人
				{
					strcpy(dep1name, e->employee.department);//保存他的部门
					if (strcmp(e1->employee.department, dep2name) == 0) //若部门一致，则可委任
					{ //必须时同部门才能委任
						strcat(dep1name, "经理"); //得到department字符串现在是"xx部经理"
						strcpy(e->employee.position, dep1name);

						flag = 1;//委任成功后，部门表中经理记得修改

						while (d != NULL)//遍历部门表 修改其中的经理姓名
						{
							if (strcmp(name, d->department.mname) == 0)
							{
								strcpy(d->department.mname, newname);//修改姓名
								e->employee.authority = 200;
								break;
							}
							d = d->next;
						}
						color(2);
						printf("委任成功!\n");
						selectEmployeesByDep(d->department.dname);//展示修改后该经理所在部门的所有员工
						return;//结束业务
					}
					else
					{
						color(4);
						printf("无法委任,%s是%s的!\n", newname, e1->employee.department);
						break;
					}
				}
				e = e->next;
			}
		}
	}
	else if (online == 2)
	{
		while (e != NULL)
		{
			if (strcmp(e->employee.name, name) == 0)
			{
				updateEmployeeByPid(e->employee.pid);
				break;
			}
			e = e->next;
		}
		if (e == NULL)
		{
			color(4);
			printf("公司无该员工！");
		}
	}
}
//5.删除业务
void deleteEmployee()
{
	EmployeeList* e = Emp;
	int pid;
	char name[15];
	if (online == 0)//未登录先登录
		userLogin();
	else if (online == 1)//总经理登录
	{
		showAllEmployeesInfo();
		color(3);
		printf("辞退员工\n1.按员工编号辞退员工\n2.按员工姓名辞退员工\n0.返回\n");
		switch (get_cmd('0', '2'))
		{
		case '1':
			color(2);
			printf("请输入员工编号：");
			pid = get_int();
			if (pid == 10000)
			{
				color(4);
				printf("超级管理员账号无法删除！");
				return;
			}
			deleteEmployeeByPid(pid);break;
		case '2':
			color(2);
			printf("请输入要删除的员工姓名：");
			scanf("%s", name);
			deleteEmployeeByName(name);
		case '0':return;
		}
	}
	else if (online == 2)//部门经理登录
	{
		while (e != NULL)//员工链表中找到经理位置
		{
			if (online_pid == e->employee.pid) break;
			e = e->next;
		}
		selectEmployeesByDep(e->employee.department);//展示部门人员信息
		color(3);
		printf("辞退员工\n1.按员工编号辞退员工\n2.按员工姓名辞退员工\n0.返回\n");
		switch (get_cmd('0', '2'))
		{
		case '1':
			color(2);
			printf("请输入员工编号：");
			pid = get_int();
			if (pid == 10000)
			{
				color(4);
				printf("超级管理员账号无法删除！");
				return;
			}
			if (pid == online_pid)
			{
				color(4);
				printf("%s%s您好,您无法删除自己！", e->employee.position, e->employee.name);
				return;
			}
			deleteEmployeeByPid(pid);//依据id删除
			selectEmployeesByDep(e->employee.department);//展示删除后部门人员信息
			break;
		case '2':
			color(2);
			printf("请输入要删除的员工姓名：");
			scanf("%s", name);
			if (strcmp(name, "admin") == 0)
			{
				color(4);
				printf("超级管理员账号无法删除！");
				return;
			}
			if (strcmp(name, e->employee.name) == 0)
			{
				color(4);
				printf("%s%s您好,您无法删除自己！", e->employee.position, e->employee.name);
				return;
			}
			deleteEmployeeByName(name);//依据姓名删除
			selectEmployeesByDep(e->employee.department);//展示删除后部门人员信息
			break;
		case '0':return;
		}
	}
	else if (online == -1)
	{
		color(4);
		printf("当前系统已经被锁定，目前无法使用\n");
	}
	else
	{
		color(4);
		printf("无权限操作!\n");
	}

}
//5.1根据员工编号删除
void deleteEmployeeByPid(int pid)
{
	char department[10];
	double salary = 0;
	EmployeeList* p = Emp;  //员工链表的头指针
	EmployeeList* q = p;
	DepartmentList* d = Dep;
	int flag = 0;
	if (online == 1)
	{
		while (p != NULL)
		{
			if (p->next != NULL)
				if (pid == p->next->employee.pid)
				{
					//如果是被删除者是经理,则需要先卸任->委任经理,后才可删除
					if (p->next->employee.authority == 200)
					{
						color(4);
						printf("被删除者是%s%s,请先卸任->委任经理!\n", p->next->employee.position, p->next->employee.name);
						printf("1.是\n0.否\n");
						switch (get_cmd('0', '1'))
						{
						case '1': updateEmployeeByName(p->next->employee.name);//卸任其职位
							break;
						case '0': return;
						}
					}
					strcpy(department, p->next->employee.department);//department记录编号员工所在部门 
					salary = p->next->employee.salary;//salary记录编号员工原来的工资
					if (p->next->next == NULL)//如果是最后一个节点  删除方法有所改变
					{
						q = p->next;
						p->next = NULL;
						free(q);
						flag = 1;break;//删除成功
					}
					//如果是中间的某个结点
					q = p->next;
					p->next = q->next;
					free(q);
					flag = 1;break;//删除成功
					break;
				}
			p = p->next;
		}
		while (d != NULL)
		{
			if (strcmp(department, d->department.dname) == 0)
			{
				d->department.dnum--;
				d->department.sumsalary -= salary;
			}
			d = d->next;
		}
		if (flag == 0)
		{
			color(4);
			printf("编号为%d的员工不存在！\n", pid);
			return;
		}
		printf("删除成功！\n");
	}
	else if (online == 2)
	{
		EmployeeList* e = Emp;
		while (e != NULL)//登陆者在链表中的位置  方便对比部门是否一致
		{
			if (e->employee.pid == online_pid) break;
			e = e->next;
		}
		while (p != NULL)
		{
			if (p->next != NULL)
				if (pid == p->next->employee.pid)//遍历找到id一致的员工
				{
					//编号为pid的员工是否属于该经理的部门
					if (strcmp(p->next->employee.department, e->employee.department) == 0)
					{
						strcpy(department, p->next->employee.department);//department记录编号员工所在部门 
						salary = p->next->employee.salary;//salary记录编号员工原来的工资
						if (p->next->next == NULL)//如果是最后一个节点  删除方法有所改变
						{
							q = p->next;
							p->next = NULL;
							free(q);
							flag = 1;break;//删除成功
						}
						//如果是中间的某个结点
						q = p->next;
						p->next = q->next;
						free(q);
						flag = 1;break;//删除成功
					}
					else
					{
						flag = 1;
						color(4);
						printf("编号为%d的员工不属于%s", pid, e->employee.department);
					}
				}
			p = p->next;
		}
		if (flag == 0)
		{
			color(4);
			printf("编号为%d的员工不存在！\n", pid);
			return;
		}
		while (d != NULL)
		{
			if (strcmp(department, d->department.dname) == 0)
			{
				d->department.dnum--;
				d->department.sumsalary -= salary;
			}
			d = d->next;
		}
		color(2);
		printf("删除成功！\n");
	}
}
//5.2根据员工姓名删除
void deleteEmployeeByName(char* name)
{
	char department[10];
	double salary = 0;
	EmployeeList* p = Emp;  //员工链表的头指针
	EmployeeList* q = p;
	DepartmentList* d = Dep;
	int flag = 0;
	if (online == 1)
	{
		while (p != NULL)
		{
			if (p->next != NULL)
				if (strcmp(name, p->next->employee.name) == 0)//找到姓名一致的员工
				{
					//如果是被删除者是经理,则需要先卸任->委任经理,后才可删除
					if (p->next->employee.authority == 200)
					{
						color(4);
						printf("被删除者是%s%s,请先卸任->委任经理!\n", p->next->employee.position, p->next->employee.name);
						printf("1.是\n0.否\n");
						switch (get_cmd('0', '1'))
						{
						case '1': updateEmployeeByName(p->next->employee.name);//卸任其职位
						case '0': return;
						}
						return;
					}
					strcpy(department, p->next->employee.department);//department记录编号员工所在部门 
					salary = p->next->employee.salary;//salary记录编号员工原来的工资
					if (p->next->next == NULL)//如果是最后一个节点  删除方法有所改变
					{
						q = p->next;
						p->next = NULL;
						free(q);
						flag = 1;break;//删除成功
					}
					//如果是中间的某个结点
					q = p->next;
					p->next = q->next;
					free(q);
					flag = 1;break;//删除成功
					break;
				}
			p = p->next;
		}
		if (flag == 0)
		{
			color(4);
			printf("姓名为%s的员工不存在！", name);
			return;
		}
		while (d != NULL)
		{
			if (strcmp(department, d->department.dname) == 0)
			{
				d->department.dnum--;
				d->department.sumsalary -= salary;
			}
			d = d->next;
		}
		printf("删除成功！\n");
	}
	else if (online == 2)
	{
		EmployeeList* e = Emp;
		while (e != NULL)//登陆经理在链表中的位置  方便对比部门是否一致
		{
			if (e->employee.pid == online_pid) break;
			e = e->next;
		}
		while (p != NULL)
		{
			if (p->next != NULL)
				if (strcmp(name, p->next->employee.name) == 0)
				{
					//姓名为name的员工是否属于该经理的部门
					if (strcmp(p->next->employee.department, e->employee.department) == 0)
					{
						strcpy(department, p->next->employee.department);//department记录编号员工所在部门 
						salary = p->next->employee.salary;//salary记录编号员工原来的工资
						if (p->next->next == NULL)//如果是最后一个节点  删除方法有所改变
						{
							q = p->next;
							p->next = NULL;
							free(q);
							flag = 1;break;//删除成功
						}
						//如果是中间的某个结点
						q = p->next;
						p->next = q->next;
						free(q);
						flag = 1;break;//删除成功
					}
					else
					{
						flag = 1;
						printf("员工%s不属于%s", name, e->employee.department);
					}
				}
			p = p->next;
		}
		if (flag == 0)
		{
			printf("姓名为%s的员工不存在！", name);
			return;
		}
		while (d != NULL)
		{
			if (strcmp(department, d->department.dname) == 0)
			{
				d->department.dnum--;
				d->department.sumsalary -= salary;
			}
			d = d->next;
		}
		printf("删除成功！\n");
	}
}
//7.员工链表排序 先相同部门排一起  然后按薪资高低排序
void employeesSort()
{
	EmployeeList* p = NULL;
	EmployeeList* q = NULL;
	EmployeeList* index = NULL;
	//1.选择排序 按部门排序
	for (p = Emp; p != NULL; p = p->next)
	{
		index = p;
		for (q = p->next; q != NULL; q = q->next)
		{
			if (strcmp(index->employee.department, q->employee.department) > 0)
				index = q;//找到下标
		}
		if (index != p)
			swap(p, index);
	}
	//2.冒泡排序，部门一致的情况下 按薪资排
	for (p = Emp; p != NULL; p = p->next)
	{
		for (q = Emp; q->next != NULL; q = q->next)
		{
			//部门不同的俩数据之间不用交换
			if (strcmp(q->employee.department, q->next->employee.department) != 0)
				continue;
			if (q->employee.salary < q->next->employee.salary)
				swap(q, q->next);
		}
	}
}
//swap函数 排序时交换两结点
void swap(EmployeeList* p, EmployeeList* q)
{
	//temp=q; q=t;t=temp
	Employee temp = { 0 };
	temp = p->employee;
	p->employee = q->employee;
	q->employee = temp;
}
