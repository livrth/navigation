#ifndef NAVIGATION_BUILDING_H
#define NAVIGATION_BUILDING_H

#include <memory>
#include <vector>
#include <string>
#include "../model.h"

class Building : public Model{
   private:
    std::vector<Id> adj; //directly adjacent buildings
    std::pair<double, double> coord; //coordinate
    std::string campus_type; //which campus itself in

   public:
    Building() = default;
    Building(std::string);

    void set_coord();
    std::pair<int,int> get_coord();

    std::string get_campus_type();
    void set_campus_type();

    void add_adj(Building adj);
    std::vector<int> & get_adj(Id building); //get the adjacent building
};

#endif  // NAVIGATION_BUILDING_H
