#include <bits/stdc++.h>
using namespace std;

/*
记录路径: https://blog.nowcoder.net/n/c500fe2e18bc41d9ae9a3d446199f939?from=nowcoder_improve
*/

const int N = 210, INF = 1e9;
int n, m, k;
int d[N][N];
int P[N][N];  //记录DP过程中间点, 还要记录路径

void Path(int u, int v, ofstream& ofs) {  // 求出  u v 最短路经过的所有点, 输出不包括起点终点
    if (P[u][v] == 0) return;
    Path(u, P[u][v], ofs);
    ofs << P[u][v] << ' ';
    Path(P[u][v], v, ofs);
    return;
}

void floyd() {
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (d[i][k] + d[k][j] < d[i][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                    P[i][j] = k;
                }
}

int main() {
    n = 20, m = 210;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i == j)
                d[i][j] = 0;
            else
                d[i][j] = INF;

    //读入地图
    string map_file = "bike_map2.txt";
    ifstream ifs;
    ifs.open(map_file, ios::in);
    if (!ifs.is_open()) {
        cout << "地图文件读取失败!\n"
             << endl;
        system("pause");
        return 0;
    }

    int a, b, x;
    while (m--) {
        ifs >> a >> b >> x;
        d[a][b] = d[b][a] = min(d[a][b], x);  //判断重边 无向图
    }
    ifs.close();
    floyd();

    //求出的最短路和路径放在 path1.txt path2.txt
    ofstream ofs;
    ofs.open("bike_path2.txt");
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {  //之后改为j=1开始的无向图
            if (i == j)
                ofs << i << ' ' << j << ' ' << 0 << endl;
            else {
                ofs << i << ' ' << j << ' ';
                ofs << i << ' ';
                Path(i, j, ofs);
                ofs << j << ' ';
                ofs << d[i][j] << endl;
            }
        }
    ofs.close();

//测试连通性
#ifdef DEBUG
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            if (d[i][j] > INF / 2) {
                cout << i << ' ' << j << "---------------" << endl;
            }
        }
    cout << "done" << endl;
#endif

//小地图测试算法正确性
#ifdef DEBUG2
    for (int i = 1; i <= 5; i++)
        for (int j = i; j <= 5; j++) {
            if (i == j)
                cout << i << ' ' << j << ' ' << 0 << endl;
            else {
                cout << i << ' ' << j << " ------- ";
                cout << i << ' ';
                Path(i, j);
                cout << j << endl;
            }
        }
#endif
    return 0;
}