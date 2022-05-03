#pragma once
#include <string>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
using namespace std;
struct single_course_a{
   string date;
   int seq;
   string place;
   string campus;
   int buliding_id;
};
struct exam_a{
    int week;
    string date;
    int st_hour,st_min,fi_hour,fi_min;
    string campus;
    string place;
};
struct single_activity_a{
    string date;
    int sh, sm, fh, fm;
    string place;
    string name;
    string clock_state;
};
class Admin {
   public:
   string user_name, pwd;
    //课程修改，发布相关
    exam_a final;
    vector<string> ref_books;
    vector<single_course_a> course_table;
    string teacher_name;
    string teacher_id;
    string course_qun;
    vector<string> stu_ids;
    int student_number;
    int ref_book_number;
    //班级修改相关
    int ca_number;
    vector<single_activity_a> activities;
    Admin();
    Admin(string user_name);
    
   
    //管理员菜单
    void operMenu();

    //发布考试时间和考试地点
    void change_activity();

    //发布新课程
    void release_new_course();

    //修改原有课程
    void change_course();
};