#include <queue>
const int INF = 1e9;

Graph prim(Graph &gr) {
	map<int, int> min_edge;
	set<pair<int, int>> s;
	for (auto &[v, adj] : gr.g) {
		min_edge[v] = INF;
		s.insert({min_edge[v], v});
	}

	auto change_key = [&](int v, int new_key) {
		s.erase({min_edge[v], v});
		s.insert({new_key, v});
		min_edge[v] = new_key;
	};

	Graph ans;
	ans.n = gr.n;
	ans.m = gr.n - 1;
	ans.oriented = gr.oriented;
	ans.weighted = gr.weighted;

	int st = gr.g.begin()->first;
	change_key(st, 0);
	while (! s.empty()) {
		int v = s.begin()->second;
		s.erase(s.begin());
		for (auto e : gr.g[v]) {
			int u = e.other_end(v);
			if (s.count(make_pair(min_edge[u], u)) && min_edge[u] > e.w) {
				change_key(u, e.w);
				ans.add_edge(e);
			}
		}
	}
	return ans;
}
