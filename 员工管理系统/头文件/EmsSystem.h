#ifndef EMSSYSTEN_H
#define EMSSYSTEN_H
#include "Employee.h"
#include "LoginStatus.h"
#include "Department.h"
#include "Util.h"
//��������
//ϵͳ����
void initSystem(void);      // ϵͳ��ʼ�������ļ���ȡ���������Ϣ���ڴ棩
void startSystem(void);     // ϵͳ��ʼ����
void menu(void);            // �������˵�
void exitSystem(void);      // ϵͳ����

//ҵ����
//�û���¼
void userLogin(void);
//�ǳ�
void userLogout(void);          //�û��ǳ�


#endif
