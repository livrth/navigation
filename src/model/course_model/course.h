#ifndef NAVIGATION_COURSE_H
#define NAVIGATION_COURSE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
using namespace std;
struct single_course{
   string date;
   int seq;
   string place;
   string campus;
};
struct exam{
    int week;
    int start_hour,start_min,finish_hour,finish_min;
    string campus;
    string place;
};
struct material{
    int weight;
    string name;
    string id;
};
class Course {
    public:
    string course_id; //课程编号
    string course_name; //课程名称
    int times_per_week,homework_number,material_number,ref_book_number,total_weeks,student_number;
    vector<string> ref_books;
    vector<single_course> client_table;
    map<int,pair<string,int> > hw_table;
    vector<material> materials;
    string teacher_name;
    string teacher_id;
    string student_id;
    string course_qun;
    exam final;
    Course();
    Course(string course_id, string course_name,string sdudent_id);
    void init();
    void operMenu();
    void submit_homework();
    void submit_material();
    void download_material();
    void query_homework_by_name();
    void query_homework_by_grades();
    void query_material_by_name();
    void query_material_by_weight();
};

#endif  // NAVIGATION_COURSE_H
