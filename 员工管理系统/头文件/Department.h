#ifndef DEPARTMENT_H
#define DEPARTMENT_H
#include "LoginStatus.h"
#include "Employee.h"
//������Ϣ
typedef struct Department
{
	char dname[10];     //��������
	char mname[20];     //���ž�������
	int  dnum;          //����������
	double sumsalary;   //����Ա��н�ʺ�
}Department;
//������̬�������� ������Ϣ
typedef struct DNode
{
	struct Department department;       //������  Ա����Ϣ
	struct DNode* next;                 //ָ����

}DepartmentList;
DepartmentList* createDepartmentList();
//ȫ�ֱ���
DepartmentList* Dep;    //��Ų�����Ϣ����ͷָ��  �������ҵ�����  ��Ҫ������ֵ


//2.��ѯ
void showALLDepartmentInfo(void);               //չʾ���в��Ÿſ�

#endif 
