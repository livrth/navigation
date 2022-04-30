#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;
#define MAX_LENGTH 12;
/*int starttime_h;
   int starttime_m;
   int finishitime_h;
   int finishitime_m;*/
/*struct single_course{
   string date;
   int seq;
   string place;
   string name;
   string course_id;
   single_course(string d,int s,string p,string n,string c):date(d),
   seq(s),place(p),name(n),course_id(c){} 
};*/

 struct Node{
    int left,right,size,value,num;
    Node(int l,int r,int s,int v):left(l),right(r),size(s),value(v),num(1){}
    Node(){}
};

class Student {
   public:
    string stu_name;//学生姓名
    string    stu_id;       //学号 唯一区分学生
    string group_id;//班级
    map<string,string> name_to_id;//在找到正确的名字后必须通过名字找到对应的下标
    map<int,pair<string,string> > time_to_place;//在找到合理的时间后必须通过时间查找到对应的地名（校区+建筑）
    map<int,string> time_to_id;//在找到合理的时间后必须通过时间查找到对应的下标
    string my_course_table[6][12];//我的课程表
    string number_to_date[8]={"No","Mon","Tue","Wed","Thu","Fri","Sar","Sun"};
    Node t[1000];//课程时间表
    int cnt=0;   //二叉树节点数
    int root=0;//根
    int course_start_time_table[12]={0,8*60,8*60+50,9*60+50,10*60+40,11*60+30,13*60,13*60+50,14*60+45,15*60+40,16*60+40,17*60+35};
    int course_finish_time_table[12]={0,8*60+45,9*60+35,10*60+35,11*60+25,12*60+15,13*60+45,14*60+35,15*60+30,16*60+25,17*60+25,18*60+10};
    Student();
    Student(string id, string name,string group);

    //学生界面操作的菜单
    void operMenu();
    void operMenuSub();

    //课内信息管理和查询
    void query_by_course_name();   //通过课程名称查询
    void query_by_course_table();  //通过课表查询

    //void upload_course_material();  //上传课程资料
    //void upload_home_work();        //上传作业

    //课外信息管理和查询
         //查询课外活动
    

    //课程导航
    void guide_now();  //进行课程路径导航

   void update(int root);//二叉搜索树
   int rank(int x,int root);
   int kth(int x,int root);
   void insert(int x,int root);

   void init();      //初始化

   void set_activity();    // 设置活动
   void delete_activity();
   void change_activity();
   void query_activity();
   void set_activity_alarm();  //设定课外活动闹钟 

   void query_by_course_time();   // 通过时间查询地点
   
   void course_menu(string object_id,string object_name,string student_id);
};