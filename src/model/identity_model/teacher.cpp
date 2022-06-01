#include "teacher.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../../global_file.h"
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

        // TODO: Aho–Corasick algorithm, AC自动机字符串匹配
        //分割为长度为10的字符串，每匹配一条重复率加 (10/作业总长度) x 100%
        //查重一次作业时间复杂度O(T*C^2) T 为两个查重对象作业文本均摊长度,C 为学生人数

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
    string log_file = "../../doc/admin";
    ofs1.open(log_file, ios::app);
    ofs1 << addition.now << " " << addition.kind << " " << addition.id << " " << addition.sth << endl;
    ofs1.close();
}