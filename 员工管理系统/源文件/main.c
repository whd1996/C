#define _CRT_SECURE_NO_WARNINGS
#include "Employee.h"
#include "LoginStatus.h"
#include "Department.h"
#include "EmsSystem.h"
#include "Util.h"



// ������
int main()
{
	initSystem();    // ϵͳ��ʼ��
	startSystem();   // ϵͳ��ʼ����
	exitSystem();    // ϵͳ����
	return 0;
}
