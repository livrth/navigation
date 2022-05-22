#include <bits/stdc++.h>
using namespace std;

//生成地图的代码，同时考虑拥挤度, 不会依赖其他代码或者被其他代码依赖
//无向图 边权均为正数，可能有环, 也可能有重边，重边意味着两个建筑间有多条路径
//生成的数据写入 ./map.txt

/*
map1.txt 第一个校区地图
map2.txt 第二个校区地图
数据格式：
建筑1编号 建筑2编号 距离
*/

void gen() {
    std::random_device seed;
    std::mt19937 rand(seed());
    std::uniform_int_distribution<int> dist(0, 999);        //距离，单位为米，随机距离 [1,1000]
    std::uniform_int_distribution<int> building_id(0, 19);  //建筑编号 [1,20]
    std::uniform_int_distribution<int> crowdedness(0, 2);  //道路拥挤程度 [1,3] 表示时间加倍的倍数

    ofstream ofs;
    ofs.open("map2_crowd.txt");

    //选210条边
    //建筑距离>50m的才符合实际
    int cnt = 0;
    while (1) {
        int build1 = building_id(rand) + 1;
        int build2 = building_id(rand) + 1;
        int random_dist = (dist(rand) + 1) * (crowdedness(rand) + 1); //距离*拥挤度
        if (random_dist < 50) continue;
        if (build1 == build2) continue;  //排除自环的情况
        cnt++;
        ofs << build1 << ' ' << build2 << ' ' << random_dist << endl;
        if (cnt >= 210) break;
    }
    ofs.close();
}

int main_() {
    gen();
    return 0;
}