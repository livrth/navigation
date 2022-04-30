#include "homework.h"
#include <iostream>
#include <string>
using namespace std;

Homework::Homework() {
}

Homework::Homework(string teacher_id, string course_id, string course_name) {
    //此处根据教师 id 找到教师姓名
    string teacher_name = "李华";  //测试用，暂且默认
    cout << "教师 " << teacher_name << " 已经布置新的 " << course_name << " 作业!" << endl;\

    system("pause");
    system("cls");
}

void Homework::compress() {
}

void Homework::decompress() {
}

void Homework::set_grades() {
}

void Homework::check_duplicate() {
}
