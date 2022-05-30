#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct logger_t {
    string now;
    string kind;
    string id;
    string sth;
    logger_t(string k, string i, string s) {
        time_t timep;
        time(&timep);
        now = asctime(gmtime(&timep));
        kind = k;
        id = i;
        sth = s;
    }
};

class Teacher {
   public:
    string teacher_id;       //教职工号
    string name;             //教师姓名
    string teaching_course;  //目前正在上的课

    Teacher();
    Teacher(string id, string name);

    //教师操作菜单
    void operMenu();

    //教师布置作业
    void set_homework();

    //教师批改作业
    void check_homework();
    void log(string sth);
};