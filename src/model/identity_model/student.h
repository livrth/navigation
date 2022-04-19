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
    virtual void operMenuSub(); 

    //课内信息管理和查询
    void query_by_course_name();
    void query_by_course_table();

    void upload_course_material(); //上传课程资料
    void upload_home_work(); //上传作业

    //课外信息管理和查询

    //课程导航
};