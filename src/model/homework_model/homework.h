#ifndef NAVIGATION_HOMEWORK_H
#define NAVIGATION_HOMEWORK_H
#include <string>
using namespace std;

class Homework {
   public:
    string course_name;  //课程名称
    string course_id;    //课程唯一的编号
    string hw_ddl;       //截至日期

    Homework();
    //每个老师的学工号
    //每门课程的编号
    Homework(string teacher_id, string course_id, string course_name);

    void compress();         //压缩
    void decompress();       //解压缩
    void set_grades();       //作业评分
    void check_duplicate();  //作业查重
};
#endif  // NAVIGATION_HOMEWORK_H
