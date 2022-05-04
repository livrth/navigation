#pragma once
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
using namespace std;
struct single_course_a {
    string date;
    int seq;
    string place;
    string campus;
    int building_id;
    string course_name, course_id;
};
struct exam_a {
    int week;
    string date;
    int sh, sm, fh, fm;
    string campus;
    string place;
};
struct material_a {
    int weight;
    string name;
    string id;
};
struct whole_course {
    int ref_book_number;
    int number;
    int homework_number;
    int material_number;
    int total_weeks;

    string course_id;
    string course_name;
    exam_a final;
    vector<string> ref_books;
    vector<single_course_a> course_table;
    vector<material_a> materials;
    vector<string> hws;
    string teacher_name;
    string teacher_id;
    string course_qun;
    vector<string> stu_ids;
    int student_number;
};
struct single_activity_a {
    string date;
    int sh, sm, fh, fm;
    string place;
    string name;
};
class Admin {
   public:
    string user_name, pwd;

    //班级修改相关

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

    void delete_course_table_term(string stu_id, string date, int seq);
    void add_course_table_term(string stu_id, single_course_a n);
};