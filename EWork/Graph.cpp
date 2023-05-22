#include "Graph.h"

Graph gGraph;

sGraph* Graph::GetGraph() {
	return &this->G;
}

void Graph::InitGraph() {
	G.n = gProject.GetProjectSelected()->task.size() + 2;
	G.m = 0;
	vector<vector<int>> matrix(G.n, vector<int>(G.n, 0));
	G.A = matrix;

	alpha = G.n - 2; // 10
	beta = G.n - 1;

	G.duration.clear();
	G.duration = vector<int>(G.n);
	G.duration[alpha] = 0;
	for (int i = 0; i < gProject.GetProjectSelected()->task.size(); i++) {

		G.duration[i] = gProject.GetProjectSelected()->task[i].duration;
	}

	h_du.clear();
	for (auto t : G.duration) {
		h_du += to_string(t) + "\n";
	}
}

void Graph::AddEdge() {
	for (auto e : gProject.GetProjectSelected()->edges) {
		G.A[e.node_a][e.node_b]++;
		G.m++;
	}

	for (int u = 0; u < G.n - 2; u++)
	{
		if (CalcInDeg(u) == 0) {
			G.A[alpha][u]++;
			G.m++;
		}
	}

	for (int u = 0; u < G.n - 2; u++)
	{
		if (CalcOutDeg(u) == 0) {
			G.A[u][beta]++;
			G.m++;
		}
	}
}

int Graph::CalcInDeg(int u) {
	int indeg_u = 0;
	for (int v = 0; v < G.n; v++)
		if (G.A[v][u] > 0)
			indeg_u++;
	return indeg_u;
}

int Graph::CalcOutDeg(int u) {
	int outdeg_u = 0;
	for (int v = 0; v < G.n; v++)
		if (G.A[u][v] > 0)
			outdeg_u++;
	return outdeg_u;
}

void Graph::TopoSort() {
	vector<int> d(G.n);
	for (int u = 0; u < G.n; u++)
	{
		d[u] = 0;
		for (int v = 0; v < G.n; v++)
		{
			if (G.A[v][u] > 0)
				d[u]++;
		}
	}

	queue<int> Q;

	for (int u = 0; u < G.n; u++)
		if (d[u] == 0)
			Q.push(u);

	L.clear();

	while (!Q.empty())
	{
		int u = Q.front();
		// printf("%d\n", u);
		L.push_back(u);
		Q.pop();

		for (int v = 0; v < G.n; v++)
		{
			if (G.A[u][v] > 0)
			{
				d[v]--;
				if (d[v] == 0)
					Q.push(v);
			}
		}
	}
}

void Graph::CalcStartEnd() {
	for (int i = 1; i < L.size() - 1; i++) {
		int u = L[i];
		//MessageBoxA(0, to_string(u).c_str(), 0, 0);
		if (G.A[alpha][u] > 0) {
			//MessageBox(0, 0, 0, 0);
			gProject.GetProjectSelected()->task[u].start = gProject.GetProjectSelected()->start;
			gProject.GetProjectSelected()->task[u].end = gDate.addDays(gProject.GetProjectSelected()->start, gProject.GetProjectSelected()->task[u].duration - 1);
		}
		else {
			sDate start({ 0,0,0 });
			int x = 0;
			for (int v = 0; v < G.n - 2; v++) {
				if (G.A[v][u] > 0) {
					if (gDate.DateLater(gProject.GetProjectSelected()->task[v].end, start)) {
						start = gProject.GetProjectSelected()->task[v].end;
						x = v;
					}
				}
			}
			gProject.GetProjectSelected()->task[u].start = gDate.addDays(start, 1);
			gProject.GetProjectSelected()->task[u].end = gDate.addDays(gProject.GetProjectSelected()->task[u].start, gProject.GetProjectSelected()->task[u].duration - 1);
		}
	}
}

void Graph::GraphProcess() {
	InitGraph();
	AddEdge();

	TopoSort();



	t.clear();
	t = vector<int>(G.n);
	t[alpha] = 0;

	for (int i = 1; i < L.size(); i++) {
		int u = L[i];
		t[u] = INT_MIN;
		for (int x = 0; x < G.n; x++) {
			if (G.A[x][u] > 0)
				t[u] = max(t[u], t[x] + G.duration[x]);
		}
	}

	T.clear();
	T = vector<int>(G.n);
	T[beta] = t[beta];

	for (int i = L.size() - 2; i >= 0; i--) {
		int u = L[i];
		T[u] = INT_MAX;
		for (int v = 0; v < G.n; v++) {
			if (G.A[u][v] > 0)
				T[u] = min(T[u], T[v] - G.duration[u]);
		}
	}

	h = "";
	for (int i = 0; i < G.n; i++) {
		for (int j = 0; j < G.n; j++) {
			h += to_string(G.A[i][j]) + " ";
		}
		h += "\n";
	}

	for (int u = 0; u < G.n - 2; u++)
		h += to_string(t[u]) + " - " + to_string(T[u]) + "\n";

	h += "Duration: " + to_string(T[beta]);
	total_duration = t[beta];
	CalcStartEnd();

}

vector<int> Graph::GetRanking() {
	return this->L;
}

int Graph::GetTotalDuration() {
	return total_duration;
}

vector<int> Graph::Get_t(){
	return this->t;
}

vector<int> Graph::Get_T() {
	return this->T;
}