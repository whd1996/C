#ifndef EMSSYSTEN_H
#define EMSSYSTEN_H
//函数声明
//系统函数
void initSystem(void);      // 系统初始化（从文件读取相关数据信息到内存）
void startSystem(void);     // 系统开始运行
void menu(void);            // 生成主菜单
void exitSystem(void);      // 系统结束

//业务函数
//用户登录
void userLogin(void);
//登出
void userLogout(void);          //用户登出


#endif
