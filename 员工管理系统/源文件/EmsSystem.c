#include "EmsSystem.h"

// ϵͳ��ʼ��
void initSystem(void)
{
	//��������洢����
	Emp = createEmployeeList();
	Dep = createDepartmentList();
	color(3);
	printf("ϵͳ������...\n");
}
// ϵͳ��ʼ����
void startSystem(void)
{
	// ����ϵͳ��ҵ�����̿���
	while (1)
	{
		menu();
		switch (get_cmd('0', '6')) // ��ȡ��������
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
// ϵͳ����
void exitSystem()
{
	EmployeeList* emp = Emp;
	DepartmentList* dep = Dep;
	// ��ֻд��ʽ���ļ�employee.txt���ļ��������������ա�
	FILE* efwp = fopen("../Ա������ϵͳ/��Դ�ļ�/employee.txt", "w");
	// ��ֻд��ʽ���ļ�department.txt���ļ��������������ա�
	FILE* dfwp = fopen("../Ա������ϵͳ/��Դ�ļ�/department.txt", "w");
	if (online == 1)//�ܾ�������ʱ �����򱣴���������
	{
		color(3);
		printf("1.���򱣴��˳�\n0.ֱ���˳�\n");
		switch (get_cmd('0', '1'))
		{
		case '1':employeesSort();//����
			showAllEmployeesInfo();//��ӡ������
			break;
		case '0':break;
		}
	}
	printf("����¼��:\n");

	color(3);
	printf("Ա����Ϣд���ļ� employee.txt\n");
	printf("Ա����Ϣд���ļ���...\n");
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
	printf("Ա����Ϣд���ļ��ɹ�!\n");
	printf("������Ϣд���ļ� department.txt\n");
	printf("������Ϣд���ļ���...\n");
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
	printf("������Ϣд���ļ��ɹ�!\n");
	// �ͷ��ڴ桢��������
	free(Emp);
	free(Dep);
	color(2);
	printf("�����˳�...\n");
	color(7);
}
// �������˵�
void menu(void)
{   //color:  0 ��ɫ 1��ɫ 2��ɫ 3��ɫ 4��ɫ 5��ɫ 6��ɫ 7��ɫ 8�Ұ�
	color(2);
	system("cls");
	printf("\n");
	printf("********************************\n");
	printf("|                              |\n");
	printf("|     Ա����Ӷ�������ϵͳ     |\n\n");
	printf("*        1.��¼                *\n");
	printf("|        2.��ѯ                |\n");
	printf("|        3.����                |\n");
	printf("|        4.�޸�                |\n");
	printf("*        5.ɾ��                *\n");
	printf("*        6.�ǳ�                *\n");
	printf("|        0.�����˳�            |\n");
	printf("|                              |\n");
	printf("********************************\n");
}

//ҵ����ʵ��
// 1.�û���¼
void userLogin(void)
{
	EmployeeList* p = Emp;//Ա������ͷָ���p
	if (online == 0)    //���û�е�¼
	{
		int pwdCount = 0;//�����������
		color(4);
		printf("���ȵ�¼!\n");
		while (pwdCount < 3)
		{
			int entry_pid = 0; //�˺� /Ա����
			char entry_pw[20] = { 0 };  //����
			color(7);
			printf("������Ա����:");
			entry_pid = get_int();//��������Ƿ�Ϊ������
			printf("����������: ");
			getLine(entry_pw, 20);
			encode(entry_pw);//�������ַ��ȼ����ٱȽ�  ��Ϊ�����������Ǽ��ܺ��
			// ��������Ա��
			while (p != NULL)
			{
				// ���ݳ���У��
				if (entry_pid == 0 || strlen(entry_pw) == 0)
				{
					printf("Ա���Ż����벻��Ϊ��\n");
					pwdCount++;
					break;
				}
				// �ɹ�ƥ���˺�����  �������decode(pwd);
				else if ((p->employee.pid == entry_pid) && strcmp(p->employee.password, entry_pw) == 0)
				{

					online_pid = entry_pid;
					if (p->employee.authority == 100)
					{
						online = 1;//��½��Ϊ�ܾ���
						printf("\n�ܾ�����½�ɹ�!\n");
						return;
					}
					else if (p->employee.authority == 200)
					{
						online = 2;//��½��Ϊ���ž���                       
						printf("\n%s���� %s����½�ɹ�!\n", p->employee.department, p->employee.name);
						return;
					}
					else if (p->employee.authority == 300)
					{
						online = 3;//��½��Ϊ��ͨԱ��               
						printf("\n%sְԱ %s����½�ɹ�!\n", p->employee.department, p->employee.name);
						return;
					}
				}
				p = p->next;//��������
			}
			p = Emp;//����ָ��ͷ��� ��ʼ��һ��У��
			printf("\n��½ʧ�ܣ��û�id���������\n");
			pwdCount++;
		}
		online = -1;//����ϵͳ
		color(4);
		printf("����������Σ���ǰϵͳ�Ѿ���������Ŀǰ�޷�ʹ��\n");
	}
	else if (online == 1)
	{
		printf("�ܾ������ã����ѵ�¼!\n");
	}
	else if (online == 2)
	{
		while (p != NULL)//�ҵ���ǰ��¼���������е�λ��
		{
			if (p->employee.pid == online_pid) break;
			p = p->next;
		}
		printf("%s����%s���ã����ѵ�¼!\n", p->employee.department, p->employee.name);
	}
	else if (online == 3)
	{
		while (p != NULL)//�ҵ���ǰ��¼���������е�λ��
		{
			if (p->employee.pid == online_pid) break;
			p = p->next;
		}
		printf("%sְԱ%s���ã����ѵ�¼\n", p->employee.department, p->employee.name);
	}
	else
	{
		color(4);
		printf("��ǰϵͳ�Ѿ���������Ŀǰ�޷�ʹ��\n");
	}
}

// 6.�û��ǳ�
void userLogout(void)
{
	if (online == 1 || online == 2 || online == 3)  //����Ѿ���¼
	{
		online = 0;
		printf("�ǳ��ɹ�\n");
	}
	else if (online == -1)
	{
		color(4);
		printf("��ǰϵͳ�Ѿ���������Ŀǰ�޷�ʹ�ã�\n");
	}
	else
	{
		color(4);
		printf("����δ��¼!\n");
	}
}

