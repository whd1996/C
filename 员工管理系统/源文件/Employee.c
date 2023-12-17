#include <Util.h>
#include "Employee.h"

//����ʵ��
//β�巨������������Ա����Ϣ
EmployeeList* createEmployeeList()
{
	int eCount = 0;   //������Ԫ�ظ��� ��Ա������
	EmployeeList* head;
	EmployeeList* p1, * p2;
	int num = 0;
	FILE* ffrp = fopen("../Ա������ϵͳ/��Դ�ļ�/employee.txt", "r");
	if (NULL == ffrp)
	{
		printf("Ա����Ϣ�ļ� ��ʧ��!\n");
		exit(0);
	}
	p1 = p2 = (EmployeeList*)malloc(sizeof(struct ENode));
	//202101 123 ���� �������� 1008611 101.00 ���²� 300 HR
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
		if (feof(ffrp) != 0)break;//�ļ���ȡ���� ����ѭ��
		num = fscanf(ffrp, "%d %s %s %s %s %lf %s %d %s\n",
			&p1->employee.pid, p1->employee.password, p1->employee.name, p1->employee.address, p1->employee.phonenum,
			&p1->employee.salary, p1->employee.department, &p1->employee.authority, p1->employee.position);
	}
	p2->next = NULL;
	return head;
}
//��ѯ����Ա����Ϣ ����������
void showAllEmployeesInfo()
{
	int count = 0;  //ͳ�Ƽ�¼��
	EmployeeList* p = Emp;//�ҵ������ͷ���
	color(6);
	printf("Ա����    ����    ����      �ֻ���         н��       ����       ְλ\n");
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
	printf("�����ҵ�%d����¼��\n", count);
}
//���ݲ��Ų�ѯԱ����Ϣ
void selectEmployeesByDep(char* department)
{
	//���ȸ��ݵ�¼�ߵ�Ա���ţ�ȫ�ֱ���online_pid���ҵ������ڽ��
	//�ٸ��ݽ���ѯ����һ�µ�
	EmployeeList* p = Emp;//�ҵ�Ա�������ͷ���
	if (online == 2 || online == 1)
	{
		color(6);

		printf("Ա����    ����    ����      �ֻ���         н��       ����       ְλ\n");
		color(7);
		while (p != NULL)//�����ҵ���ͬ���ŵ�Ա������ӡ
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
//ͨ��Ա����Ų�ѯԱ����Ϣ
void selectEmployeeByPid(int pid)
{
	EmployeeList* p = Emp;//�ҵ�Ա�������ͷ���
	int flag = 0;//��־���޲鵽
	if (online == 1)//�ܾ���ɲ�������
	{
		while (p != NULL)
		{
			if (pid == p->employee.pid)
			{
				color(6);
				printf("Ա����    ����    ����      �ֻ���         н��       ����       ְλ\n");
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
			printf("�޴�Ա����\n");
		}
	}
	else if (online == 2)//���ž���ɲ��Լ�������
	{
		EmployeeList* e = Emp;
		int flag = 0;
		while (p != NULL)//�ҵ���¼�ߵĲ���
		{
			if (online_pid == p->employee.pid) {
				break;
			}
			p = p->next;
		}
		while (e != NULL) //���ұ��һ�µ�Ա��
		{
			if (e->employee.pid == pid)
			{
				if (strcmp(e->employee.department, p->employee.department) == 0)
				{
					color(6);
					printf("Ա����    ����    ����      �ֻ���         н��       ����       ְλ\n");
					color(7);
					printf("%-10d%-8s%-10s%-15s%-11.2lf%-11s%-10s\n",
						e->employee.pid, e->employee.name, e->employee.address, e->employee.phonenum,
						e->employee.salary, e->employee.department, e->employee.position);
					flag = 1;//�鵽�� ���Ǹò��ŵ� ���ӡ
				}
				else
				{
					flag = 1;//�鵽������������
					color(4);
					printf("��Ա������%s������Ȩ�޲��ģ�\n", e->employee.department);
				}
			}
			e = e->next;
		}
		if (flag == 0)
		{
			color(4);
			printf("��˾�޴�Ա����\n");
		}
	}
	else //��ͨԱ��
	{
		char pwd[15] = { 0 };
		color(6);
		printf("Ա����    ����    ����        ����      �ֻ���         н��       ����       ְλ\n");
		color(7);
		while (p != NULL)
		{
			if (pid == p->employee.pid)
			{
				strcpy(pwd, p->employee.password);
				decode(pwd);    //����������ַ�����
				printf("%-10d%-8s%-12s%-10s%-15s%-11.2lf%-11s%-10s\n",
					p->employee.pid, p->employee.name, pwd, p->employee.address, p->employee.phonenum,
					p->employee.salary, p->employee.department, p->employee.position);
				break;
			}
			p = p->next;
		}
	}
}
//����Ա��������ѯԱ����Ϣ
void selectEmployeeByName(char* name)
{
	EmployeeList* p = Emp;//�ҵ�Ա�������ͷ���
	int flag = 0;//��־���޲鵽
	if (online == 1)//�ܾ���ɲ�������
	{

		while (p != NULL)
		{
			if (strcmp(name, p->employee.name) == 0)
			{
				color(6);
				printf("Ա����    ����    ����      �ֻ���         н��       ����       ְλ\n");
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
			printf("�޴�Ա����\n");
		}
	}
	else if (online == 2)//���ž���ɲ��Լ�������
	{
		EmployeeList* e = Emp;
		int flag = 0;
		while (p != NULL)//�ҵ���¼�ߵĲ���
		{
			if (online_pid == p->employee.pid) {
				break;
			}
			p = p->next;
		}
		while (e != NULL) //���ұ��һ�µ�Ա��
		{
			if (strcmp(e->employee.name, name) == 0)
			{
				if (strcmp(e->employee.department, p->employee.department) == 0)
				{
					color(6);
					printf("Ա����    ����    ����      �ֻ���         н��       ����       ְλ\n");
					color(7);
					printf("%-10d%-8s%-10s%-15s%-11.2lf%-11s%-10s\n",
						e->employee.pid, e->employee.name, e->employee.address, e->employee.phonenum,
						e->employee.salary, e->employee.department, e->employee.position);
					flag = 1;//�鵽�� ���Ǹò��ŵ� ���ӡ
				}
				else
				{
					flag = 1;//�鵽������������
					color(4);
					printf("��Ա������%s������Ȩ�޲��ģ�\n", e->employee.department);
				}
			}
			e = e->next;
		}
		if (flag == 0)
		{
			color(4);
			printf("��˾�޴�Ա����\n");
		}
	}
}
//����Ա�������ѯԱ����Ϣ
void selectEmployeesByAddress(char* address)
{
	EmployeeList* p = Emp;//�ҵ�Ա�������ͷ���
	int flag = 0;//�Ƿ��ӡ���� ���Ʊ���ֻ��ӡһ��
	if (online == 1)
	{
		while (p != NULL)//�����ҵ���ͬ�����Ա������ӡ
		{
			if (strcmp(p->employee.address, address) == 0)
			{
				if (flag == 0)
				{
					flag = 1;
					color(6);
					printf("Ա����    ����    ����      �ֻ���         н��       ����       ְλ\n");
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
			printf("�޼���Ϊ%s��Ա����\n", address);
		}
	}
	else if (online == 2)
	{
		EmployeeList* e = Emp;
		int flag = 0;
		int flag2 = 0;
		int f = 0;//һ�μ�������ʹ��Ϣ��ֻ���һ��
		while (p != NULL)//�ҵ���¼�ߵĲ���
		{
			if (online_pid == p->employee.pid) {
				break;
			}
			p = p->next;
		}
		while (e != NULL) //���Ҽ���һ�µ�Ա��
		{
			if (strcmp(e->employee.address, address) == 0)
			{

				if (strcmp(e->employee.department, p->employee.department) == 0)//�鵽�� ���Ǹò��ŵ� ���ӡ
				{
					if (f == 0)
					{
						color(6);
						printf("Ա����    ����    ����      �ֻ���         н��       ����       ְλ\n");
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
			printf("%s�޼���Ϊ%s��Ա����\n", p->employee.department, address);
		}
		if (flag == 0 && flag2 == 0)
		{
			color(4);
			printf("����˾�޼���Ϊ%s��Ա����\n", address);
		}
	}
}
//3.����ҵ��
void addEmployee()
{
	EmployeeList* e = Emp;
	if (online == 1)
	{
		printf("�ܾ�������,����Ա������ϵ���²�����!\n");
		while (e != NULL)
		{
			if (strcmp(e->employee.position, "���²�����") == 0)
			{
				color(6);
				printf("���²�����:%s\t��ϵ��ʽ:%s", e->employee.name, e->employee.phonenum);
				break;
			}
			e = e->next;
		}
	}
	else if (online == 2 || online == 3)//�������ͨԱ����¼
	{
		while (e != NULL)//�ҵ��������������е�λ��
		{
			if (e->employee.pid == online_pid) break;
			e = e->next;
		}
		if (strcmp(e->employee.department, "���²�") == 0)//����ǵ�¼���������²�
		{
			//��������û�
			char pwd[15];
			int max = 202100; //ȡ������Ա�����  ����Ա��Ĭ�ϴ�202100��ʼ����
			DepartmentList* dep = Dep;
			EmployeeList* p = (EmployeeList*)malloc(sizeof(struct ENode));//�����½���ڴ�
			color(3);
			printf("����Ա����ʼ: \n");
			e = Emp;
			while (e != NULL)//�ҵ�����Ա�����
			{
				if (max < e->employee.pid)
					max = e->employee.pid;
				e = e->next;
			}
			color(2);
			printf("������Ա��������");
			scanf("%s", p->employee.name);      //���� 
			p->employee.pid = ++max;            //Ա�����  ����
			sprintf(pwd, "%d", max);				//����(�����ת�����ַ���)
			encode(pwd);                        //�������� 
			strcpy(p->employee.password, pwd);  //����Ĭ��Ϊ��ǰԱ�����
			p->employee.authority = 300;        //Ȩ�� Ϊ ְԱ 
			printf("������Ա�����᣺");
			scanf("%s", p->employee.address);   //����
			strcpy(p->employee.position, "ְԱ");//ְλ ��Ա����ΪְԱ
			printf("������Ա���ֻ��ţ�");
			strcpy(p->employee.phonenum, get_phoneNum());
			color(3);
			printf("\n��ѡ��Ա�����ţ�\n1.���²�\n2.����\n3.���۲�\n4.�г���\n");//����
			switch (get_cmd('1', '4'))
			{
			case '1':   strcpy(p->employee.department, "���²�");break;
			case '2':   strcpy(p->employee.department, "����");break;
			case '3':   strcpy(p->employee.department, "���۲�");break;
			case '4':   strcpy(p->employee.department, "�г���");break;
			}
			while (dep != NULL)//�������ű�  �ҵ�������Ա�Ķ�Ӧ����
			{
				if (strcmp(p->employee.department, dep->department.dname) == 0)
					break;
				dep = dep->next;
			}
			if (online == 2)//��������²������¼  ��������ӹ���
			{
				int i = 0;//����������ַ���
				int count = 0;//��¼С�������
				int flag = 0;//��־�û������Ƿ�Ϊ�Ϸ��� ��������������� ��������
				color(2);
				printf("������н�ʣ�");
				p->employee.salary = get_double();
				dep->department.sumsalary += p->employee.salary;//���ű��Ӧ��������
				dep->department.dnum++;//���ű��Ӧ��������
			}
			else
			{
				p->employee.salary = 0;
				dep->department.dnum++;//���ű��Ӧ��������
				printf("\n����ϵ%s����%s!Ϊ��Ա��%s����н��!\n", dep->department.dname, dep->department.mname, p->employee.name);
			}
			e = Emp;//��ͷ���������ҵ�β���  ����β�����������
			while (e != NULL)
			{
				if (e->next == NULL)//���½����뵽����β
				{
					e->next = p;
					p->next = NULL;
				}
				e = e->next;
			}
			color(2);
			printf("Ա�������ɹ�!");
		}
		else//�������������Ա��  ����Ȩ�޲���
		{
			color(4);
			printf("�����������²�����Ȩ�޲���!\n");
		}
	}
	else if (online == 0)//��δ��¼
	{
		userLogin();
	}
	else if (online == -1)
	{
		color(4);
		printf("��ǰϵͳ�Ѿ���������Ŀǰ�޷�ʹ��\n");
	}
}
//4.�޸�ҵ��
void updateEmployee() {
	char name[20];
	int  pid;
	EmployeeList* e = Emp;
	if (online == 0)
	{ //δ��¼��ʾ�ȵ�¼
		userLogin();
	}
	else if (online == 1)
	{ //�ܾ����¼ ж��/ί�β��ž���
		showAllEmployeesInfo();//չʾ������Ϣ
		color(3);
		printf("�Ƿ�ί�Ρ�ж�ξ���\n1.��\n0.��\n");
		switch (get_cmd('0', '1')) {
		case '1':
			color(2);
			printf("��������Ҫж�εľ���������");
			scanf("%s", name);
			updateEmployeeByName(name);
			break;
		case '0':
			return;
		}
	}
	else if (online == 2) { //���ž����¼
		while (e != NULL) { //Ա���������ҵ�����λ��
			if (online_pid == e->employee.pid) break;
			e = e->next;
		}
		selectEmployeesByDep(e->employee.department);//չʾ������Ա��Ϣ
		color(3);
		printf("�޸�Ա��н��\n1.��Ա������޸�\n2.��Ա�������޸�\n3.�޸ı�����Ϣ\n0.����\n");
		switch (get_cmd('0', '3'))
		{
		case '1':
			color(2);
			printf("������Ҫ�޸�н����Ա��id��");
			pid = get_int();
			updateEmployeeByPid(pid);
			break;
		case '2':
			color(2);
			printf("������Ҫ�޸�н����Ա��������");
			scanf("%s", name);
			updateEmployeeByName(name);
			break;
		case '3':

			online = 3;//Ȩ����ʱ��Ϊ��ͨԱ��
			selectEmployeeByPid(online_pid);
			updateEmployeeByPid(online_pid);
			online = 2;//Ȩ�޸Ļؾ���
			break;
		case '0':
			return;
		}
	}
	else if (online == 3)
	{ //��ͨԱ����¼
		selectEmployeeByPid(online_pid);
		color(3);
		printf("�Ƿ��޸ı�����Ϣ��\n1.��\n0.��\n");
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
		printf("��ǰϵͳ�Ѿ���������Ŀǰ�޷�ʹ��\n");
	}
}
//4.1����Ա��id���޸�
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
		selectEmployeeByPid(pid);//չʾ��Ա����Ϣ
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
				printf("%s���ã��޷��޸��Լ����ʣ�\n", e->employee.name);
				return;
			}
			color(2);
			printf("�������Ա���µ�н��\n");
			newsalary = get_double();//У�� �Ϸ�����
			while (d != NULL)//�޸ĸò����ܹ���
			{
				if (strcmp(e->employee.department, d->department.dname) == 0)
					d->department.sumsalary += (newsalary - e1->employee.salary);
				d = d->next;
			}
			e1->employee.salary = newsalary;//���ǹ���
			flag = 1;
		}
		else
		{
			color(4);
			printf("%s����%s,�����޸���н�ʵ�Ȩ�ޣ�", e1->employee.name, e1->employee.department);
			return;
		}
		if (flag == 1)
			selectEmployeesByDep(e->employee.department);//�鵽�þ������ڲ��ŵ�����Ա��
		else
			printf("н���޸�ʧ��");
	}
	else if (online == 3) {
		while (e != NULL) {
			if (online_pid == e->employee.pid)
				break;
			e = e->next;
		}
		color(3);
		printf("�޸ĵ���Ϣ��\n1.�ֻ���\n2.����\n3.����\n0.�˳�\n");
		switch (get_cmd('0', '3')) {
		case '1':
			color(2);
			printf("���������µ��ֻ��ţ�");
			strcpy(e->employee.phonenum, get_phoneNum());
			flag = 1;
			break;
		case'2':
			color(2);
			printf("�������޸ĺ�ļ��᣺");
			scanf("%s", e->employee.address);
			flag = 1;
			break;
		case'3':
			while (1)
			{
				color(2);
				printf("��������������룺");
				getLine(key1, 15);
				printf("\n���ٴ�������������룺");
				getLine(key2, 15);
				if (strcmp(key1, key2) == 0)
				{
					encode(key2);   //������ܺ���
					strcpy(e->employee.password, key2);
					flag = 1;
					break;
				}
				color(4);
				printf("\n�����������벻һ��\n");
			}
			break;
		case '0': return;
		}
	}
	if (flag == 1)
	{
		color(6);
		printf("\n���޸ĺ����Ϣ���£�\n");
		selectEmployeeByPid(pid);
		color(2);
		printf("��Ϣ�޸ĳɹ�!\n");
	}
}
//4.2����Ա�������޸�(�ܾ���ί�Ρ�ж�ξ���)
void updateEmployeeByName(char* name)
{
	char newname[15];//��ί��������
	char dep1name[20];//��ί�������ڵĲ��� Ҳ����ƴ���ַ�����xx������
	char dep2name[10];//��ж���˵ľ������ڵĲ���
	EmployeeList* e = Emp;
	EmployeeList* e1 = NULL;// Ҫί�����������еĽ��λ��
	DepartmentList* d = Dep;
	int flag = 0; //��ʾû�鵽
	if (online == 1)//�ܾ����¼ʱ��ί��ж�ξ���
	{
		while (e != NULL)
		{
			if (strcmp(name, e->employee.name) == 0)
			{
				if (strcmp(e->employee.position, "�ܾ���") == 0)//�ܾ����޷�ж���Լ�
				{
					color(4);
					printf("���û�Ϊ�ܾ����޷�ж��!\n");
					return;
				}
				if (strcmp(e->employee.position, "ְԱ") == 0) //���������ְԱ������ʾ����ΪְԱ ����ж��
				{
					color(4);
					printf("%sΪְԱ���޷�ж��!\n", name);
					return;
				}
				else //��������Ǿ���  ��ж��
				{
					strcpy(e->employee.position, "ְԱ");//ְλ��xx�����ΪְԱ
					e->employee.authority = 300;//������Ȩ��
					printf("ж�γɹ�!\n");
					flag = 1;
					break;
				}
			}
			e = e->next;
		}
		if (e == NULL)
		{
			color(4);
			printf("���޴���!\nж��ʧ��!\n");
			return;
		}
		selectEmployeesByDep(e->employee.department);//չʾ�þ������ڲ��ŵ�����Ա��
		strcpy(dep2name, e->employee.department);//dep2���汻ж�ξ���Ĳ�����
		flag = 0;
		while (1)
		{
			color(2);
			printf("������Ҫί�ε��¾�������: ");
			scanf("%s", newname);
			e1 = Emp;
			while (e1 != NULL)
			{
				if (strcmp(newname, e1->employee.name) == 0)
				{
					//�ҵ��������������е�λ��,���ڶԱȲ����Ƿ�һ��
					break;
				}
				e1 = e1->next;
			}
			if (e1 == NULL)
			{
				color(4);
				printf("��˾���޴���\n");
				continue;
			}
			e = Emp;//e����ָ������ͷ
			while (e != NULL)
			{
				if (strcmp(newname, e->employee.name) == 0) //���������д���
				{
					strcpy(dep1name, e->employee.department);//�������Ĳ���
					if (strcmp(e1->employee.department, dep2name) == 0) //������һ�£����ί��
					{ //����ʱͬ���Ų���ί��
						strcat(dep1name, "����"); //�õ�department�ַ���������"xx������"
						strcpy(e->employee.position, dep1name);

						flag = 1;//ί�γɹ��󣬲��ű��о���ǵ��޸�

						while (d != NULL)//�������ű� �޸����еľ�������
						{
							if (strcmp(name, d->department.mname) == 0)
							{
								strcpy(d->department.mname, newname);//�޸�����
								e->employee.authority = 200;
								break;
							}
							d = d->next;
						}
						color(2);
						printf("ί�γɹ�!\n");
						selectEmployeesByDep(d->department.dname);//չʾ�޸ĺ�þ������ڲ��ŵ�����Ա��
						return;//����ҵ��
					}
					else
					{
						color(4);
						printf("�޷�ί��,%s��%s��!\n", newname, e1->employee.department);
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
			printf("��˾�޸�Ա����");
		}
	}
}
//5.ɾ��ҵ��
void deleteEmployee()
{
	EmployeeList* e = Emp;
	int pid;
	char name[15];
	if (online == 0)//δ��¼�ȵ�¼
		userLogin();
	else if (online == 1)//�ܾ����¼
	{
		showAllEmployeesInfo();
		color(3);
		printf("����Ա��\n1.��Ա����Ŵ���Ա��\n2.��Ա����������Ա��\n0.����\n");
		switch (get_cmd('0', '2'))
		{
		case '1':
			color(2);
			printf("������Ա����ţ�");
			pid = get_int();
			if (pid == 10000)
			{
				color(4);
				printf("��������Ա�˺��޷�ɾ����");
				return;
			}
			deleteEmployeeByPid(pid);break;
		case '2':
			color(2);
			printf("������Ҫɾ����Ա��������");
			scanf("%s", name);
			deleteEmployeeByName(name);
		case '0':return;
		}
	}
	else if (online == 2)//���ž����¼
	{
		while (e != NULL)//Ա���������ҵ�����λ��
		{
			if (online_pid == e->employee.pid) break;
			e = e->next;
		}
		selectEmployeesByDep(e->employee.department);//չʾ������Ա��Ϣ
		color(3);
		printf("����Ա��\n1.��Ա����Ŵ���Ա��\n2.��Ա����������Ա��\n0.����\n");
		switch (get_cmd('0', '2'))
		{
		case '1':
			color(2);
			printf("������Ա����ţ�");
			pid = get_int();
			if (pid == 10000)
			{
				color(4);
				printf("��������Ա�˺��޷�ɾ����");
				return;
			}
			if (pid == online_pid)
			{
				color(4);
				printf("%s%s����,���޷�ɾ���Լ���", e->employee.position, e->employee.name);
				return;
			}
			deleteEmployeeByPid(pid);//����idɾ��
			selectEmployeesByDep(e->employee.department);//չʾɾ��������Ա��Ϣ
			break;
		case '2':
			color(2);
			printf("������Ҫɾ����Ա��������");
			scanf("%s", name);
			if (strcmp(name, "admin") == 0)
			{
				color(4);
				printf("��������Ա�˺��޷�ɾ����");
				return;
			}
			if (strcmp(name, e->employee.name) == 0)
			{
				color(4);
				printf("%s%s����,���޷�ɾ���Լ���", e->employee.position, e->employee.name);
				return;
			}
			deleteEmployeeByName(name);//��������ɾ��
			selectEmployeesByDep(e->employee.department);//չʾɾ��������Ա��Ϣ
			break;
		case '0':return;
		}
	}
	else if (online == -1)
	{
		color(4);
		printf("��ǰϵͳ�Ѿ���������Ŀǰ�޷�ʹ��\n");
	}
	else
	{
		color(4);
		printf("��Ȩ�޲���!\n");
	}

}
//5.1����Ա�����ɾ��
void deleteEmployeeByPid(int pid)
{
	char department[10];
	double salary = 0;
	EmployeeList* p = Emp;  //Ա�������ͷָ��
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
					//����Ǳ�ɾ�����Ǿ���,����Ҫ��ж��->ί�ξ���,��ſ�ɾ��
					if (p->next->employee.authority == 200)
					{
						color(4);
						printf("��ɾ������%s%s,����ж��->ί�ξ���!\n", p->next->employee.position, p->next->employee.name);
						printf("1.��\n0.��\n");
						switch (get_cmd('0', '1'))
						{
						case '1': updateEmployeeByName(p->next->employee.name);//ж����ְλ
							break;
						case '0': return;
						}
					}
					strcpy(department, p->next->employee.department);//department��¼���Ա�����ڲ��� 
					salary = p->next->employee.salary;//salary��¼���Ա��ԭ���Ĺ���
					if (p->next->next == NULL)//��������һ���ڵ�  ɾ�����������ı�
					{
						q = p->next;
						p->next = NULL;
						free(q);
						flag = 1;break;//ɾ���ɹ�
					}
					//������м��ĳ�����
					q = p->next;
					p->next = q->next;
					free(q);
					flag = 1;break;//ɾ���ɹ�
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
			printf("���Ϊ%d��Ա�������ڣ�\n", pid);
			return;
		}
		printf("ɾ���ɹ���\n");
	}
	else if (online == 2)
	{
		EmployeeList* e = Emp;
		while (e != NULL)//��½���������е�λ��  ����ԱȲ����Ƿ�һ��
		{
			if (e->employee.pid == online_pid) break;
			e = e->next;
		}
		while (p != NULL)
		{
			if (p->next != NULL)
				if (pid == p->next->employee.pid)//�����ҵ�idһ�µ�Ա��
				{
					//���Ϊpid��Ա���Ƿ����ڸþ���Ĳ���
					if (strcmp(p->next->employee.department, e->employee.department) == 0)
					{
						strcpy(department, p->next->employee.department);//department��¼���Ա�����ڲ��� 
						salary = p->next->employee.salary;//salary��¼���Ա��ԭ���Ĺ���
						if (p->next->next == NULL)//��������һ���ڵ�  ɾ�����������ı�
						{
							q = p->next;
							p->next = NULL;
							free(q);
							flag = 1;break;//ɾ���ɹ�
						}
						//������м��ĳ�����
						q = p->next;
						p->next = q->next;
						free(q);
						flag = 1;break;//ɾ���ɹ�
					}
					else
					{
						flag = 1;
						color(4);
						printf("���Ϊ%d��Ա��������%s", pid, e->employee.department);
					}
				}
			p = p->next;
		}
		if (flag == 0)
		{
			color(4);
			printf("���Ϊ%d��Ա�������ڣ�\n", pid);
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
		printf("ɾ���ɹ���\n");
	}
}
//5.2����Ա������ɾ��
void deleteEmployeeByName(char* name)
{
	char department[10];
	double salary = 0;
	EmployeeList* p = Emp;  //Ա�������ͷָ��
	EmployeeList* q = p;
	DepartmentList* d = Dep;
	int flag = 0;
	if (online == 1)
	{
		while (p != NULL)
		{
			if (p->next != NULL)
				if (strcmp(name, p->next->employee.name) == 0)//�ҵ�����һ�µ�Ա��
				{
					//����Ǳ�ɾ�����Ǿ���,����Ҫ��ж��->ί�ξ���,��ſ�ɾ��
					if (p->next->employee.authority == 200)
					{
						color(4);
						printf("��ɾ������%s%s,����ж��->ί�ξ���!\n", p->next->employee.position, p->next->employee.name);
						printf("1.��\n0.��\n");
						switch (get_cmd('0', '1'))
						{
						case '1': updateEmployeeByName(p->next->employee.name);//ж����ְλ
						case '0': return;
						}
						return;
					}
					strcpy(department, p->next->employee.department);//department��¼���Ա�����ڲ��� 
					salary = p->next->employee.salary;//salary��¼���Ա��ԭ���Ĺ���
					if (p->next->next == NULL)//��������һ���ڵ�  ɾ�����������ı�
					{
						q = p->next;
						p->next = NULL;
						free(q);
						flag = 1;break;//ɾ���ɹ�
					}
					//������м��ĳ�����
					q = p->next;
					p->next = q->next;
					free(q);
					flag = 1;break;//ɾ���ɹ�
					break;
				}
			p = p->next;
		}
		if (flag == 0)
		{
			color(4);
			printf("����Ϊ%s��Ա�������ڣ�", name);
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
		printf("ɾ���ɹ���\n");
	}
	else if (online == 2)
	{
		EmployeeList* e = Emp;
		while (e != NULL)//��½�����������е�λ��  ����ԱȲ����Ƿ�һ��
		{
			if (e->employee.pid == online_pid) break;
			e = e->next;
		}
		while (p != NULL)
		{
			if (p->next != NULL)
				if (strcmp(name, p->next->employee.name) == 0)
				{
					//����Ϊname��Ա���Ƿ����ڸþ���Ĳ���
					if (strcmp(p->next->employee.department, e->employee.department) == 0)
					{
						strcpy(department, p->next->employee.department);//department��¼���Ա�����ڲ��� 
						salary = p->next->employee.salary;//salary��¼���Ա��ԭ���Ĺ���
						if (p->next->next == NULL)//��������һ���ڵ�  ɾ�����������ı�
						{
							q = p->next;
							p->next = NULL;
							free(q);
							flag = 1;break;//ɾ���ɹ�
						}
						//������м��ĳ�����
						q = p->next;
						p->next = q->next;
						free(q);
						flag = 1;break;//ɾ���ɹ�
					}
					else
					{
						flag = 1;
						printf("Ա��%s������%s", name, e->employee.department);
					}
				}
			p = p->next;
		}
		if (flag == 0)
		{
			printf("����Ϊ%s��Ա�������ڣ�", name);
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
		printf("ɾ���ɹ���\n");
	}
}
//7.Ա���������� ����ͬ������һ��  Ȼ��н�ʸߵ�����
void employeesSort()
{
	EmployeeList* p = NULL;
	EmployeeList* q = NULL;
	EmployeeList* index = NULL;
	//1.ѡ������ ����������
	for (p = Emp; p != NULL; p = p->next)
	{
		index = p;
		for (q = p->next; q != NULL; q = q->next)
		{
			if (strcmp(index->employee.department, q->employee.department) > 0)
				index = q;//�ҵ��±�
		}
		if (index != p)
			swap(p, index);
	}
	//2.ð�����򣬲���һ�µ������ ��н����
	for (p = Emp; p != NULL; p = p->next)
	{
		for (q = Emp; q->next != NULL; q = q->next)
		{
			//���Ų�ͬ��������֮�䲻�ý���
			if (strcmp(q->employee.department, q->next->employee.department) != 0)
				continue;
			if (q->employee.salary < q->next->employee.salary)
				swap(q, q->next);
		}
	}
}
//swap���� ����ʱ���������
void swap(EmployeeList* p, EmployeeList* q)
{
	//temp=q; q=t;t=temp
	Employee temp = { 0 };
	temp = p->employee;
	p->employee = q->employee;
	q->employee = temp;
}
