#include <pthread.h>
#include <windows.h>

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <locale>
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <typeinfo>

#include "../course_model/course.h"
#include "admin.h"
#include "global_file.h"
#include "menu.cpp"
#include "student.h"
#include "teacher.h"
mutex m_lock;
void trial(Student*& stu) {
    SYSTEMTIME sys;
    GetLocalTime(&sys);
    stu->T[0] = weekly_real_time(sys.wDayOfWeek, sys.wHour, sys.wMinute, sys.wSecond + (sys.wMilliseconds % 10) / (double)100);
    while (true) {
        m_lock.lock();
        if (stu->out) {
            m_lock.unlock();
            return;
        } else
            m_lock.unlock();
        Sleep(50);
        if (!stu->stop) {
            GetLocalTime(&sys);
            m_lock.lock();
            if (stu->fast) {
                stu->T[2] = weekly_real_time(sys.wDayOfWeek, sys.wHour, sys.wMinute, sys.wSecond + (sys.wMilliseconds % 10) / (double)100);
                stu->T[2].fix = stu->T[2].result - stu->diff1 - stu->diff2;
                stu->weekly_sys_time = int(ceil(stu->T[0].result + (stu->T[1].fix - stu->T[0].result) * 6 + (stu->T[2].fix - stu->T[1].fix) * 60)) % 10080;
            } else {
                stu->T[1] = weekly_real_time(sys.wDayOfWeek, sys.wHour, sys.wMinute, sys.wSecond + (sys.wMilliseconds % 10) / (double)100);
                stu->T[1].fix = stu->T[1].result - stu->diff1;
                stu->weekly_sys_time = int(ceil(stu->T[0].result + (stu->T[1].fix - stu->T[0].result) * 6)) % 10080;
            }
            for (int r = 1; r <= stu->cnt2; r++) {
                int t = stu->kth(r, stu->root, stu->t2);
                // cout << t / 1440 + 1 << " " << t % 1440 / 60 << " " << t % 1440 % 60 << "\a" << endl;
                Sleep(50);
                if (stu->weekly_sys_time == t) {
                    vector<single_activity> result = stu->time_to_activity[t];
                    for (vector<single_activity>::iterator it = result.begin(); it != result.end(); ++it) {
                        if (it->clock_state == "circular_clock") {
                            cout << "\a"
                                 << "?????????????????????" << endl;
                            stu->log("clock_time_up");
                            Sleep(100);
                        }
                        if (it->clock_state == "once_clock") {
                            cout << "\a"
                                 << "?????????????????????" << endl;
                            stu->log("clock_time_up");
                            Sleep(100);
                            it->clock_state = "no_clock";
                        }
                    }
                }
            }
            m_lock.unlock();
        }
    }
}
void student_menu(Student*& stu) {
    SYSTEMTIME now;
    stu->init();  //????????????????????????
    thread going(trial, std::ref(stu));
    going.detach();
    while (true) {
        stu->operMenu();
        int op;
        cin >> op;
        if (op == 1) {  //??????????????????

            stu->query_by_course_name();

        } else if (op == 2) {
            stu->query_by_course_table();

        } else if (op == 3) {
            stu->query_by_course_time();
            system("pause");
            system("cls");
        } else if (op == 4) {
            stu->query_by_activity_name();
            system("pause");
            system("cls");
        } else if (op == 5) {
            stu->activity_menu();

        } else if (op == 6) {
            stu->query_by_activity_time();
            system("pause");
            system("cls");
        } else if (op == 7) {
            stu->guide_now();
        } else if (op == 8) {
            m_lock.lock();
            stu->fast = true;
            m_lock.unlock();
            cout << "??????????????????!" << endl;

            system("pause");
            system("cls");
        } else if (op == 9) {
            if (!stu->stop) {
                GetLocalTime(&now);
                m_lock.lock();
                stu->T[3] = weekly_real_time(now.wDayOfWeek, now.wHour, now.wMinute, now.wSecond + (now.wMilliseconds % 10) / (double)100);
                stu->stop = true;
                m_lock.unlock();
                cout << "??????????????????!" << endl;
            } else {
                GetLocalTime(&now);
                m_lock.lock();
                stu->T[4] = weekly_real_time(now.wDayOfWeek, now.wHour, now.wMinute, now.wSecond + (now.wMilliseconds % 10) / (double)100);
                if (stu->fast) {
                    stu->diff2 += stu->T[4].result - stu->T[3].result;

                } else {
                    stu->diff1 += stu->T[4].result - stu->T[3].result;
                }
                stu->stop = false;
                m_lock.unlock();
                cout << "??????????????????!" << endl;
            }
            system("pause");
            system("cls");
        } else if (op == 0) {
            stu->submit();
            m_lock.lock();
            stu->out = true;
            m_lock.unlock();
            Sleep(2000);
            // going.~thread();
            //   delete going;
            delete stu;
            cout << "\n????????????\n"
                 << endl;
            system("pause");
            system("cls");
            return;
        } else {
            cout << "\n?????????????????????, ???????????????: ";
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
            tea->set_homework();  //????????????
            system("pause");
        } else if (op == 2) {
            tea->mark_homework();  //????????????
        } else if (op == 8) {
            //????????????????????????

        } else if (op == 0) {
            delete tea;
            cout << "\n????????????\n"
                 << endl;
            system("pause");
            system("cls");
            return;
        } else {
            cout << "\n?????????????????????, ???????????????: ";
            system("pause");
            system("cls");
        }
    }
}

void admin_menu(Admin*& admin) {
    while (true) {
        admin->operMenu();
        int op;
        cin >> op;
        if (op == 1) {
            admin->change_activity();
        } else if (op == 2) {
            admin->release_new_course();
        } else if (op == 3) {
            admin->change_course();
        } else if (op == 0) {
            delete admin;
            cout << "\n????????????\n"
                 << endl;
            system("pause");
            system("cls");
            return;
        } else {
            cout << "\n?????????????????????, ???????????????: ";
            system("pause");
            system("cls");
        }
    }
}

//??????/??????/???????????????
void login(string fileName, int type) {
    Student* stu = nullptr;
    Teacher* tea = nullptr;
    ifstream ifs;
    ifs.open(fileName, ios::in);

    if (!ifs.is_open()) {
        cout << "?????????????????????" << endl;
        ifs.close();
        return;
    }
    string id;  //?????????
    string pwd;
    cout << "\n?????????????????????: ";
    cin >> id;
    cout << "\n???????????????: ";
    cin >> pwd;

    if (type == 1) {  //????????????
        string file_id, file_pwd, file_name, group_id;
        while (ifs >> file_id >> file_pwd >> file_name >> group_id) {
            if (file_id == id && file_pwd == pwd) {
                cout << "\n????????????????????????!\n"
                     << endl;
                system("pause");
                system("cls");
                stu = new Student(id, file_name, group_id);
                student_menu(stu);
                return;
            }
        }
    } else if (type == 2) {  //????????????
        string file_id, file_pwd, file_name;
        while (ifs >> file_id >> file_pwd >> file_name) {
            if (file_id == id && file_pwd == pwd) {
                cout << "\n????????????????????????!\n"
                     << endl;
                system("pause");
                system("cls");
                tea = new Teacher(id, file_name);
                teacher_menu(tea);
                return;
            }
        }

    } else if (type == 3) {  //???????????????
        string file_name, file_pwd;
        while (ifs >> file_name >> file_pwd) {
            if (file_name == id && file_pwd == pwd) {
                cout << "\n?????????????????????!\n"
                     << endl;
                system("pause");
                system("cls");
                Admin* admin = nullptr;
                admin = new Admin(file_name);
                admin_menu(admin);
                return;
            }
        }
    }
    cout << "\n??????????????????! ??????????????????????????????\n"
         << endl;
    system("pause");
    system("cls");

    return;
}

//??????????????????
void new_stu_reg() {
    string stu_id, name, pwd, group;
    cout << "\n?????????????????????: ";
    cin >> group;
    cout << "\n?????????????????????: ";
    cin >> stu_id;
    cout << "\n???????????????????????????: ";
    cin >> name;
    cout << "\n???????????????????????????: ";
    cin >> pwd;

    // IO?????????????????????????????? ?????? -O3 ????????????
    //????????????????????? "test.txt" ???????????????????????????????????????
    ofstream ofs;
    ofs.open(STU_INFO_FILE, ios::app);
    if (!ofs.is_open()) {
        cout << "????????????????????????????????????!" << endl;
        ofs.close();
        return;
    }
    //?????? ?????? ??????
    ofs << stu_id << ' ' << pwd << ' ' << name << ' ' << group << endl;
    ofs.close();
    cout << "\n??????????????????, ????????????????????????!\n\n";
    system("pause");
    system("cls");
}

//??????????????????
void new_teacher_reg() {
    string teacher_id, name, pwd;
    cout << "\n???????????????????????????: ";
    cin >> teacher_id;
    cout << "\n?????????????????????: ";
    cin >> name;
    cout << "\n???????????????????????????: ";
    cin >> pwd;

    ofstream ofs;
    ofs.open(TEACHER_INFO_FILE, ios::app);
    if (!ofs.is_open()) {
        cout << "????????????????????????????????????!" << endl;
        ofs.close();
        return;
    }
    //???????????? ?????? ??????
    ofs << teacher_id << ' ' << pwd << ' ' << name << endl;
    ofs.close();
    cout << "\n??????????????????, ????????????????????????!\n\n";
    system("pause");
    system("cls");
}

int main() {
    //??????????????????
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
        cout << "\t\t ----------------------------------\n";
        cout << "\t\t|       ??????????????????????????????       |\n";
        cout << "\t\t ----------------------------------\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t|          1.??????????????????          |\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t|          2.??????????????????          |\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t|          3.??????????????????          |\n";
        cout << "\t\t|                                  |\n";
        // cout << "\t\t|          4.??????????????????          |\n";
        // cout << "\t\t|                                  |\n";
        // cout << "\t\t|          5.??????????????????          |\n";
        // cout << "\t\t|                                  |\n";
        cout << "\t\t|          0.??????????????????          |\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t ----------------------------------\n";
        cout << "\n\n";
        cout << "?????????????????????: ";

        cin >> op;
        switch (op) {
            case 1:
                login(STU_INFO_FILE, 1);  //??????????????????
                break;
            case 2:
                login(TEACHER_INFO_FILE, 2);  //??????????????????
                break;
            case 3:
                login(ADMIN_INFO_FILE, 3);  //???????????????
                break;
                // case 4:
                //     new_stu_reg();
                //    break;
                // case 5:
                //    new_teacher_reg();
                //    break;
            case 0:
                cout << "\n???????????????\n\n";
                system("pause");
                return 0;
                break;
            default:
                cout << "????????????????????????, ???????????????!" << endl;
                system("pause");
                system("cls");
                break;
        }
    }
    system("pause");
    exit(0);
}
