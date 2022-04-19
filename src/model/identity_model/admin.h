#pragma once
#include <string>
using namespace std;

class Admin {
   public:
    string user_name, pwd;

    Admin();
    Admin(string user_name);

    //管理员菜单
    void operMenu();

    //发布考试时间和考试地点
    void release_exam();

    //发布新课程
    void release_new_course();

    //修改原有课程
    void change_course();
};