#include "Department.h"
#include "Util.h"
//β�巨�������ű���������Ϣ
DepartmentList* createDepartmentList()
{
	int dCount = 0;   //������Ԫ�ظ��� ��Ա������
	DepartmentList* head;
	DepartmentList* p1, * p2;
	int num = 0;
	FILE* dfrp = fopen("../Ա������ϵͳ/��Դ�ļ�/department.txt", "r");
	if (NULL == dfrp)
	{
		printf("������Ϣ�ļ� ��ʧ��!\n");
		exit(0);
	}
	p1 = p2 = (DepartmentList*)malloc(sizeof(struct DNode));
	//���²� ���� 3 2300
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
		if (feof(dfrp) != 0)break;//�ļ���ȡ���� ����ѭ��
		num = fscanf(dfrp, "%s %s %d %lf\n", p1->department.dname, p1->department.mname,
			&p1->department.dnum, &p1->department.sumsalary);
	}
	p2->next = NULL;
	return head;
}
// 2.��ѯҵ��
void showAllInfo(void)
{
	char department[10];    //����
	int pid;                //Ա�����
	char address[20];       //Ա������
	char name[15];          //Ա������
	EmployeeList* p = Emp;  //Ա�������ͷָ��

	if (online == 1)    //����ܾ����Ѿ���¼
	{
		color(3);
		printf("1.��ʾ����Ա����Ϣ\n2.��ʾ���Ÿſ�\n3.��������ѯ\n4.��Ա���Ų�ѯ\n5.�����Ų�ѯ\n6.�������ѯ\n0.����\n");
		switch (get_cmd('0', '6'))
		{
		case '1':
			showAllEmployeesInfo();//��ʾ����Ա����Ϣ
			break;
		case '2':
			showALLDepartmentInfo();//��ʾ���в��Ÿſ�  ����н�ʺ�
			break;
		case '3':
			//��������
			color(2);
			printf("������������ ");
			scanf("%s", name);          //��������
			selectEmployeeByName(name); //����������ѯ
			break;
		case '4':
			//��Ա���Ų�
			color(2);
			printf("������Ա���ţ� ");
			pid = get_int();
			selectEmployeeByPid(pid);   //����Ա���Ų�
			break;
		case '5':
			//���벿�Ų�
			color(3);
			printf("\n��ѡ��Ա�����ţ�\n1.���²�\n2.����\n3.���۲�\n4.�г���\n");//����
			switch (get_cmd('1', '4'))
			{
			case '1':   strcpy(department, "���²�");break;
			case '2':   strcpy(department, "����");break;
			case '3':   strcpy(department, "���۲�");break;
			case '4':   strcpy(department, "�г���");break;
			}
			selectEmployeesByDep(department);
			break;
		case '6':
			//���뼮�� ֱϽ�л�ʡ�� �� ������������������������
			color(2);
			printf("�����뼮�᣺ ");
			scanf("%s", address);       //���뼮��
			selectEmployeesByAddress(address);
			break;
		case '0':return;
		}
	}
	else if (online == 2)//���ĳ�����ž����¼
	{
		color(3);
		printf("1.��ʾ������Ա����Ϣ\n2.��ʾ�����Ÿſ�\n3.��������ѯ\n4.��Ա���Ų�ѯ\n5.�������ѯ\n6.��ѯ������Ϣ\n0.����\n");
		switch (get_cmd('0', '6'))
		{
		case '1':
			while (p != NULL)//�ҵ���¼�����ڵĲ���  ���ڲ�ѯ��ͬ���ŵ�Ա��
			{
				if (p->employee.pid == online_pid)
					break;
				p = p->next;
			}
			selectEmployeesByDep(p->employee.department);//���������ڲ��Ų�Ա����Ϣ
			break;
		case '2':
			showALLDepartmentInfo();//��ʾ�����Ÿſ�  ����н�ʺ�
			break;
		case '3':
			//��������
			color(2);
			printf("������������ ");
			scanf("%s", name);          //��������
			selectEmployeeByName(name); //����������ѯ
			color(2);
			break;
		case '4':
			//��Ա���Ų�
			color(2);
			printf("������Ա���ţ� ");
			pid = get_int();
			selectEmployeeByPid(pid);   //����Ա���Ų�
			break;
		case '5':
			color(2);
			printf("������Ա�����᣺ ");
			scanf("%s", &address);
			selectEmployeesByAddress(address);//���뼮���Ա����Ϣ ֱϽ�л�ʡ�� �� ������������������������
			break;
		case '6'://��ѯ������Ϣʱ  ������ͨԱ�� ������ʾ����
			online = 3;
			selectEmployeeByPid(online_pid);
			online = 2;
			break;
		case '0':return;
		}

	}
	else if (online == 3)//��ͨԱ����¼
	{
		color(3);
		printf("1.��ʾ������Ϣ\n2.��ʾ��˾���Ÿſ�\n0.����\n");

		switch (get_cmd('0', '2'))
		{
		case '1':
			selectEmployeeByPid(online_pid);    //����¼�ߵı��
			break;
		case '2':
			showALLDepartmentInfo();//��ʾ��˾���Ÿſ�  ������н�ʺ�
			break;
		case '0':return;
		}
	}
	else if (online == 0)
	{
		//δ��¼ʱ  չʾ���в�����Ϣ  ����ʾ���������Ͳ��ž�������
		showALLDepartmentInfo();
		color(4);
		printf("����,�����ѯ������Ϣ,���ȵ�¼!");

	}
	else if (online == -1)
	{
		color(4);
		printf("��ǰϵͳ�Ѿ���������Ŀǰ�޷�ʹ��\n");
	}
	else
	{
		printf("����û�е�¼\n");
	}
}

//��ѯ���ű���Ϣ
void showALLDepartmentInfo()
{
	DepartmentList* p = Dep;
	EmployeeList* e = Emp;
	int count = 0;//��ѯ��¼��
	double sum = 0;//н���ܺ�

	if (online == 1) //������ܾ����  ����ʾ�������� �������� ���в�����Ӧ��н���ܶ�
	{
		color(6);
		printf("��������  ���ž���  ��������  Ӧ��н�ʺ�\n");
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
		printf("����%d����¼,Ӧ����н�ܺ�Ϊ%.2lf��", count, sum);
	}
	else if (online == 2)//����ǲ��ž����  ����ʾ�������� ���� �ò���Ӧ��н���ܶ�
	{
		while (e != NULL)//���ȴ�Ա���������ҵ��������ڵĽ��e
		{
			if (online_pid == e->employee.pid)
				break;
			e = e->next;
		}
		color(6);
		printf("��������  ��������  Ӧ��н�ʺ�\n");
		color(7);
		while (p != NULL)//�ٲ�ѯ�ò�������
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
		printf("Ӧ����н�ܺ�Ϊ%.2lf��", sum);
	}
	else  //�������ͨԱ����δ��¼�߲�  ��ֻ��ʾ�������� ���� ���ž�������
	{
		color(6);
		printf("��������  ���ž���  ��������\n");
		color(7);
		while (p != NULL)
		{
			printf("%-11s%-12s%-5d\n", p->department.dname, p->department.mname,
				p->department.dnum);
			count++;
			p = p->next;
		}
		color(6);
		printf("����%d����¼!\n", count);
	}
}