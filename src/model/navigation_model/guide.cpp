#include "guide.h"

#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
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
    //已经预处理了最短路 不需要建图了
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

    //课程表信息
    //存入课程对应的建筑编号
    map<string, int> mp;
    set<string> all_course;
    //星期 第几节 教室 课程名称 所在校区 课程编号 教室所在建筑
    string file_date, file_classroom, file_course_name, file_campus;
    int file_class_number;
    string file_course_id;
    int file_building_id;
    while (ifs >> file_date >> file_class_number >> file_classroom >> file_course_name >> file_campus >> file_course_id >> file_building_id) {
        mp[file_course_name] = file_building_id;
        all_course.insert(file_course_name);
    }
    cout << "\n\n您的当前课程可选项为: \n\n";
    cout << "-----------------------------------------------------" << endl;
    int cnt = 0;
    for (auto t : all_course) {
        cout << t << "\t";
        cnt++;
        if (cnt % 5 == 0) cout << endl;
    }
    cout << endl;
    cout << "-----------------------------------------------------" << endl;
    ifs.close();

    cout << "\n\n请输入您当前正在上的课程名称: ";
    string course_go_on;
    cin >> course_go_on;

    cout << "\n\n请输入您将要上课的课程名称: ";
    string course_name;
    cin >> course_name;

    cout << "\n\n系统已为您规划好路线如下: \n\n";
    int now_build_id = mp[course_go_on];
    int next_build_id = mp[course_name];
    ifstream iifs;
    string path_file;
    if (this->campus_now == "沙河")
        path_file = "../../src/model/navigation_model/path1.txt";  //沙河校区
    else
        path_file = "../../src/model/navigation_model/path2.txt";
    iifs.open(path_file, ios::in);
    if (!iifs.is_open()) {
        cout << "路径寻找文件不存在!" << endl;
        system("pause");
        return;
    }
    int file_from_id, file_to_id;
    //ifstream getline
    // while(iifs >> file_from_id >> file_to_id){
    //     if(file_from_id == now_build_id && file_to_id == next_build_id){

    //     }
    // }
}

void Guide::print_path_by_location() {
}

void Guide::print_path_by_time() {
}
