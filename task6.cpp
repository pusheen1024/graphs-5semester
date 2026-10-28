#include <queue>

void dfs(int v, Graph &gr, int c, map<int, int> &comps) {
	comps[v] = c;
	for (auto e : gr.g[v]) {
		int u = e.other_end(v);
		if (! comps.count(u)) {
			dfs(u, gr, c, comps);
		}
	}
}

int cyclomatic_number(Graph &gr) {
	map<int, int> comps;
	int c = 0;
	for (auto &[v, adj] : gr.g) {
		if (! comps.count(v)) {
			dfs(v, gr, c++, comps);
		}
	}
	return gr.m - (gr.n - c);
}
