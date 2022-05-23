#include "teacher.h"
// #include "homework.h"
#include <iostream>

using namespace std;

Teacher::Teacher() {
}

Teacher::Teacher(string id, string name) {
    this->teacher_id = id;
    this->name = name;
}

void Teacher::set_homework() {
    //TODO: 下面样例仅仅作为测试用
    //后期完善要和文件交互
    string course_name, course_id;
    cout << "请输入您要布置的作业: ";
    cin >> course_name;
    cout << "请输入该课程的编号: ";
    cin >> course_id;
    // Homework temp_hw(this->teacher_id, course_id, course_name);
    
}

//批改作业
//同时系统实现查重
void Teacher::check_homework() {

}