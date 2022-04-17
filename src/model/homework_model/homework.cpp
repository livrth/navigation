#include "Homework.h"
using std::string,std::to_string;
Homework::Homework(Id id, string name,Id studentid,string description,Id courseid,Id teacherid){
    this->set_id(id);
    this->set_name(name);
    this->studentid=studentid;
    this->description=description;
    this->courseid=courseid;
    this->teacherid=teacherid;
    this->compress_address=to_string(teacherid)+"\\"+to_string(courseid)+"\\"+to_string(studentid)+"\\"+"1";
    this->code_address=to_string(teacherid)+"\\"+to_string(courseid)+"\\"+to_string(studentid)+"\\"+"2";
    this->decompress_address=to_string(teacherid)+"\\"+to_string(courseid)+"\\"+to_string(studentid)+"\\"+"3";
}
void Homework::print(){
    std::cout<<"student:"<<studentid<<' '<<"name:"<<this->get_name()<<' '<<commit;
    std::cout<<"\n"<<"grades:"<<grades<<' '<<"compress address:"<<compress_address;
}
void Homework::set_grades(double grades){
    this->grades=grades;
}
void Homework::set_commit(){
    this->commit=true;
}
void Homework::set_check_result(double check_result){
    this->check_result=check_result;
}
double Homework::get_grades(){
    return this->grades;
}
string Homework::get_commit(){
    if (this->commit==falese)return "commited";
    else return "not commited";
}
double Homework::get_check_result(){
    return this->check_result;
}
string Homework::get_compress_address(){
    return this->compress_address;
}
string Homework::get_code_address(){
    return this->code_address;
}
string Homework::get_decompress_address(){
    return this->decompress_address;
}
void Homework::submit(std::string location){
    //encode
}
void Homework::decode(){
    //decode
    //check same
}

