#include "teacher.h"

#include <direct.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../../global_file.h"
#include "course.h"
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
    string course_name, course_id, time;
    string course_collection = "../../src/model/identity_model/homework_set/" + teacher_id + "_teacher/course_collection.txt";
    ifstream ifs;
    ifs.open(course_collection, ios::in);
    if (!ifs.is_open()) {
        cout << "用户课程文件不存在" << endl;
        ifs.close();
        return;
    }
    map<string, string> name_to_id;
    string name, id;
    while (ifs >> name >> id) name_to_id[name] = id;

    cout << "请输入该课程的名称: " << endl;
    cin >> course_name;
    course_id = name_to_id[course_name];
    cout << "请输入您要布置的作业次数: " << endl;
    cin >> time;
    Course cou = Course(course_id, course_name, teacher_id);
    cou.init2();
    char path0[200];
    if (!getcwd(path0, 200)) {
        cout << "Get path fail!" << endl;
        return;
    }
    string path = path0;
    int eff = path.find("\\build\\build");
    path.erase(path.begin() + eff, path.end());
    string folderPath, target;
    //  string target, base = "../../src/model/identity_model/homework_set/" + teacher_id + "_teacher/" + course_id + "_course/" + time + "_times/";
    folderPath = path + "\\src\\model\\identity_model\\homework_set\\" + teacher_id + "_teacher\\" + course_id + "_course\\" + time + "_times";
    // cout << folderPath << endl;
    if (0 != access(folderPath.c_str(), 0)) {
        mkdir(folderPath.c_str());
    }
    string end[4];
    ofstream location_out;
    for (int i = 0; i <= cou.stu_number - 1; i++) {
        target = folderPath + "\\" + cou.stus[i] + "_stu";
        // cout << target << endl;
        if (0 != access(target.c_str(), 0)) {
            mkdir(target.c_str());
        }

        end[0] = target + "\\hw.txt";
        location_out.open(end[0], std::ios::out | std::ios::app);
        location_out.close();

        end[1] = target + "\\info.txt";
        location_out.open(end[1], std::ios::out | std::ios::app);
        location_out << 0 << " "
                     << "未交" << endl;
        location_out.close();

        end[2] = target + "\\zip.txt";
        location_out.open(end[2], std::ios::out | std::ios::app);
        location_out.close();

        end[3] = target + "\\unzip.txt";
        location_out.open(end[3], std::ios::out | std::ios::app);
        location_out.close();
    }
    log("set_homework");
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
    cout << "\n查重函数 Debug Result: \n\n";
    string hw_folder = "../../src/model/identity_model/homework_set/" + this->teacher_id + "_teacher/" + course_id + "_course/" + to_string(times) + "_times/";

    //获取所有学号
    ifstream ifs_stu_info;
    ifs_stu_info.open(STU_INFO_FILE, ios::in);
    if (!ifs_stu_info.is_open()) {
        cout << "\n打开学生信息文件失败!\n";
        system("pause");
        return;
    }

    string stu_id, stu_pwd, stu_name, stu_class;
    vector<string> all_stu;
    while (ifs_stu_info >> stu_id >> stu_pwd >> stu_name >> stu_class) {
        all_stu.push_back(stu_id);
    }
    //遍历每个学号
    for (auto stu_id : all_stu) {
        string hw_file = hw_folder + stu_id + "_stu/" + "hw.txt";  //当前学生作业
        ifstream ifs_hw;
        ifs_hw.open(hw_file, ios::in);
        if (!ifs_hw.is_open()) {
            cout << "\n打开学生 " << stu_id << " 作业文件失败!\n";
            system("pause");
            return;
        }

        string hw_content;  //作业中所有字符串拼接起来的结果
        string hw_lines;
        while (ifs_hw >> hw_lines) hw_content += hw_lines;
        //输出作业内容测试一下
        // cout << hw_content << "\n\n";

<<<<<<< HEAD
        // TODO: Aho–Corasick algorithm, AC自动机字符串匹配
        //分割为长度为10的字符串，每匹配一条重复率加 (10/作业总长度) x 100%
        //查重一次作业时间复杂度O(T*C^2) T 为两个查重对象作业文本均摊长度,C 为学生人数
=======
        // TODO: AC自动机字符串匹配
>>>>>>> 9e2116704ba5654325b70ef4a5291f3f68d42f07

        for (auto other_id : all_stu) {
            if (other_id != stu_id) {  //其他学生文件夹
            }
        }
    }
    system("pause");
    system("cls");
}

void Teacher::log(string sth) {
    logger_t addition = logger_t("teacher", teacher_id, sth);
    ofstream ofs1;
    string log_file = "../../log/admin.txt";
    ofs1.open(log_file, ios::app);
    ofs1 << addition.now << " " << addition.kind << " " << addition.id << " " << addition.sth << endl;
    ofs1.close();
}