#pragma once
#include <iostream>
#include <string>
using namespace std;

class Student {
   public:
    string stu_name,  //学生姓名
        stu_id;       //学号 唯一区分学生
    Student();
    Student(string id);

    //学生界面操作的菜单
    virtual void operMenu();
    
};