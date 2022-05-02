#include "guide.h"

#include <windows.h>

#include <cctype>
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
    cout << "\n\n您的当前课程可选项为: \n";
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

    cout << "\n请输入您当前正在上的课程名称: ";
    string course_go_on;
    cin >> course_go_on;

    cout << "请输入您将要上课的课程名称: ";
    string course_name;
    cin >> course_name;

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
    Sleep(200);
    cout << "\n......";
    Sleep(200);
    cout << "......";
    Sleep(200);
    cout << "......";
    Sleep(200);
    cout << "\n";
    cout << "系统已识别到您当前在: " << now_build_id << "号 教学楼" << endl;
    cout << "即将前往: " << next_build_id << "号 教学楼\n";
    cout << "......";
    Sleep(200);
    cout << "......";
    Sleep(200);
    cout << "......";
    Sleep(200);
    cout << "\n";
    cout << "\n系统已为您规划好路线如下: \n";
    cout << "---------------------------------------------------------------------------\n";
    for (std::string line; std::getline(iifs, line);) {
        vector<string> v;  //去掉空格分开之后的所有单独建筑编号
        string temp = "";

        for (int i = 0; line[i]; i++) {
            if (!isspace(line[i]))
                temp += line[i];
            else {
                while (isspace(line[i])) i++;
                i--;
                v.push_back(temp);
                temp = "";
            }
        }
        v.push_back(temp);

        if (stoi(v[0]) == now_build_id && stoi(v[1]) == next_build_id) {
            // cout << line << endl;
            for (int i = 2; i < (int)(v.size() - 2); i++) cout << v[i] + " 号教学楼 -> ";
            cout << v[v.size() - 2] + " 号教学楼" << endl;
            cout << "---------------------------------------------------------------------------\n";
            cout << "路线总长度: " << v[v.size() - 1] << " 米" << endl;
            break;
        }
    }
    cout << "---------------------------------------------------------------------------\n\n";
    cout << "最短路径显示完毕!\n\n";
    iifs.close();
    system("pause");
    system("cls");
}

void Guide::print_path_by_location() {
}

void Guide::print_path_by_time() {
}
