#include "guide.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

Guide::Guide() {
}

Guide::Guide(string campus, string stu_id) {
    this->campus_now = campus;
    this->stu_id = stu_id;
}

void Guide::build_graph(string campus_in) {
    campus_in = this->campus_now;
    ifstream ifs;
    string map_path = "../../src/model/navigation_model/map" + campus_in + ".txt";
    ifs.open(map_path, ios::in);
    if (!ifs.is_open()) {
        cout << "地图文件读取失败!\n"
             << endl;
        system("pause");
        return;
    }
}

void Guide::print_path_by_course() {
    string table_path = "../../src/model/identity_model/course_table/" + this->stu_id + "_course_table.txt";
    ifstream ifs;
    ifs.open(table_path, ios::in);
    if (!ifs.is_open()) {
        cout << "学生课表文件读取失败!\n\n";
        system("pause");
        return;
    }
    cout << "\n请输入您将要上课的课程名称: ";
    string course_name;
    cin >> course_name;

    //课程表信息
    // string
}

void Guide::print_path_by_location() {
}

void Guide::print_path_by_time() {
}
