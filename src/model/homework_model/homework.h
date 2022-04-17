#ifndef NAVIGATION_HOMEWORK_H
#define NAVIGATION_HOMEWORK_H
#include "Model.h"
class Homework: public Model{
private:
    Id studentid=-1;
    Id courseid=-1;
    Id teacherid=-1;
    bool  commit=false;
    std::string description="";
    double check_result;
    double grades;
    std::string compress_address="";
    std::string code_address="";
    std::string decompress_address="";
public:
    Homework(Id id,std::string name,Id studentid, std::string description,Id courseid,Id teacherid);
    void print();
    void set_grades(double grades);
    void set_commit();
    void set_check_result(double check_result);
    double get_grades();
    std::string get_commit();
    double get_check_result();
    std::string get_compress_address();
    std::string get_code_address();
    std::string get_decompress_address();
    void submit(std::string location);
    void decode();
};
#endif //NAVIGATION_HOMEWORK_H

