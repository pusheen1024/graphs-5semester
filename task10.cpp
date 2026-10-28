void dfs2(int v, Graph &gr, Graph &tree, set<int> &used, map<int, Edge> &p, map<int, int> &d) {
	used.insert(v);
	for (auto e : gr.g[v]) {
		int u = e.other_end(v);
		if (! used.count(u)) {
			tree.add_edge(Edge(v, u, e.w));
			tree.add_edge(Edge(u, v, e.w));
			p[u] = e;
			d[u] = d[v] + 1;
			dfs2(u, gr, tree, used, p, d);
		}
	}
}

vector<set<Edge>> negative_cycles(Graph &gr) {
	map<int, int> depth;
	depth[0] = 0;
	for (int i = 0; i < gr.n - 1; i++) {
		for (auto &[v, adj] : gr.g) {
			for (auto e : adj) {
				int u = e.other_end(v);
				depth[u] = min(depth[u], depth[v] + e.w);
			}
		}
	}
	bool fl = 0;
	for (auto &[v, adj] : gr.g) {
		for (auto e : adj) {
			int u = e.other_end(v);
			if (depth[u] > depth[v] + e.w) fl = 1;
		}
	}
	if (! fl) return {};
	Graph tree;
	tree.n = gr.n;
	tree.m = gr.n - 1;
	tree.oriented = gr.oriented;
	tree.weighted = gr.weighted;
	int v = gr.g.begin()->first;
	set<int> used;
	map<int, Edge> p;
	map<int, int> d;
	vector<vector<Edge>> cycles;
	dfs2(v, gr, tree, used, p, d);
	for (auto &[v, adj] : gr.g) {
		for (auto e : adj) {
			if (tree.edges.count(e)) continue;
			int u = e.other_end(v);
			int cur_u = u;
			int cur_v = v;
			while (d[cur_u] > d[cur_v]) {
				cur_u = p[cur_u].other_end(cur_u);
			}
			while (d[cur_v] > d[cur_u]) {
				cur_v = p[cur_v].other_end(cur_v);
			}
			int lca = cur_v;
			cur_u = u, cur_v = v;
			vector<Edge> path_u;
			while (cur_u != lca) {
				path_u.pb(p[cur_u]);
				cur_u = p[cur_u].other_end(cur_u);	
			}
			vector<Edge> path_v;
			while (cur_v != lca) {
				path_v.pb(p[cur_v]);
				cur_v = p[cur_v].other_end(cur_v);
			}
			path_u.pb(e);
			reverse(path_v.begin(), path_v.end());
			for (auto x : path_v) path_u.pb(x);
			cycles.pb(path_u);
		}
	}
	int mx = cycles.size();
	vector<set<Edge>> ans;
	vector<int> weights;
	set<set<int>> vertices;
	for (int mask = 0; mask < (1 << mx); mask++) {
		set<Edge> edges;
		for (int i = 0; i < mx; i++) {
			if (mask & (1 << i)) {
				for (int j = 0; j < cycles[i].size(); j++) {
					if (edges.count(cycles[i][j])) edges.erase(cycles[i][j]);
					else if (edges.count(cycles[i][j].get_symmetry())) edges.erase(cycles[i][j].get_symmetry());
					else edges.insert(cycles[i][j]);
				}
			}
		}
		set<int> vx;
		for (auto e : edges) {
			vx.insert(e.v);
			vx.insert(e.u);
		}
		if (! edges.empty() && ! vertices.count(vx)) {
			int weight = 0;
			for (auto e : edges) weight += e.w;
			if (weight < 0) {
				ans.pb(edges);
				weights.pb(weight);
				vertices.insert(vx);
			}
		}
	}
	for (int i = 0; i < ans.size(); i++) {
		cout << "Отрицательный цикл, вес = " << weights[i] << '\n';
		for (auto e : ans[i]) e.print_edge(cout, gr.weighted);
		cout << '\n';
	}
	return ans;
}
