#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <ctime>

#include "../course_model/course.h"
#include "admin.h"
#include "guide.h"
#include "student.h"
#include "teacher.h"

//实现除了登录界面之外所有的图形化打印菜单

void Student::operMenu() {
    time_t now = time(0);
    char* dt = ctime(&now);
    cout << endl;
    cout << "欢迎学生：" << this->stu_name << " 登录! " << dt << endl;
    cout << "\t\t -----------------------\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     1.课程名称查询    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     2.课表课程查询    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     3.课程时间查询    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     4.活动名称查询    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     5.进入活动菜单    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     6.活动时间查询    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     7.进行路径导航    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     0.注销登出账号    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t -----------------------\n\n";
    cout << "请选择您的操作: ";
}

void Student::operMenuSub() {
    //
}

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
    cout << "课程名称：" << course_name << endl;
    cout << "每周课时数目：" << times_per_week << endl;
    for (int i = 0; i <= times_per_week - 1; i++) {
        single_course a = course_table[i];
        cout << " " << a.date << "第" << a.seq << "节" << a.sh << ":" << a.sm << "-" << a.fh << ":" << a.fm << " " << a.campus << a.place << endl;
    }
    cout << "任课教师：" << teacher_name << endl;
    cout << "课程群：" << course_qun << endl;
    cout << "当前进度："
         << " "
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
    cout << endl;
    cout << "\t\t -----------------------\n";
    cout << "\t\t|       课程页面        |\n";
    cout << "\t\t -----------------------\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     1.提交课程作业    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     2.提交课程资料    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     3.下载课程资料    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     4.作业名称查询    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     5.作业成绩排序    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     6.资料名称查询    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     7.资料权重排序    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t|     0.退出课程页面    |\n";
    cout << "\t\t|                       |\n";
    cout << "\t\t -----------------------\n";
    cout << "请选择您的操作: ";
}