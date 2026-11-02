void k_shortest_paths(Graph &gr, int s_v, int s_u, int k) {
	priority_queue<pair<int, pair<int, vector<int>>>> q;
	map<int, int> d;
	q.push({0, {s_v, {s_v}}});
	map<int, int> used;
	vector<pair<vector<int>, int>> ans;
	while (! q.empty()) {
		auto [dv, p] = q.top();
		auto [v, way] = p;
		q.pop();
		cout << v << '\n';
		if (used[v] >= k) continue;
		used[v]++;
		for (auto e : gr.g[v]) {
			int u = e.other_end(v);
			int nd = dv + e.w;
			vector<int> way1 = way;
			way1.pb(u);
			if (u == s_u) ans.pb({way1, nd});
			if (used[u] < k) q.push({-nd, {u, way1}});
		}
	}
	int i = 1;
	for (auto &[way, depth] : ans) {
		cout << "Кратчайший путь №" << i << " длины " << depth << ":\n";
		for (int x : way) cout << x << ' ';
		cout << '\n';
		i++;
	}
}
