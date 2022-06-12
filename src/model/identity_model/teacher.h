#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "../../global_file.h"
using namespace std;
struct single_course_t {
    string date;
    int seq;
    string place;
    string campus;
    int building_id;
    string course_name, course_id;
    int len;
    vector<string> words;
};

struct material_t {
    int weight;
    string name;
    string id;
    int len;
    vector<string> words;
};

struct hw_t {
    string name;
    int len;
    vector<string> words;
};
struct exam_t {
    int week;
    string date;
    int sh, sm, fh, fm;
    string campus;
    string place;
};
struct whole_course_t {
    int ref_book_number;
    int number;
    int homework_number;
    int material_number;
    int total_weeks;

    string course_id;
    string course_name;
    exam_t final;
    vector<string> ref_books;
    vector<single_course_t> course_table;
    vector<material_t> materials;
    vector<hw_t> hws;
    string teacher_name;
    string teacher_id;
    string course_qun;
    vector<string> stu_ids;
    int student_number;
    vector<int> hw_len;
    vector<vector<string> > hw_words;
    vector<int> ma_len;
    vector<vector<string> > ma_words;
};
struct logger_t {
    string now;
    string kind;
    string id;
    string sth;
    logger_t(string k, string i, string s) {
        time_t timep;
        time(&timep);
        now = asctime(gmtime(&timep));
        kind = k;
        id = i;
        sth = s;
    }
};
class Teacher {
   public:
    map<string, string> name_to_id;
    string teacher_id;                    //教职工号
    string name;                          //教师姓名
    vector<string> teaching_course_name;  //目前正在上的所有课名称
    vector<string> teaching_course_id;    //所有正在上的课的ID 可能会用到这个数组

    //以下为解压缩算法
    unsigned int unzip_lenstr;
    pair<char, int> unzip_chlen[257];
    map<char, string> unzip_code;
    map<string, char> unzip_decode;
    string unzip_text;

    Teacher();
    Teacher(string id, string name);

    //教师操作菜单
    void operMenu();

    void set_homework();  //布置作业

    void check_duplicate(string course_id, int times, vector<string> v);  //作业查重
    void decompress_homework(vector<string> v);                           //解压作业

    void mark_homework();  //教师批改作业

    void log(string sth);

    //以下为解压缩算法
    string charToStr(char x);
    void buildCodeTable(int n);
    void loadZip(const char* pathname);
    void unzip(const char* pathname);
    void decompress(string course, string time, vector<string> v);
};