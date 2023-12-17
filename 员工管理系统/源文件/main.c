#define _CRT_SECURE_NO_WARNINGS
#include "Employee.h"
#include "LoginStatus.h"
#include "Department.h"
#include "EmsSystem.h"
#include "Util.h"



// 主函数
int main()
{
	initSystem();    // 系统初始化
	startSystem();   // 系统开始运行
	exitSystem();    // 系统结束
	return 0;
}
