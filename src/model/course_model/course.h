#ifndef NAVIGATION_COURSE_H
#define NAVIGATION_COURSE_H
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
using namespace std;
struct single_course {
    string date;
    int seq;
    int sh, sm, fh, fm;
    string place;
    string campus;
};
struct exam {
    int week;
    string date;
    int st_hour, st_min, fi_hour, fi_min;
    string campus;
    string place;
};
struct material {
    int weight;
    string name;
    string id;
    int len;
    vector<string> words;
};
struct hw {
    int grades;
    string name;
    string state;
    int len;
    vector<string> words;
};
class Course {
   public:
    string course_id;    //课程编号
    string course_name;  //课程名称
    int course_start_time_table[12] = {0, 8 * 60, 8 * 60 + 50, 9 * 60 + 50, 10 * 60 + 40, 11 * 60 + 30, 13 * 60, 13 * 60 + 50, 14 * 60 + 45, 15 * 60 + 40, 16 * 60 + 40, 17 * 60 + 35};
    int course_finish_time_table[12] = {0, 8 * 60 + 45, 9 * 60 + 35, 10 * 60 + 35, 11 * 60 + 25, 12 * 60 + 15, 13 * 60 + 45, 14 * 60 + 35, 15 * 60 + 30, 16 * 60 + 25, 17 * 60 + 25, 18 * 60 + 10};
    int times_per_week, homework_number, material_number, ref_book_number, total_weeks, student_number;
    vector<string> ref_books;
    vector<single_course> course_table;
    map<int, hw> hws;
    vector<int> order_hws = {0};
    vector<material> materials;
    vector<int> order_materials;
    string teacher_name;
    string teacher_id;
    string user_id;
    string course_qun;
    exam final;
    Course();
    Course(string course_id, string course_name, string sdudent_id);
    void init();
    void operMenu();
    void submit_homework();
    void submit_material();
    void download_material();
    void query_homework_by_name();
    void query_homework_by_grades();
    void query_material_by_name();
    void query_material_by_weight();
    void qsort_m(int l, int r);
    void qsort_h(int l, int r);
};

#endif  // NAVIGATION_COURSE_H
