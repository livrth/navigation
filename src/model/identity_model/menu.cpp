#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <ctime>

#include "admin.h"
#include "student.h"
#include "teacher.h"
#include "../course_model/course.h"

//实现除了登录界面之外所有的图形化打印菜单

void Student::operMenu() {
    time_t now = time(0);
    char* dt = ctime(&now);
    cout << endl;
    cout << "欢迎学生：" << this->stu_name << " 登录! " << dt << endl;
    cout << "\t\t -----------------------\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     1.课程名称查询    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     2.课表课程查询    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     3.设置课外活动    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     4.时间查找课程    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     5.查询课外活动    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     6.设定活动闹钟    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     7.进行路径导航    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     0.注销登出账号    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t -----------------------\n";
    cout << "请选择您的操作: ";
    
}

void Student::operMenuSub() {
    //
}

void Teacher::operMenu() {
    system("cls");
    time_t now = time(0);
    char* dt = ctime(&now);
    cout << endl;
    cout << "欢迎教师：" << this->name << " 登录! " << dt << endl;
    cout << "\t\t -----------------------\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     1.教师布置作业    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     2.教师批改作业    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     0.注销登出账号    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t -----------------------\n";
    cout << "请选择您的操作: ";
}

void Admin::operMenu() {
    system("cls");
    time_t now = time(0);
    char* dt = ctime(&now);
    cout << endl;
    cout << "欢迎管理员: " << this->user_name << " 登录! " << dt << endl;
    cout << "\t\t -----------------------\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     1.发布考试信息    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     2.设置新的课程    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     3.修改原有课程    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     0.注销登出账号    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t -----------------------\n";
    cout << "请选择您的操作: ";
}

void Course::operMenu(){

}
