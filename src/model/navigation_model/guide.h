#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Guide {
   public:
    int build_now;      //现在所处的建筑位置
    string campus_now;  //现在所处的校区 沙河 西土城
    string stu_id;      //当前操作的学生的学号

    /*
    TODO:考虑交通工具 地图加入道路拥挤程度(按照时间不同 这个是动态的...)
    TODO:选做的算法
    */

    Guide();
    Guide(string in_campus, string stu_id);  //现在所处的校区 当前操作学生的学号
    Guide(string stu_id);                    // 当前操作学生的学号

    void build_graph(string campus_now);  //每次导航时候都要先建图 放入内存中

    void guideOperMenu();                 //导航选择菜单
    void print_path_by_course();          //根据课程名称导航
    void print_path_by_location();        //根据上课地点导航 考虑不同校区
    void print_path_by_time();            //根据上课时间导航
    void print_path_by_fixed_building();  //选做算法 经过固定建筑(同校区内的建筑)
};