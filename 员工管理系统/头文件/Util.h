#ifndef UTIL_H
#define UTIL_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <conio.h>		//�����������뺯��ͷ�ļ�
#include <Windows.h>	//�޸Ŀ���̨������ɫ�����������˸�ʱ�������
//���ߺ���
void color(int x);//��ӡ��ɫ�޸� 0 ��ɫ 1��ɫ 2��ɫ 3��ɫ 4��ɫ 5��ɫ 6��ɫ 7��ɫ 8�Ұ�
char* getLine(char* buf, int len);      //��������ת����*�� 
char get_cmd(char start, char end);     // ����̨��ʾ�������� ҵ���߼�����
void encode(char* password);    //������ܺ���
void decode(char* password);    //������ܺ���
double get_double(void);        //У���û�����ֱ��Ϊ�Ϸ�������
int get_int(void);				//У���û�����ֱ��Ϊ�Ϸ�����
char* get_phoneNum(void);
#endif