#ifndef NAVIGATION_BUILDING_H
#define NAVIGATION_BUILDING_H

#include <string>
#include <vector>

using namespace std;

class Building {
   public:
    std::vector<int> adj;       // directly adjacent buildings
    std::pair<int, int> coord;  // coordinate
    std::string campus_type;    // which campus itself in

    Building() = default;
    Building(std::string);

    // void add_adj(Building adj); //添加邻接点，目前地图初始化写死，貌似不需要
    std::set<int>& get_adj(int building);  // get the adjacent building
};

#endif  // NAVIGATION_BUILDING_H
