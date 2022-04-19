#pragma once
#include <iostream>
#include <string>
using namespace std;

class Teacher {
   public:
    string teacher_id;  //教职工号
    string name;        //教师姓名

    Teacher();
    Teacher(string id);

    //教师操作菜单
    void operMenu();

    //教师布置作业
    void set_homework();

    //教师批改作业
    void check_homework();
};