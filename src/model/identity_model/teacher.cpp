#include "teacher.h"
// #include "homework.h"
#include <fstream>
#include <iostream>
using namespace std;

Teacher::Teacher() {
}

Teacher::Teacher(string id, string name) {
    this->teacher_id = id;
    this->name = name;
}

void Teacher::set_homework() {
    // TODO: 下面样例仅仅作为测试用
    //后期完善要和文件交互
    string course_name, course_id;
    cout << "请输入您要布置的作业: ";
    cin >> course_name;
    cout << "请输入该课程的编号: ";
    cin >> course_id;
    // Homework temp_hw(this->teacher_id, course_id, course_name);
}

//批改作业
void Teacher::mark_homework() {
    string course_id;    //课程编号
    string course_name;  //课程名称
    int hw_times;        //作业次数

    cout << "请输入要批改作业的课程名称: ";
    cin >> course_name;
    //教师输入课程名称，然后从 course_colleciton.txt 中查到课程id 赋值给 course_id;
    // string hw_path = ......

    cout << "请输入要批改的作业次数: ";
    cin >> hw_times;

    this->decompress_homework();                 //先调用解压作业
    this->check_duplicate(course_id, hw_times);  //然后得到查重结果
}

//解压作业
void Teacher::decompress_homework() {
}

//得到某次作业的查重结果
void Teacher::check_duplicate(string course_id, int times) {
}

void Teacher::log(string sth) {
    logger_t addition = logger_t("teacher", teacher_id, sth);
    ofstream ofs1;
    string log_file = "../../doc/admin";
    ofs1.open(log_file, ios::app);
    ofs1 << addition.now << " " << addition.kind << " " << addition.id << " " << addition.sth << endl;
    ofs1.close();
}