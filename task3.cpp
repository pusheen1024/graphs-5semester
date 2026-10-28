// task2-8

vector<int> get_vertices(Graph &graph) {
	map<int, int> in;
	map<int, int> out;
	for (auto &[v, adj] : graph.g) {
		for (auto e : adj) {
			int u = e.other_end(v);
			out[v]++;
			in[u]++;
		}
	}
	vector<int> res;
	for (auto &[v, adj] : graph.g) {
		if (out[v] > in[v]) res.pb(v);
	}
	return res;
}
