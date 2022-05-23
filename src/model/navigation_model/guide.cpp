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
    cout << "\n您的当前课程可选项为: \n";
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
    if (flag_shahe_xitu) {  //沙河 -> 西土城
        cout << "\n您可选乘每日定点校车路线如下: " << endl;
        cout << "----------------------------------------------------------------------------\n";
        cout << "北邮沙河校区->沙河公交站->京藏高速沙河收费站->京藏高速->马甸桥->北邮海淀校区" << endl;
        cout << "----------------------------------------------------------------------------\n\n";

        cout << "您可选乘公交车路线如下(乘坐12站 43分钟): " << endl;
        cout << "----------------------------------------------------------------------------\n";
        cout << "北邮沙河校区->沙河公交站->马甸桥东公交站->蓟门桥南公交站->北邮海淀校区" << endl;
        cout << "----------------------------------------------------------------------------\n\n";
        cout << "您到达西土城校区之后的校内导航路线如下: \n";
    } else if (flag_xitu_shahe) {  //西土城 -> 沙河
        cout << "\n您可选乘每日定点校车路线如下: " << endl;
        cout << "----------------------------------------------------------------------------\n";
        cout << "北邮海淀校区->马甸桥->京藏高速->京藏高速沙河收费站->沙河公交站->北邮沙河校区\n";
        cout << "----------------------------------------------------------------------------\n\n";

        cout << "您可选乘公交车路线如下(乘坐12站 43分钟): " << endl;
        cout << "----------------------------------------------------------------------------\n";
        cout << "北邮海淀校区->蓟门桥南公交站->马甸桥东公交站->沙河公交站->北邮沙河校区\n";
        cout << "----------------------------------------------------------------------------\n\n";
        cout << "您到达沙河校区之后的校内导航路线如下: \n";
    }

    /*
    每个校区的校门规定为1号建筑
    跨校区需要先抵达目的校区，然后从1号建筑导航到目的教学楼建筑
    */
    if (flag_shahe_xitu || flag_xitu_shahe) now_build_id = 1;  //校门开始导航

    //最短距离策略
    cout << "\n最短步行距离路线如下: \n";
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

    cout << "最短步行时间路线如下: \n";
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
    //自行车道重新生成地图
    //只需要最短时间，行驶速度为 4m/s
    //自行车道地图 bike_map1.txt bike_map2.txt bike_path1.txt bike_path2.txt
    string bike_path_file;
    if (this->campus_now == "沙河")
        bike_path_file = "../../src/model/navigation_model/bike_path1.txt";  //沙河校区
    else
        bike_path_file = "../../src/model/navigation_model/bike_path2.txt";

    ifstream ifs_bike;
    ifs_bike.open(bike_path_file, ios::in);
    if (!ifs_bike.is_open()) {
        cout << "自行车道路径寻找文件不存在!" << endl;
        system("pause");
        return;
    }

    cout << "自行车道最短时间路线如下: \n";
    cout << "---------------------------------------------------------------------------\n";
    for (std::string line; std::getline(ifs_bike, line);) {
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
            cout << "最少骑车所需时长约 " << stoi(v[v.size() - 1]) * 1.0 / 4.0 << " 秒" << endl;
            break;
        }
    }
    cout << "---------------------------------------------------------------------------\n\n";
    ifs_bike.close();

    system("pause");
    system("cls");
}

void Guide::print_path_by_location() {
    /*
    同校区内直接导航
    跨校区: 当前建筑->当前校区1号建筑(校门) -> 另外一个校区1号建筑->另外一个校区目的建筑
    */

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
    map<string, int> mp;  //具体教室 教室所在建筑编号
    // map<string, string> campus_map;  //具体教室 教室所在校区
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
        mp[file_classroom] = file_building_id;
        // campus_map[file_course_name] = file_campus;  //所在校区
        all_course.insert(file_course_name);
    }
    ifs.close();

    string campus_now, classroom_now;    //现在所在校区 教室
    string campus_next, classroom_next;  //要去的校区 教室
    cout << "请输入您当前所在教室(例如 沙河 2号楼208): ";
    cin >> campus_now >> classroom_now;
    cout << "请输入您将要去的教室(例如 沙河 9号楼510): ";
    cin >> campus_next >> classroom_next;
    int now_build_id = mp[classroom_now];    //当前所在建筑
    int next_build_id = mp[classroom_next];  //即将要去的建筑

    if (campus_now == campus_next) {  //都在同一校区 包括都在沙河和都在西土城
        cout << "\n识别到您不需要跨校区, " << campus_now << "校区内的导航如下:\n";
        string path_file;
        ifstream iifs;
        if (campus_now == "沙河")
            path_file = "../../src/model/navigation_model/path1.txt";  //沙河校区
        else
            path_file = "../../src/model/navigation_model/path2.txt";  //西土城

        string cps_next = campus_now;

        iifs.open(path_file, ios::in);
        if (!iifs.is_open()) {
            cout << "路径寻找文件不存在!" << endl;
            system("pause");
            return;
        }

        cout << "\n最短步行距离路线如下: \n";
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
                for (int i = 2; i < (int)(v.size() - 2); i++) cout << (v[i] == "1" ? (cps_next + "校门 -> ") : v[i] + " 号教学楼 -> ");
                cout << v[v.size() - 2] + " 号教学楼" << endl;
                cout << "---------------------------------------------------------------------------\n";
                cout << "最短步行路线总长度: " << v[v.size() - 1] << " 米" << endl;
                break;
            }
        }
        cout << "---------------------------------------------------------------------------\n\n";
        iifs.close();

        //最短步行时间(拥挤度地图)
        string crowd_path_file;
        if (campus_now == "沙河")
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

        cout << "最短步行时间路线如下: \n";
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
                for (int i = 2; i < (int)(v.size() - 2); i++) cout << (v[i] == "1" ? (cps_next + "校门 -> ") : v[i] + " 号教学楼 -> ");
                cout << v[v.size() - 2] + " 号教学楼" << endl;
                cout << "---------------------------------------------------------------------------\n";
                cout << "最少步行所需时长约 " << stoi(v[v.size() - 1]) * 1.0 / 1.5 << " 秒" << endl;
                break;
            }
        }
        cout << "---------------------------------------------------------------------------\n\n";
        ifs_crowd.close();

        //自行车道时间
        string bike_path_file;
        if (campus_now == "沙河")
            bike_path_file = "../../src/model/navigation_model/bike_path1.txt";  //沙河校区
        else
            bike_path_file = "../../src/model/navigation_model/bike_path2.txt";

        ifstream ifs_bike;
        ifs_bike.open(bike_path_file, ios::in);
        if (!ifs_bike.is_open()) {
            cout << "自行车道路径寻找文件不存在!" << endl;
            system("pause");
            return;
        }

        cout << "自行车道最短时间路线如下: \n";
        cout << "---------------------------------------------------------------------------\n";
        for (std::string line; std::getline(ifs_bike, line);) {
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
                cout << "最少骑车所需时长约 " << stoi(v[v.size() - 1]) * 1.0 / 4.0 << " 秒" << endl;
                break;
            }
        }
        cout << "---------------------------------------------------------------------------\n\n";
        ifs_bike.close();
    } else if (campus_now == "沙河" && campus_next == "西土城") {  //沙河 -> 西土城
        //当前沙河教学楼-> 1号沙河校门
        cout << "\n识别到您需要跨校区导航, 请先沿如下路线步行至沙河校门口进行乘车:\n";
        int temp_next_id = next_build_id;  //西土城的目的教学楼编号
        next_build_id = 1;
        string path_file;
        ifstream iifs_;
        path_file = "../../src/model/navigation_model/path1.txt";  //沙河校区

        string cps_next = campus_now;

        iifs_.open(path_file, ios::in);
        if (!iifs_.is_open()) {
            cout << "步行路径寻找文件不存在!" << endl;
            system("pause");
            return;
        }

        // cout << "\n最短步行距离路线如下: \n";
        cout << "---------------------------------------------------------------------------\n";
        for (std::string line; std::getline(iifs_, line);) {
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
                for (int i = 2; i < (int)(v.size() - 2); i++) cout << (v[i] == "1" ? (cps_next + "校门 -> ") : v[i] + " 号教学楼 -> ");
                // cout << v[v.size() - 2] + " 号教学楼" << endl;
                cout << "沙河校区门口" << endl;
                cout << "---------------------------------------------------------------------------\n";
                cout << "最短步行路线总长度: " << v[v.size() - 1] << " 米" << endl;
                break;
            }
        }
        cout << "---------------------------------------------------------------------------\n\n";
        iifs_.close();

        //乘车规划:
        cout << "您可选乘每日定点校车路线如下: " << endl;
        cout << "----------------------------------------------------------------------------\n";
        cout << "北邮沙河校区->沙河公交站->京藏高速沙河收费站->京藏高速->马甸桥->北邮海淀校区" << endl;
        cout << "----------------------------------------------------------------------------\n\n";

        cout << "您可选乘公交车路线如下(乘坐12站 43分钟): " << endl;
        cout << "----------------------------------------------------------------------------\n";
        cout << "北邮沙河校区->沙河公交站->马甸桥东公交站->蓟门桥南公交站->北邮海淀校区" << endl;
        cout << "----------------------------------------------------------------------------\n\n";
        cout << "您到达西土城校区之后的校内导航路线如下: \n";

        //西土城校门-> 西土城目的建筑
        now_build_id = 1;
        next_build_id = temp_next_id;
        cps_next = "西土城";
        campus_now = "西土城";

        ifstream iifs;
        path_file = "../../src/model/navigation_model/path2.txt";  //西土城

        iifs.open(path_file, ios::in);
        if (!iifs.is_open()) {
            cout << "路径寻找文件不存在!" << endl;
            system("pause");
            return;
        }

        cout << "\n最短步行距离路线如下: \n";
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
                for (int i = 2; i < (int)(v.size() - 2); i++) cout << (v[i] == "1" ? (cps_next + "校门 -> ") : v[i] + " 号教学楼 -> ");
                cout << v[v.size() - 2] + " 号教学楼" << endl;
                cout << "---------------------------------------------------------------------------\n";
                cout << "最短步行路线总长度: " << v[v.size() - 1] << " 米" << endl;
                break;
            }
        }
        cout << "---------------------------------------------------------------------------\n\n";
        iifs.close();

        //最短步行时间(拥挤度地图)
        string crowd_path_file;
        if (campus_now == "沙河")
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

        cout << "最短步行时间路线如下: \n";
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
                for (int i = 2; i < (int)(v.size() - 2); i++) cout << (v[i] == "1" ? (cps_next + "校门 -> ") : v[i] + " 号教学楼 -> ");
                cout << v[v.size() - 2] + " 号教学楼" << endl;
                cout << "---------------------------------------------------------------------------\n";
                cout << "最少步行所需时长约 " << stoi(v[v.size() - 1]) * 1.0 / 1.5 << " 秒" << endl;
                break;
            }
        }
        cout << "---------------------------------------------------------------------------\n\n";
        ifs_crowd.close();

        //自行车道时间
        string bike_path_file;
        if (campus_now == "沙河")
            bike_path_file = "../../src/model/navigation_model/bike_path1.txt";  //沙河校区
        else
            bike_path_file = "../../src/model/navigation_model/bike_path2.txt";

        ifstream ifs_bike;
        ifs_bike.open(bike_path_file, ios::in);
        if (!ifs_bike.is_open()) {
            cout << "自行车道路径寻找文件不存在!" << endl;
            system("pause");
            return;
        }

        cout << "自行车道最短时间路线如下: \n";
        cout << "---------------------------------------------------------------------------\n";
        for (std::string line; std::getline(ifs_bike, line);) {
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
                cout << "最少骑车所需时长约 " << stoi(v[v.size() - 1]) * 1.0 / 4.0 << " 秒" << endl;
                break;
            }
        }
        cout << "---------------------------------------------------------------------------\n\n";
        ifs_bike.close();
    } else if (campus_now == "西土城" && campus_next == "沙河") {  // 西土城 -> 沙河
        //当前西土城教学楼 -> 1号西土城校门
        cout << "\n识别到您需要跨校区导航, 请先沿如下路线步行至西土城校门口进行乘车:\n";
        int temp_next_id = next_build_id;  //沙河的目的教学楼编号
        next_build_id = 1;
        string path_file;
        ifstream iifs_;
        path_file = "../../src/model/navigation_model/path2.txt";  //西土城校区

        string cps_next = campus_now;

        iifs_.open(path_file, ios::in);
        if (!iifs_.is_open()) {
            cout << "步行路径寻找文件不存在!" << endl;
            system("pause");
            return;
        }

        cout << "---------------------------------------------------------------------------\n";
        for (std::string line; std::getline(iifs_, line);) {
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
                for (int i = 2; i < (int)(v.size() - 2); i++) cout << (v[i] == "1" ? (cps_next + "校门 -> ") : v[i] + " 号教学楼 -> ");
                // cout << v[v.size() - 2] + " 号教学楼" << endl;
                cout << "西土城校区门口" << endl;
                cout << "---------------------------------------------------------------------------\n";
                cout << "最短步行路线总长度: " << v[v.size() - 1] << " 米" << endl;
                break;
            }
        }
        cout << "---------------------------------------------------------------------------\n\n";
        iifs_.close();

        //乘车规划:
        cout << "您可选乘每日定点校车路线如下: " << endl;
        cout << "----------------------------------------------------------------------------\n";
        cout << "北邮海淀校区->马甸桥->京藏高速->京藏高速沙河收费站->沙河公交站->北邮沙河校区\n";
        cout << "----------------------------------------------------------------------------\n\n";

        cout << "您可选乘公交车路线如下(乘坐12站 43分钟): " << endl;
        cout << "----------------------------------------------------------------------------\n";
        cout << "北邮海淀校区->蓟门桥南公交站->马甸桥东公交站->沙河公交站->北邮沙河校区\n";
        cout << "----------------------------------------------------------------------------\n\n";
        cout << "您到达沙河校区之后的校内导航路线如下: \n";

        //沙河校门-> 沙河目的建筑
        now_build_id = 1;
        next_build_id = temp_next_id;
        cps_next = "沙河";
        campus_now = "沙河";

        ifstream iifs;
        path_file = "../../src/model/navigation_model/path1.txt";  //沙河

        iifs.open(path_file, ios::in);
        if (!iifs.is_open()) {
            cout << "路径寻找文件不存在!" << endl;
            system("pause");
            return;
        }

        cout << "\n最短步行距离路线如下: \n";
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
                for (int i = 2; i < (int)(v.size() - 2); i++) cout << (v[i] == "1" ? (cps_next + "校门 -> ") : v[i] + " 号教学楼 -> ");
                cout << v[v.size() - 2] + " 号教学楼" << endl;
                cout << "---------------------------------------------------------------------------\n";
                cout << "最短步行路线总长度: " << v[v.size() - 1] << " 米" << endl;
                break;
            }
        }
        cout << "---------------------------------------------------------------------------\n\n";
        iifs.close();

        //最短步行时间(拥挤度地图)
        string crowd_path_file;
        if (campus_now == "沙河")
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

        cout << "最短步行时间路线如下: \n";
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
                for (int i = 2; i < (int)(v.size() - 2); i++) cout << (v[i] == "1" ? (cps_next + "校门 -> ") : v[i] + " 号教学楼 -> ");
                cout << v[v.size() - 2] + " 号教学楼" << endl;
                cout << "---------------------------------------------------------------------------\n";
                cout << "最少步行所需时长约 " << stoi(v[v.size() - 1]) * 1.0 / 1.5 << " 秒" << endl;
                break;
            }
        }
        cout << "---------------------------------------------------------------------------\n\n";
        ifs_crowd.close();

        //自行车道时间
        string bike_path_file;
        if (campus_now == "沙河")
            bike_path_file = "../../src/model/navigation_model/bike_path1.txt";  //沙河校区
        else
            bike_path_file = "../../src/model/navigation_model/bike_path2.txt";

        ifstream ifs_bike;
        ifs_bike.open(bike_path_file, ios::in);
        if (!ifs_bike.is_open()) {
            cout << "自行车道路径寻找文件不存在!" << endl;
            system("pause");
            return;
        }

        cout << "自行车道最短时间路线如下: \n";
        cout << "---------------------------------------------------------------------------\n";
        for (std::string line; std::getline(ifs_bike, line);) {
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
                cout << "最少骑车所需时长约 " << stoi(v[v.size() - 1]) * 1.0 / 4.0 << " 秒" << endl;
                break;
            }
        }
        cout << "---------------------------------------------------------------------------\n\n";
        ifs_bike.close();
    }

    system("pause");
    system("cls");
}

void Guide::print_path_by_time() {
    string table_path = "../../src/model/identity_model/course_table/" + this->stu_id + "_course_table.txt";
    ifstream ifs;
    ifs.open(table_path, ios::in);
    if (!ifs.is_open()) {
        cout << "学生课表文件读取失败!\n\n";
        system("pause");
        return;
    }

    map<pair<string, int>, pair<string, int> > mp;  //<{Mon, 1}, {计网,5}> 星期 课程节号 课程名称 建筑编号
    map<string, string> campus_map;                 //课程 课程所在校区
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
        mp[{file_date, file_class_number}] = {file_course_name, file_building_id};
        campus_map[file_course_name] = file_campus;  //所在校区
        all_course.insert(file_course_name);
    }

    int now_build_id;
    int next_build_id;
    // cout << "请输入当前您当前所在时间(例如 Fri 08:30): ";
    cout << "请输入您当前所在校区以及建筑/教学楼编号(例如 沙河 5): ";
    cin >> now_build_id;
    cout << "请输入您要查询的上课时间(例如 Fri 10:30): ";
    string query_date;
    int query_hour, query_minute;
    cin >> query_date;
    scanf("%d:%d", &query_hour, &query_minute);

    // TODO: 根据时间转换为 课程的节号
    //在 mp 里面{星期, 节次} 查到课程名称和建筑编号(next_build_id)
    //然后在 campus_map 根课程名称查到校区 考虑是否需要跨校区
    //这样就转换为根据位置查询的完全一样的逻辑了
}

void Guide::print_path_by_fixed_building() {  //选做算法  经过固定地点
}
