#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

class Guide{
    public:
    int build_now; //现在所处的建筑位置
    int campus_now; //现在所处的校区

    /*
    TODO:考虑交通工具 地图加入道路拥挤程度(按照时间不同 这个是动态的...)
    */

    Guide();
    Guide(string in_campus); //现在所处的校区

    void guideOperMenu(); //导航选择菜单
    void print_path_by_course(); //输出最短路导航路径
    void print_path_by_location();
    void print_path_by_time();
};