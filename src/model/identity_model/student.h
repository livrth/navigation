#pragma once
#include <iostream>
#include <string>
using namespace std;

class Student {
   public:
    string stu_name,  //学生姓名
        stu_id;       //学号 唯一区分学生
    Student();
    Student(string id, string name);

    //学生界面操作的菜单
    void operMenu();
    void operMenuSub();

    //课内信息管理和查询
    void query_by_course_name();   //通过课程名称查询
    void query_by_course_table();  //通过课表查询

    void upload_course_material();  //上传课程资料
    void upload_home_work();        //上传作业

    //课外信息管理和查询
    void query_activity();      //查询课外活动
    void set_activity_alarm();  //设定课外活动闹钟

    //课程导航
    void guide_now();  //进行课程路径导航
};