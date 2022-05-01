#include "building.h"
#include <iostream>
#include <fstream>
#include <set>
using namespace std;

//地图都写死了
//这个building 整个 campus_model 是否需要待定

Building::Building() {

}

Building::Building(string s) {  //所属校区
    this->campus_type = s;
}

//获取当前编号建筑的所有邻接点
std::set<int>& Building::get_adj(int building_number) {
    set<int> adj;
    ifstream ifs;
    ifs.open("map.txt", ios::in);
    int build1, build2, dist;
    while(ifs >> build1 >> build2 >> dist){
        if(building_number == build1) adj.insert(build2);
        if(building_number == build2) adj.insert(build1);
    }
    ifs.close();
    return adj;
}