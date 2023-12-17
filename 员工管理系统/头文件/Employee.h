#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include "LoginStatus.h"
#include "Department.h"
#include "EmsSystem.h"
//员工信息
typedef struct Employee
{
	int  pid;           //用户账号 自增主键（从202100开始） 总经理账号固定10000 密码666
	char name[20];      //姓名
	char password[20];  //用户密码     
	char address[20];   //籍贯
	char phonenum[20];  //手机号
	double salary;      //薪资
	char department[10];//所属部门
	int  authority;     //权限管理 100=总经理  200=部门经理  300=普通员工
	char position[15];  //职位
}Employee;
//创建动态单链表结点 员工信息
typedef struct ENode
{
	struct Employee employee;           //数据域  员工信息
	struct ENode* next;                 //指针域
}EmployeeList;
EmployeeList* createEmployeeList(void);         //初始化员工信息链表
//2.查询
void showAllInfo(void);                         //查询员工信息  菜单中调用

//具体查询
void showAllEmployeesInfo(void);                //查询所有员工信息       
void selectEmployeesByDep(char* department);    //依据部门查询员工信息   
void selectEmployeeByPid(int pid);              //依据编号查询员工信息  
void selectEmployeeByName(char* name);          //依据姓名查询员工信息   
void selectEmployeesByAddress(char* address);   //依据籍贯查询员工信息 

//3.新增员工
void addEmployee(void);                     //菜单中调用,新增员工信息

//4.修改员工
void updateEmployee(void);                  //主菜单中调用
void updateEmployeeByName(char* name);      //依据姓名修改员工信息 
void updateEmployeeByPid(int pid);          //依据员工编号修改员工信息 

//5.删除员工
void deleteEmployee(void);                  //主菜单调用
void deleteEmployeeByName(char* name);      //依据姓名删除员工信息
void deleteEmployeeByPid(int pid);          //依据编号删除员工信息

//7.排序 先按部门排，相同部门排一起 部门相同再按薪资排 
void employeesSort(void);   //所有员工排序
void swap(EmployeeList* p, EmployeeList* q);//交换节点数据函数

//全局变量
EmployeeList* Emp;      //存放员工信息链表头指针  方便各种业务操作  不要给他赋值

#endif