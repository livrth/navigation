#include "course.h"
#include <fstream>
Course::Course(string course_id, string course_name,string sdudent_id) {
    this->course_id=course_id;
    this->course_name=course_name;
    this->student_id=sdudent_id;
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
      ifs>>a.date>>a.seq>>a.campus>>a.place;
      client_table.push_back(a);
    }
    ifs>>teacher_name>>teacher_id>>course_qun>>total_weeks;
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
    }
    ifs>>homework_number;
    for(int i=1;i<=homework_number;i++){
      ifs>>hw_table[i].first;
    }
    ifs>>student_number;
    string object_id;
    for(int i=1;i<=student_number;i++){
        ifs>>object_id;
        if(object_id==student_id){
             for(int i=1;i<=homework_number;i++){
                ifs>>hw_table[i].second;              
                }
        break;
        }
    }
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
}
void Course::query_material_by_name(){
}
void Course::query_material_by_weight(){
}

void Course::operMenu(){
    cout << endl;
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
