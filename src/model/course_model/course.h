#ifndef NAVIGATION_COURSE_H
#define NAVIGATION_COURSE_H

#include <iostream>
#include <string>

using namespace std;

class Course {
    public:
    string course_id; //课程编号
    string course_name; //课程名称
    
    Course();
    Course(string course_id, string course_name);
    void init();
    void operMenu();
    void submit_homework();
    void submit_material();
    void download_material();
    void query_homework_by_grades();
    void query_material_by_name();
    void query_material_by_weight();
};

#endif  // NAVIGATION_COURSE_H
