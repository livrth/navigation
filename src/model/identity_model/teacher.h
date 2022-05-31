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
    string teacher_id;                    //教职工号
    string name;                          //教师姓名
    vector<string> teaching_course_name;  //目前正在上的所有课名称
    vector<string> teaching_course_id;    //所有正在上的课的ID 可能会用到这个数组

    Teacher();
    Teacher(string id, string name);

    //教师操作菜单
    void operMenu();

    void set_homework();  //布置作业

    void check_duplicate(string course_id, int times);      //作业查重
    void decompress_homework();  //解压作业

    void mark_homework();  //教师批改作业

    void log(string sth);
};