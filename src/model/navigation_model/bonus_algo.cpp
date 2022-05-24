#include <cstdlib>
#include <fstream>
#include <iostream>

#include "guide.h"

using namespace std;

// https://stackoverflow.com/questions/222413/find-the-shortest-path-in-a-graph-which-visits-certain-nodes
// complexity: O(K! + N^3) K is must pass node count N is all nodes in graph

void Guide::print_path_by_fixed_building() {  //选做算法  经过固定地点
    // cout << "请输入您当前所在校区: ";
    // string campus_now;
    // cin >> campus_now;
    cout << "请输入您所在的建筑编号(例如 5): ";
    int startp;
    cin >> startp;

    cout << "请输入您的目的建筑编号(例如 3): ";
    int endp;
    cin >> endp;

    //读入地图中的边
    string path_file;
    // test
    path_file = "../../src/model/navigation_model/shortest_path_test_map.txt";  //沙河校区

    // if (campus_now == "沙河")
    //     path_file = "../../src/model/navigation_model/path1.txt";  //沙河校区
    // else
    //     path_file = "../../src/model/navigation_model/path2.txt";  //西土城

    ifstream ifs;
    ifs.open(path_file, ios::in);
    if (!ifs.is_open()) {
        cout << "\n打开地图路径文件失败!" << endl;
        system("pause");
        return;
    }

    const int N = 220, INF = 1e9;
    int n = 210;
    int d[N][N];
    // init dist
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i == j)
                d[i][j] = 0;
            else
                d[i][j] = INF;

    auto floyd = [&]() {
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    };

    //读入地图边
    int a, b, x;
    while (ifs >> a >> b >> x) {
        d[a][b] = d[b][a] = min(d[a][b], x);  //判断重边
    }
    ifs.close();

    floyd();

    cout << "请输入您需要经过的固定建筑物编号(例如 3(建筑个数) 2 3 5): ";
    vector<int> node;
    int cnt;
    cin >> cnt;
    for (int i = 0; i < cnt; i++) {
        int x;
        cin >> x;
        node.push_back(x);
    }
    sort(node.begin(), node.end());

    int res = INF;
    vector<int> best_path;
    do {
        int dist = d[startp][node[0]];
        for (int i = 0; i < cnt - 1; i++) dist += d[node[i]][node[i + 1]];
        dist += d[node[cnt - 1]][endp];
        if (dist < res) {
            res = dist;
            best_path = node;
        }
    } while (next_permutation(node.begin(), node.end()));

    cout << "最短距离: " << res << endl;
    cout << startp << ' ';
    for (auto t : best_path) cout << t << ' ';  //必经点的最优排列
    cout << endp << endl;
    cout << "\n";

    // TODO: 目前只是得到最短路d[][]的表示路径
    //对于每一步最短路，都输出详细的单步路径

    system("pause");
    system("cls");
}
