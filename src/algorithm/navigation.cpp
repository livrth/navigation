#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#define DBL_EPS 1e-6

struct Node {
	int id;
	double dis;

	bool operator<(const Node x) const {
		return x.dis < dis;
	}
};

struct Edge {
	int to;
	int next;
	double distance;
	bool bicycle_passable;
	double congestion_rate;
};

struct Path {
	int to;
	double distance;
};



