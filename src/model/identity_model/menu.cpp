#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <ctime>

#include "../course_model/course.h"
#include "admin.h"
#include "guide.h"
#include "student.h"
#include "teacher.h"

//实现除了登录界面之外所有的图形化打印菜单
int week = 15;
void Teacher::operMenu() {
    system("cls");
    time_t now = time(0);
    char* dt = ctime(&now);
    cout << endl;
    cout << "欢迎教师：" << this->name << " 登录! " << dt << endl;
    cout << "\t\t -----------------------\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     1.教师布置作业    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     2.教师批改作业    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     0.注销登出账号    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t -----------------------\n\n";
    cout << "请选择您的操作: ";
}

void Admin::operMenu() {
    system("cls");
    time_t now = time(0);
    char* dt = ctime(&now);
    cout << endl;
    cout << "欢迎管理员: " << this->user_name << " 登录! " << dt << endl;
    cout << "\t\t -----------------------\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     1.班级活动管理    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     2.发布新的课程    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     3.修改原有课程    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     0.注销登出账号    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t -----------------------\n\n";
    cout << "请选择您的操作: ";
}

void Guide::guideOperMenu() {
    system("cls");
    cout << endl;
    cout << "\t\t ----------------------------\n";
    cout << "\t\t|           导航页面         |\n";
    cout << "\t\t ----------------------------\n";
    cout << "\t\t|                            |\n";
    cout << "\t\t|     1.根据课程名称导航     |\n";
    cout << "\t\t|                            |\n";
    cout << "\t\t|     2.根据上课地点导航     |\n";
    cout << "\t\t|                            |\n";
    cout << "\t\t|     3.根据上课时间导航     |\n";
    cout << "\t\t|                            |\n";
    cout << "\t\t|     4.经过固定地点导航     |\n";
    cout << "\t\t|                            |\n";
    cout << "\t\t|     0.退出当前导航系统     |\n";
    cout << "\t\t|                            |\n";
    cout << "\t\t ----------------------------\n\n";
    cout << endl;
}

void Course::operMenu() {
    cout << endl;
    cout << "\t ------------------------------------------\n";
    cout << "\t|                 课程页面                 |\n";
    cout << "\t ------------------------------------------\n";
    cout << "\t|                                          |\n";
    cout << "\t|     1.提交课程作业     5.作业成绩排序    |\n";
    cout << "\t|                                          |\n";
    cout << "\t|     2.提交课程资料     6.资料名称查询    |\n";
    cout << "\t|                                          |\n";
    cout << "\t|     3.下载课程资料     7.资料权重排序    |\n";
    cout << "\t|                                          |\n";
    cout << "\t|     4.作业名称查询     0.退出课程页面    |\n";
    cout << "\t|                                          |\n";
    cout << "\t ------------------------------------------\n";
    cout << endl;
    cout << "课程名称：" << course_name << endl;
    cout << "每周课时数目：" << times_per_week << endl;
    for (int i = 0; i <= times_per_week - 1; i++) {
        single_course a = course_table[i];
        cout << " " << a.date << "第" << a.seq << "节" << a.sh << ":" << a.sm << "-" << a.fh << ":" << a.fm << " " << a.campus << a.place << endl;
    }
    cout << "任课教师：" << teacher_name << endl;
    cout << "课程群：" << course_qun << endl;
    cout << "当前进度："
         << week
         << "/" << total_weeks << endl;
    cout << "考试时间："
         << "第" << final.week << "周" << final.date;
    cout << final.st_hour << ":" << final.st_min << "-" << final.fi_hour << ":" << final.fi_min << endl;
    cout << "考试地点：" << final.campus << final.place << endl;
    cout << "课程参考书籍：" << endl;
    for (int i = 0; i <= ref_book_number - 1; i++) {
        cout << "  " << ref_books[i] << endl;
    }
    if (ref_book_number == 0) cout << "暂无参考书籍";
    cout << "课程电子资料：" << endl;
    for (int i = 0; i <= material_number - 1; i++) {
        cout << "  " << materials[i].name << "  权重:" << materials[i].weight << endl;
    }
    if (material_number == 0) cout << "暂无资料";
    cout << "课程作业：" << endl;
    for (int i = 1; i <= homework_number; i++) {
        cout << "第" << i << "次作业"
             << "  " << hws[i].name << "  "
             << "成绩：" << hws[i].grades;
        cout << " 状态：" << hws[i].state << endl;
        // cout<<"  "<<"第"<<i<<"次作业"<<"  "<<hws[i].first<<"  "<<"成绩："<<hws[i].second<<endl;
    }
    if (homework_number == 0) cout << "暂无作业";
    cout << "请选择您的操作: ";
}
void Student::activity_menu() {
    system("pause");
    system("cls");
    while (true) {
        cout << "\t\t ----------------------------------\n";
        cout << "\t\t|             活动页面             |\n";
        cout << "\t\t ----------------------------------\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t|          1.添加个人活动          |\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t|          2.删除个人活动          |\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t|          3.修改个人活动          |\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t|          4.个人活动闹钟          |\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t|          5.活动类型查询          |\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t|          0.返回个人主页          |\n";
        cout << "\t\t|                                  |\n";
        cout << "\t\t ----------------------------------\n";
        cout << endl;
        cout << "\t\t\t\t\t\t\t活动表" << endl;
        for (int i = 2; i <= cnt2; i++) {
            vector<single_activity> x = time_to_activity[t2[i].value];
            for (vector<single_activity>::iterator it = x.begin(); it != x.end(); ++it) {
                cout << "活动时间：" << it->date << it->sh << ":" << it->sm << "-" << it->fh << ":" << it->fm << "    ";
                cout << "活动地点:" << it->place << "    "
                     << "活动名称：" << it->name << "    "
                     << "活动类型：";
                cout << kind[it->state] << "     "
                     << "闹钟属性：" << it->clock_state << endl;
                clash_test(it->date, it->sh * 60 + it->sm, it->fh * 60 + it->fm);
            }
        }
        cout << "\n\n";
        cout << "请选择您的操作: ";
        int op;
        cin >> op;
        if (op == 1) {
            set_activity();
        } else if (op == 2) {
            delete_activity();
        } else if (op == 3) {
            change_activity();
        } else if (op == 4) {
            set_activity_alarm();
        } else if (op == 5) {
            typequery();
        } else if (op == 0) {
            cout << "返回成功" << endl;
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
void Student::operMenu() {
    time_t now = time(0);
    char* dt = ctime(&now);
    if (!stop) show_new_time = true;
    bool week_counter = true;
    if (nowday == 6) week_counter = true;
    if (show_new_time) {
        nowday = this->weekly_sys_time / 1440;
        nowhour = this->weekly_sys_time % 1440 / 60;
        nowmin = this->weekly_sys_time % 1440 % 60;
        if (stop) show_new_time = false;
    }
    if (nowday == 0 && week_counter) {
        week++;
        week_counter = false;
    }
    cout << "                     模拟时间:" << number_to_date[nowday + 1] << " " << nowhour << ":" << nowmin;
    cout << endl;
    cout << "欢迎学生：" << this->stu_name << " 登录! " << dt << endl;
    cout << "\t ------------------------------------------\n";
    cout << "\t|                                          |\n";
    cout << "\t|     1.课程名称查询     6.活动时间查询    |\n";
    cout << "\t|                                          |\n";
    cout << "\t|     2.课程课表查询     7.进行路径导航    |\n";
    cout << "\t|                                          |\n";
    cout << "\t|     3.课程时间查询     8.时间快进二倍    |\n";
    cout << "\t|                                          |\n";
    cout << "\t|     4.活动名称查询     9.系统时间暂停    |\n";
    cout << "\t|                                          |\n";
    cout << "\t|     5.进入活动菜单     0.注销登出账号    |\n";
    cout << "\t|                                          |\n";
    cout << "\t ------------------------------------------\n\n";
    cout << "请选择您的操作: ";
}
