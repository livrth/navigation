#include <iostream>
#include <algorithm>
#include <string>

class Guide{
    public:
    int build_now; //现在所处的建筑位置
    int campus_now; //现在所处的校区

    /*
    TODO:考虑交通工具 地图加入道路拥挤程度(按照时间不同 这个是动态的...)
    */

    Guide();
    void print_path(); //输出最短路导航路径
};