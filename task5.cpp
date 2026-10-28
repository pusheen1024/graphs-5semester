#include <queue>

map<int, int> bfs(Graph &gr, int st) {
	map<int, int> d;
	d[st] = 0;
	queue<int> q;
	q.push(st);
	while (! q.empty()) {
		int v = q.front();
		q.pop();
		for (auto e : gr.g[v]) {
			int u = e.other_end(v);
			if (! d.count(u)) {
				d[u] = d[v] + 1;
				q.push(u);
			}
		}
	}
	for (auto &[v, adj] : gr.g) {
		if (! d.count(v)) {
			d[v] = -1;
		}
	}
	return d;
}
