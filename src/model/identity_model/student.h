#pragma once
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;
#define MAX_LENGTH 12;
/*int starttime_h;
   int starttime_m;
   int finishitime_h;
   int finishitime_m;*/
struct single_activity {
    string date;
    int sh, sm, fh, fm;
    string place;
    string name;
    string clock_state;
    char state;
    int len;
    vector<string> words;
    bool operator<(const single_activity &a) const {
        return (a.date < date || a.sh < sh || a.sm < sm || a.place < place);
    }
    /*single_activity(string d,int sh,int sm,int fh,int fm, string p,string n,string c,string i):date(d),
    sh(sh),sm(sm),fh(fh),fm(fm),place(p),name(n),clock_state(c),activity_id(i){}
    single_activity(){}*/
};

struct Node {
    int left, right, size, value, num;
    Node(int l, int r, int s, int v) : left(l), right(r), size(s), value(v), num(1) {}
    Node() {}
};

class Student {
   public:
    string stu_name;  //学生姓名
    string stu_id;    //学号 唯一区分学生
    string group_id;  //班级

    map<string, string> name_to_id;                         //在找到正确的名字后必须通过名字找到对应的下标
    map<int, pair<string, string>> time_to_place;           //在找到合理的时间后必须通过时间查找到对应的地名（校区+建筑）
    string my_course_table[6][12];                          //我的课程表
    Node t1[1000];                                          //课程时间表
    int cnt1 = 0;                                           //二叉树节点数
    map<string, vector<single_activity>> name_to_activity;  //在找到正确的名字后必须通过名字找到对应的活动
    map<int, vector<single_activity>> time_to_activity;     //在找到合理的时间后必须通过时间查找到对应的活动
    Node t2[1000];
    int cnt2 = 0;

    map<string, set<string>> word_to_sen;
    map<string, set<string>> word_to_par;

    int ca_number;  //班级活动数目
    string number_to_date[8] = {"No", "Mon", "Tue", "Wed", "Thu", "Fri", "Sar", "Sun"};
    map<char, string> kind = {{'p', "个人"}, {'c', "班级"}, {'d', "最近删除"}};
    int root = 0;  //根
    int course_start_time_table[12] = {0, 8 * 60, 8 * 60 + 50, 9 * 60 + 50, 10 * 60 + 40, 11 * 60 + 30, 13 * 60, 13 * 60 + 50, 14 * 60 + 45, 15 * 60 + 40, 16 * 60 + 35, 17 * 60 + 25};
    int course_finish_time_table[12] = {0, 8 * 60 + 45, 9 * 60 + 35, 10 * 60 + 35, 11 * 60 + 25, 12 * 60 + 15, 13 * 60 + 45, 14 * 60 + 35, 15 * 60 + 30, 16 * 60 + 25, 17 * 60 + 20, 18 * 60 + 10};
    Student();
    Student(string id, string name, string group);

    //学生界面操作的菜单
    void operMenu();
    void operMenuSub();

    // void upload_course_material();  //上传课程资料
    // void upload_home_work();        //上传作业

    //课外信息管理和查询
    //查询课外活动

    //课程导航
    void guide_now();  //进行课程路径导航

    void update(int root, Node *t);  //二叉搜索树
    int rank(int x, int root, Node *t);
    int kth(int x, int root, Node *t);
    void insert(int x, int root, Node *t, int &cnt);

    void init();  //初始化

    //课内信息管理和查询
    void query_by_course_name();   //通过课程名称查询
    void query_by_course_table();  //通过课表查询
    void query_by_course_time();   // 通过时间查询地点

    void query_by_activity_name();
    void query_by_activity_time();
    void set_activity();  // 设置活动
    void delete_activity();
    void change_activity();

    void set_activity_alarm();  //设定课外活动闹钟

    void course_menu(string object_id, string object_name, string student_id);
    void activity_menu();
    void clash_test(string date, int st, int ft);
    bool interact(int x1, int x2, int y1, int y2);
};