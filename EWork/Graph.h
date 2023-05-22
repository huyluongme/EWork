#pragma once

#include "stdafx.h"

typedef struct {
	int n, m;
	vector<vector<int>> A;
	vector<int> duration;
}sGraph;

class Graph
{
	sGraph G;
	vector<int> L;
	vector<int> t, T;
	int alpha, beta;
	int total_duration;
public:
	string h = "";
	string h_du;
	sGraph* GetGraph();
	void InitGraph();
	void AddEdge();
	int CalcInDeg(int u);
	int CalcOutDeg(int u);
	void TopoSort();
	void CalcStartEnd();
	void GraphProcess();
	vector<int> GetRanking();
	vector<int> Get_t();
	vector<int> Get_T();
	int GetTotalDuration();
};

extern Graph gGraph;