#include "student.h"
#include <fstream>
Student::Student() {
}

Student::Student(string id, string name) {
    this->stu_id = id;
    this->stu_name = name;
}

void Student::query_by_course_name() {
}

void Student::query_by_course_table() {
}

void Student::upload_course_material() {
}

void Student::set_activity_alarm() {
}

void Student::guide_now() {
}

void Student::query_activity() {
}

void Student::upload_home_work() {
}

void Student::update(int root){
    t[root].size=t[t[root].left].size+t[t[root].right].size+t[root].num;
}

int Student::rank(int x,int root){
    if(root){
        if(x<t[root].value)
        return rank(x,t[root].left);
        if(x>t[root].value)
        return rank(x,t[root].right)+t[t[root].left].size+t[root].num;
        return t[t[root].left].size+t[root].num;
    }
    return 1;
}

int Student::kth(int x,int root){
    if(x<=t[t[root].left].size)return kth(x,t[root].left);
    if(x<=t[t[root].left].size+t[root].num)return t[root].value;
    return kth(x-t[t[root].left].size-t[root].num,t[root].right);
}

void Student::insert(int x,int root){
    if(x<t[root].value)
    if(!t[root].left)
    t[t[root].left=++cnt]=Node(0,0,1,x);
    else insert(x,t[root].left);
    else if(x>t[root].value)
    if(!t[root].right)t[t[root].right=++cnt]=Node(0,0,1,x);
    else insert(x,t[root].right);
    else t[root].num++;
    update(root);
}

void Student::init(){
    string courese_table_filename="../../src/model/identity_model/course_table/"+stu_id+"_course_table.txt";
    ifstream ifs;
    ifs.open(courese_table_filename, ios::in);

    if (!ifs.is_open()) {
        cout << "用户文件不存在" << endl;
        ifs.close();
        return;
    }

    string date,place,course_name,course_id;
    int start_h,finish_h,start_m,finish_m;
    t[root=++cnt]=Node(0,0,1,2147483647);
    while(ifs >>date>>start_h>>start_m>>finish_h>>finish_m>>place>>course_name>>course_id){
        int time=0;
        if(date.find("Mon")!=-1)time+=0 ;
        if(date.find("Tue")!=-1)time+=1440 ;
        if(date.find("Wed")!=-1)time+=2880 ;
        if(date.find("Thu")!=-1)time+=4320 ;
        if(date.find("Fri")!=-1)time+=5760 ;
        if(date.find("Sar")!=-1)time+=7200 ;
        if(date.find("Sun")!=-1)time+=8640 ;
        time+=start_h*60+start_m;
        insert(time,root);
        name_to_id[course_name]=course_id;
        time_to_place[time]=place;
        time_to_id[time]=course_id;
        my_course_table.push_back(single_course(date,start_h,start_m,finish_h,finish_m,place,course_name,course_id));
    }
    ifs.close();
}

void Student::query_by_course_time(){
    int hour;
    int min;
    int date;
    int time;
    cout<<"\n 1:星期一";
    cout<<"\n 2：星期二";
    cout<<"\n 3：星期三";
    cout<<"\n 4：星期四";
    cout<<"\n 5：星期五";
    cout<<"\n 6：星期六";
    cout<<"\n 7：星期日"; 
     cout<<"\n请选择星期：";
    cin>>date;
    cout<<"\n请以格式 小时 ：分钟 输入时间,输入小时后按回车:\n";
    cin>>hour;
    cout<<":";
    cin>>min;
    time=(date-1)*1440+60*hour+min;
    int close_t;
    int r=rank(time,root);
   
    if(r!=cnt){
       close_t=kth(r,root);
    }
    else {close_t=kth(1,root);
    }
    cout<<time_to_place[close_t];
}

void Student::set_activity(){
}