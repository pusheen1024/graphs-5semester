vector<int> get_center(Graph &gr) {
	map<int, map<int, int>> dist;
	vector<int> vx;
	for (auto &[v, adj] : gr.g) vx.pb(v);
	for (int i : vx) {
		for (int j : vx) {
			dist[i][j] = INF;
		}
	}
	for (int v : vx) {
		for (auto e : gr.g[v]) {
			int u = e.other_end(v);
			dist[v][u] = (gr.weighted ? e.w : 1);
		}
		dist[v][v] = 0;
	}
	for (int i : vx) {
		for (int j : vx) {
			for (int k : vx) {
				dist[i][k] = min(dist[i][k], dist[i][j] + dist[j][k]);
			}
		}
	}
	auto exc = [&](int v) {
		int mx = 0;
		for (int u : vx) {
			mx = max(mx, dist[v][u]);
		}
		return mx;
	};
	int radius = INF;
	for (int v : vx) {
		radius = min(radius, exc(v));
	}
	if (radius == INF) {
		cout << "Граф несвязный, радиус бесконечный!" << '\n';
		return {};
	}
	vector<int> center;
	for (int v : vx) {
		if (exc(v) == radius) center.pb(v);
	}
	return center;
}
