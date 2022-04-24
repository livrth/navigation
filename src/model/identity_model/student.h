#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

struct single_course{
   string date;
   int starttime_h;
   int starttime_m;
   int finishitime_h;
   int finishitime_m;
   string place;
   string name;
   string course_id;
   single_course(string d,int sh,int sm,int fh,int fm,string p,string n,string c):date(d),
   starttime_h(sh),starttime_m(sm),finishitime_h(fh),finishitime_m(fm),place(p),name(n),
   course_id(c){}
};

 struct Node{
    int left,right,size,value,num;
    Node(int l,int r,int s,int v):left(l),right(r),size(s),value(v),num(1){}
    Node(){}
};

class Student {
   public:
    string stu_name;//学生姓名
    string    stu_id;       //学号 唯一区分学生
    map<string,string> name_to_id;//在找到正确的名字后必须通过名字找到对应的下标
    map<int,string> time_to_place;//在找到合理的时间后必须通过时间查找到对应的地名
    map<int,string> time_to_id;//在找到合理的时间后必须通过时间查找到对应的下标
    vector<single_course> my_course_table;//我的课程表
    Node t[1000];//课程时间表
    int cnt=0;   //二叉树节点数
    int root=0;//根

    Student();
    Student(string id, string name);

    //学生界面操作的菜单
    void operMenu();
    void operMenuSub();

    //课内信息管理和查询
    void query_by_course_name();   //通过课程名称查询
    void query_by_course_table();  //通过课表查询

    void upload_course_material();  //上传课程资料
    void upload_home_work();        //上传作业

    //课外信息管理和查询
    void query_activity();      //查询课外活动
    void set_activity_alarm();  //设定课外活动闹钟

    //课程导航
    void guide_now();  //进行课程路径导航

   void update(int root);//二叉搜索树
   int rank(int x,int root);
   int kth(int x,int root);
   void insert(int x,int root);

   void init();      //初始化

   void set_activity();    // 设置活动

   void query_by_course_time();   // 通过时间查询地点
};