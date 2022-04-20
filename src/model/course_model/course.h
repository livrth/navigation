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
};

#endif  // NAVIGATION_COURSE_H
