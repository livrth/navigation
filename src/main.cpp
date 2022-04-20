#include <windows.h>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>

#include "admin.h"
#include "global_file.h"
#include "menu.cpp"
#include "student.h"
#include "teacher.h"

using namespace std;

void student_menu(Student*& stu) {
    while (true) {
        stu->operMenu();
        int op;
        cin >> op;
        if (op == 1) {  //课程名称查询
            stu->query_by_course_name();
        } else if (op == 2) {
            stu->query_by_course_table();
        } else if (op == 3) {
            stu->upload_course_material();
        } else if (op == 4) {
            stu->upload_home_work();
        } else if (op == 5) {
            stu->query_activity();
        } else if (op == 6) {
            stu->set_activity_alarm();
        } else if (op == 7) {
            stu->guide_now();
        } else if (op == 0) {
            delete stu;
            cout << "注销成功" << endl;
            system("pause");
            system("cls");
            return;
        } else {
            cout << "\n无法识别的操作, 请重新输入: ";
            system("pause");
            system("cls");
        }
    }
}

void teacher_menu(Teacher*& tea) {
    while (true) {
        tea->operMenu();
        int op;
        cin >> op;
        if (op == 1) {
            tea->set_homework();  //布置作业
        } else if (op == 2) {
            tea->check_homework();  //检查作业
        } else if (op == 0) {
            delete tea;
            cout << "注销成功" << endl;
            system("pause");
            system("cls");
            return;
        } else {
            cout << "\n无法识别的操作, 请重新输入: ";
            system("pause");
            system("cls");
        }
    }
}

void admin_menu(Admin*& admin) {
}

//学生/教师/管理员登录
void login(string fileName, int type) {
    Student* stu = nullptr;
    Teacher* tea = nullptr;
    // cout << "here ---- 1" << endl;
    ifstream ifs;
    ifs.open(fileName, ios::in);
    // cout << "here ----- 2" << endl;

    if (!ifs.is_open()) {
        cout << "用户文件不存在" << endl;
        ifs.close();
        return;
    }
    string id;  //用户名
    string pwd;
    cout << "\n请输入学号或者教职工号: ";
    cin >> id;
    cout << "\n请输入密码: " << endl;
    cin >> pwd;

    if (type == 1) {  //学生登录
        string file_id, file_pwd, file_name;
        while (ifs >> file_id >> file_pwd >> file_name) {
            if (file_id == id && file_pwd == pwd) {
                cout << "\n学生用户登录成功!" << endl;
                system("pause");
                system("cls");
                stu = new Student(id, file_name);
                student_menu(stu);
                return;
            }
        }
    } else if (type == 2) {  //教师登录
        string file_id, file_pwd, file_name;
        while (ifs >> file_id >> file_pwd >> file_name) {
            if (file_id == id && file_pwd == pwd) {
                cout << "\n教师用户登录成功!" << endl;
                system("pause");
                system("cls");
                tea = new Teacher(id);
                teacher_menu(tea);
                return;
            }
        }

    } else if (type == 3) {  //管理员登录
        string file_name, file_pwd;
        while (ifs >> file_name >> file_pwd) {
            if (file_name == id && file_pwd == pwd) {
                cout << "\n管理员登录成功!" << endl;
                system("pause");
                system("cls");
                Admin* admin = nullptr;
                admin = new Admin(id);
                admin_menu(admin);
                return;
            }
        }
    }
    cout << "验证登录失败! 请检查用户名或者密码 " << endl;
    system("pause");
    system("cls");

    return;
}

//学生用户注册
void new_stu_reg() {
    string stu_id, name, pwd;
    cout << "\n请输入您的学号: ";
    cin >> stu_id;
    cout << "\n请输入您的学生姓名: ";
    cin >> name;
    cout << "\n请输入新账号的密码: ";
    cin >> pwd;

    //IO流一调用就直接段错误 关掉 -O3 优化选项
    //修改文件路径为 "test.txt" 也就是当前目录下生成也不行
    ofstream ofs;
    ofs.open(STU_INFO_FILE, ios::app);
    if (!ofs.is_open()) {
        cout << "学生用户信息文件打开失败!" << endl;
        ofs.close();
        return;
    }
    //学号 密码 姓名
    ofs << stu_id << ' ' << pwd << ' ' << name << endl;
    ofs.close();
    cout << "\n您已注册成功, 请登录使用本系统!\n\n";
    system("pause");
    system("cls");
}

//教师用户注册
void new_teacher_reg() {
    string teacher_id, name, pwd;
    cout << "\n请输入您的教职工号: ";
    cin >> teacher_id;
    cout << "请输入您的姓名: ";
    cin >> name;
    cout << "请输入新账号的密码: ";
    cin >> pwd;

    ofstream ofs;
    ofs.open(TEACHER_INFO_FILE, ios::app);
    if (!ofs.is_open()) {
        cout << "教师用户信息文件打开失败!" << endl;
        ofs.close();
        return;
    }
    //教职工号 密码 姓名
    ofs << teacher_id << ' ' << pwd << ' ' << name << endl;
    ofs.close();
    cout << "\n您已注册成功, 请登录使用本系统!\n\n";
    system("pause");
    system("cls");
}

int main() {
    //起始欢迎界面
    system("cls");
    cout << "\n\n";
    Sleep(100);
    cout << "	 __  __     ______     __         __         ______    \n";
    Sleep(100);
    cout << "	/\\ \\_\\ \\   /\\  ___\\   /\\ \\       /\\ \\       /\\  __ \\   \n";
    Sleep(100);
    cout << "	\\ \\  __ \\  \\ \\  __\\   \\ \\ \\____  \\ \\ \\____  \\ \\ \\/\\ \\  \n";
    Sleep(100);
    cout << "	 \\ \\_\\ \\_\\  \\ \\_____\\  \\ \\_____\\  \\ \\_____\\  \\ \\_____\\ \n";
    Sleep(100);
    cout << "	  \\/_/\\/_/   \\/_____/   \\/_____/   \\/_____/   \\/_____/ \n";
    cout << endl;
    cout << "\t\tWelcome to Course Assistance System \n";
    Sleep(1500);
    system("cls");

    int op;
    while (true) {
        cout << "\n\n";
        cout << "\t\t -------------------------------\n";
        cout << "\t\t|      欢迎来到课程辅助系统     |\n";
        cout << "\t\t -------------------------------\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          1.学生用户登录       |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          2.教师用户登录       |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          3.管理员登录         |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          4.学生用户注册       |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          5.教师用户注册       |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|          0.退出此系统         |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t -------------------------------\n";
        cout << "\n\n";
        cout << "请输入您的选择: ";

        cin >> op;
        switch (op) {
            case 1:
                login(STU_INFO_FILE, 1);  //学生用户登录
                break;
            case 2:
                login(TEACHER_INFO_FILE, 2);  //教师用户登录
                break;
            case 3:
                login(ADMIN_INFO_FILE, 3);  //管理员登录
                break;
            case 4:
                new_stu_reg();
                break;
            case 5:
                new_teacher_reg();
                break;
            case 0:
                cout << "\n已退出系统\n\n";
                system("pause");
                return 0;
                break;
            default:
                cout << "系统无法识别输入, 请重新选择!" << endl;
                system("pause");
                system("cls");
                break;
        }
    }
    system("pause");
    return 0;
}