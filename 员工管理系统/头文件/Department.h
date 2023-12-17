#ifndef DEPARTMENT_H
#define DEPARTMENT_H
#include "LoginStatus.h"
#include "Employee.h"
//部门信息
typedef struct Department
{
	char dname[10];     //部门名称
	char mname[20];     //部门经理名称
	int  dnum;          //部门总人数
	double sumsalary;   //部门员工薪资和
}Department;
//创建动态单链表结点 部门信息
typedef struct DNode
{
	struct Department department;       //数据域  员工信息
	struct DNode* next;                 //指针域

}DepartmentList;
DepartmentList* createDepartmentList();
//全局变量
DepartmentList* Dep;    //存放部门信息链表头指针  方便各种业务操作  不要给他赋值


//2.查询
void showALLDepartmentInfo(void);               //展示所有部门概况

#endif 
