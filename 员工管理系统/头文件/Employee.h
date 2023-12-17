#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include "LoginStatus.h"
#include "Department.h"
#include "EmsSystem.h"
//Ա����Ϣ
typedef struct Employee
{
	int  pid;           //�û��˺� ������������202100��ʼ�� �ܾ����˺Ź̶�10000 ����666
	char name[20];      //����
	char password[20];  //�û�����     
	char address[20];   //����
	char phonenum[20];  //�ֻ���
	double salary;      //н��
	char department[10];//��������
	int  authority;     //Ȩ�޹��� 100=�ܾ���  200=���ž���  300=��ͨԱ��
	char position[15];  //ְλ
}Employee;
//������̬�������� Ա����Ϣ
typedef struct ENode
{
	struct Employee employee;           //������  Ա����Ϣ
	struct ENode* next;                 //ָ����
}EmployeeList;
EmployeeList* createEmployeeList(void);         //��ʼ��Ա����Ϣ����
//2.��ѯ
void showAllInfo(void);                         //��ѯԱ����Ϣ  �˵��е���

//�����ѯ
void showAllEmployeesInfo(void);                //��ѯ����Ա����Ϣ       
void selectEmployeesByDep(char* department);    //���ݲ��Ų�ѯԱ����Ϣ   
void selectEmployeeByPid(int pid);              //���ݱ�Ų�ѯԱ����Ϣ  
void selectEmployeeByName(char* name);          //����������ѯԱ����Ϣ   
void selectEmployeesByAddress(char* address);   //���ݼ����ѯԱ����Ϣ 

//3.����Ա��
void addEmployee(void);                     //�˵��е���,����Ա����Ϣ

//4.�޸�Ա��
void updateEmployee(void);                  //���˵��е���
void updateEmployeeByName(char* name);      //���������޸�Ա����Ϣ 
void updateEmployeeByPid(int pid);          //����Ա������޸�Ա����Ϣ 

//5.ɾ��Ա��
void deleteEmployee(void);                  //���˵�����
void deleteEmployeeByName(char* name);      //��������ɾ��Ա����Ϣ
void deleteEmployeeByPid(int pid);          //���ݱ��ɾ��Ա����Ϣ

//7.���� �Ȱ������ţ���ͬ������һ�� ������ͬ�ٰ�н���� 
void employeesSort(void);   //����Ա������
void swap(EmployeeList* p, EmployeeList* q);//�����ڵ����ݺ���

//ȫ�ֱ���
EmployeeList* Emp;      //���Ա����Ϣ����ͷָ��  �������ҵ�����  ��Ҫ������ֵ

#endif