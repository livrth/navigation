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

Guide::Guide(string stu_id) {
    this->stu_id = stu_id;
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
    map<string, string> campus_map;  //课程 课程所在校区
    set<string> all_course;
    //星期 第几节 教室 课程名称 所在校区 课程编号 教室所在建筑
    string file_date, file_classroom, file_course_name, file_campus;
    int file_class_number, name_length;
    string file_course_id, garbage;
    int file_building_id;
    while (ifs >> file_date >> file_class_number >> file_classroom >> file_course_name >> file_campus >> file_course_id >> file_building_id >> name_length) {
        for (int z = 1; z <= name_length; z++) {
            ifs >> garbage;
        }
        mp[file_course_name] = file_building_id;
        campus_map[file_course_name] = file_campus;  //所在校区
        all_course.insert(file_course_name);
    }
    cout << "\n\n您的当前课程可选项为: \n";
    cout << "-----------------------------------------------------" << endl;
    int cnt = 0;
    for (auto t : all_course) {
        cout << t << "\t";
        cnt++;
        if (cnt % 4 == 0) cout << endl;
    }
    cout << "-----------------------------------------------------" << endl;
    ifs.close();

    cout << "\n请输入您正在上的课程名称: ";
    string course_go_on;
    cin >> course_go_on;

    cout << "请输入您将要上课的课程名称: ";
    string course_name;
    cin >> course_name;

    bool flag_shahe_xitu = false;  //沙河->西土城 跨校区
    bool flag_xitu_shahe = false;  //西土城 -> 沙河 跨校区
    string cps_now = campus_map[course_go_on];
    string cps_next = campus_map[course_name];
    if (cps_now == cps_next && cps_now == "沙河") {
        cout << "\n已查询到您不需要跨校区上课, 当前为沙河校区内导航: \n";
        this->campus_now = "沙河";
    } else if (cps_now == cps_next && cps_now == "西土城") {
        cout << "\n已查询到您不需要跨校区上课, 当前为西土城校区内导航: \n";
        this->campus_now = "西土城";
    } else if (cps_now == "沙河" && cps_next == "西土城") {
        flag_shahe_xitu = true;
        this->campus_now = "西土城";
        cout << "\n已查询到您需跨校区上课, 将从沙河校区出发前往西土城校区: \n";

        // cout << "已到达西土城\n\n";
    } else if (cps_now == "西土城" && cps_next == "沙河") {
        flag_xitu_shahe = true;
        this->campus_now = "沙河";
        cout << "\n已查询到您需跨校区上课, 将从西土城校区出发前往沙河校区: \n";

        // cout << "已到达沙河\n\n";
    }

    int now_build_id = mp[course_go_on];  //当前所在校区的建筑
    int next_build_id = mp[course_name];  //目的校区所在建筑

    ifstream iifs;
    string path_file;

    if (this->campus_now == "沙河")
        path_file = "../../src/model/navigation_model/path1.txt";  //沙河校区
    else
        path_file = "../../src/model/navigation_model/path2.txt";  //西土城

    iifs.open(path_file, ios::in);
    if (!iifs.is_open()) {
        cout << "路径寻找文件不存在!" << endl;
        system("pause");
        return;
    }
    for (int i = 0; i < 3; i++) {
        cout << "..............";
        Sleep(200);
    }
    cout << "\n";
    cout << "已识别到您当前在: " << cps_now << "校区 " << now_build_id << "号教学楼" << endl;
    cout << "导航目的教学楼为: " << cps_next << "校区 " << next_build_id << "号教学楼\n";
    for (int i = 0; i < 3; i++) {
        cout << "..............";
        Sleep(200);
    }
    cout << "\n";

    //如果需要跨校区 输出校区间交通方式 定点班车(校车) 公交车

    /*
    每个校区的校门规定为1号建筑
    跨校区需要先抵达目的校区，然后从1号建筑导航到目的教学楼建筑
    */
    if (flag_shahe_xitu || flag_xitu_shahe) now_build_id = 1;  //校门开始导航

    //最短距离策略
    cout << "\n已为您规划好步行最短距离路线如下: \n";
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
            for (int i = 2; i < (int)(v.size() - 2); i++) cout << (v[i] == "1" ? (cps_next + "校门 -> ") : v[i] + " 号教学楼 -> ");
            cout << v[v.size() - 2] + " 号教学楼" << endl;
            cout << "---------------------------------------------------------------------------\n";
            cout << "最短步行路线总长度: " << v[v.size() - 1] << " 米" << endl;
            break;
        }
    }
    cout << "---------------------------------------------------------------------------\n\n";
    iifs.close();

    //最短时间策略，重新生成地图考虑拥挤度 不考虑跨校区 步行不考虑交通方式
    //输出步行时间 步速 1.5m/s

    string crowd_path_file;
    if (this->campus_now == "沙河")
        crowd_path_file = "../../src/model/navigation_model/path1_crowd.txt";  //沙河校区
    else
        crowd_path_file = "../../src/model/navigation_model/path2_crowd.txt";

    ifstream ifs_crowd;
    ifs_crowd.open(crowd_path_file, ios::in);
    if (!ifs_crowd.is_open()) {
        cout << "拥挤度路径寻找文件不存在!" << endl;
        system("pause");
        return;
    }

    cout << "已为您规划好最短步行时间路线如下: \n";
    cout << "---------------------------------------------------------------------------\n";
    for (std::string line; std::getline(ifs_crowd, line);) {
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
            for (int i = 2; i < (int)(v.size() - 2); i++) cout << (v[i] == "1" ? (cps_next + "校门 -> ") : v[i] + " 号教学楼 -> ");
            cout << v[v.size() - 2] + " 号教学楼" << endl;
            cout << "---------------------------------------------------------------------------\n";
            cout << "最少步行所需时长约 " << stoi(v[v.size() - 1]) * 1.0 / 1.5 << " 秒" << endl;
            break;
        }
    }
    cout << "---------------------------------------------------------------------------\n\n";
    ifs_crowd.close();

    //交通工具策略 考虑新地图 自行车道 考虑拥挤度

    system("pause");
    system("cls");
}

void Guide::print_path_by_location() {
}

void Guide::print_path_by_time() {
}

void Guide::print_path_by_fixed_building() {  //选做算法  经过固定地点
}
