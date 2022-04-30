#include "course.h"
#include <fstream>
Course::Course(string course_id, string course_name,string id) {
    this->course_id=course_id;
    this->course_name=course_name;
    this->user_id=id;
}
void Course::init(){
    string courese_filename="../../src/model/course_model/course_collection/"+course_id+"_course.txt";
    ifstream ifs;
    ifs.open(courese_filename, ios::in);

    if (!ifs.is_open()) {
        cout << "课程文件不存在" << endl;
        ifs.close();
        return;
    }

    ifs>>times_per_week;
    for(int i=1;i<=times_per_week;i++){
      single_course a;
      ifs>>a.date>>a.seq>>a.campus>>a.place>>course_name;
      a.sh=course_start_time_table[a.seq]/60;
      a.sm=course_start_time_table[a.seq]%60;
      a.fh=course_finish_time_table[a.seq]/60;
      a.fm=course_finish_time_table[a.seq]%60;
      number_table.push_back(a);
    }
    ifs>>teacher_name>>teacher_id>>course_qun>>total_weeks;
    ifs>>final.week>>final.date>>final.st_hour>>final.st_min>>final.fi_hour>>final.fi_min>>final.campus>>final.place;
    ifs>>ref_book_number;
    for(int i=1;i<=ref_book_number;i++){
      string book_name;
      ifs>>book_name;
      ref_books.push_back(book_name);
    }
    ifs>>material_number;
    for(int i=1;i<=material_number;i++){
      material a;
      ifs>>a.weight>>a.name>>a.id;
      materials.push_back(a);
      order_materials.push_back(i-1);
    }
    ifs>>homework_number;
    for(int i=1;i<=homework_number;i++){
      ifs>>hws[i].first;
    }
    ifs>>student_number;
    string object_id;
    for(int i=1;i<=student_number;i++){
        ifs>>object_id;
        if(object_id==user_id){
             for(int i=1;i<=homework_number;i++){
                ifs>>hws[i].second; 
                order_hws.push_back(i);         
                }
        break;
        }
    }
    ifs.close();
}

void Course::submit_homework(){
}
void Course::submit_material(){
}
void Course::download_material(){
}
void Course::query_homework_by_name(){
}
void Course::query_homework_by_grades(){
qsort_h(1,homework_number) ;
for(int i=1;i<=homework_number;i++){
cout<<"第"<<order_hws[i]<<"次作业"<<"  "<<hws[order_hws[i]].first<<"  "<<"成绩："<<hws[order_hws[i]].second<<endl;    
}
cout<<"请输入Yes来提交作业或者输入No来退出:";
string opt;
cin>>opt;
if(opt=="No")return;
else submit_homework();    
}
void Course::query_material_by_name(){
}
void Course::query_material_by_weight(){ 
qsort_m(0,material_number-1);
for(int i=0;i<=material_number-1;i++){
cout<<materials[order_materials[i]].name<<"  权重："<<materials[order_materials[i]].weight<<endl;
}
cout<<"请输入Yes来下载某份资料或者输入No来退出:";
string opt;
cin>>opt;
if(opt=="No")return;
else download_material();
}

void Course::operMenu(){
    cout << endl;
    cout<<"课程名称："<<course_name<<endl;
    cout<<"每周课时数目："<<times_per_week<<endl;
    for(int i=0;i<=times_per_week-1;i++){
      single_course a=number_table[i];
      cout<<a.date<<"第"<<a.seq<<"节"<<a.sh<<":"<<a.sm<<"-"<<a.fh<<":"<<a.fm<<" "<<a.campus<<a.place<<endl;
    }
    cout<<endl;
    cout<<"任课教师："<<teacher_name<<endl;
    cout<<"课程群："<<course_qun<<endl;
    cout<<"当前进度："<<" "<<"/"<<total_weeks<<endl;
    cout<<"考试时间："<<"第"<<final.week<<"周"<<final.date;
    cout<<final.st_hour<<":"<<final.st_min<<"-"<<final.fi_hour<<":"<<final.fi_min<<endl;
    cout<<"考试地点："<<final.campus<<final.place<<endl;
    cout<<"课程参考书籍："<<endl;
    for(int i=0;i<=ref_book_number-1;i++){
     cout<<ref_books[i]<<endl;
    }
    cout<<"课程电子资料："<<endl;
    for(int i=0;i<=material_number-1;i++){
     cout<<materials[i].name<<"  权重:"<<materials[i].weight<<endl;
    }
    cout<<"课程作业："<<endl;
    for(int i=1;i<=homework_number;i++){
     cout<<"第"<<i<<"次作业"<<"  "<<hws[i].first<<"  "<<"成绩："<<hws[i].second<<endl;
    }
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

void Course::qsort_h(int l,int r){
int i=l,j=r,flag=hws[order_hws[(l+r)/2]].second,tmp;
do{
    while(hws[order_hws[i]].second>flag)i++;
    while(hws[order_hws[j]].second<flag)j--;
    if(i<=j){
        tmp=order_hws[i];order_hws[i]=order_hws[j];order_hws[j]=tmp;
        i++;j--;
    }
}while(i<=j);
if(l<j)qsort_h(l,j);
if(i<r)qsort_h(i,r);
}

void Course::qsort_m(int l,int r){
int i=l,j=r,flag=materials[order_materials[(l+r)/2]].weight,tmp;
do{
    while(materials[order_materials[i]].weight>flag)i++;
    while(materials[order_materials[j]].weight<flag)j--;
    if(i<=j){
        tmp=order_materials[i];order_materials[i]=order_materials[j];order_materials[j]=tmp;
        i++;j--;
    }
}while(i<=j);
if(l<j)qsort_m(l,j);
if(i<r)qsort_m(i,r);    
}