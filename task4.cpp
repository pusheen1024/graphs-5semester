bool is_subset (Graph &g1, Graph &g2) {
	for (auto &[v, adj] : g1.g) {
		if (! g2.g.count(v)) {
			return false;
		}
	}
	for (auto e : g1.edges) {
		if (! g2.edges.count(e)) {
			return false;
		}
	}
	return true;
}
