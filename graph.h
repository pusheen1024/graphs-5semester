#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <fstream>

#define pb push_back

using namespace std;

class Edge { // класс ребра
	public:

	int v, u;
	int w;

	Edge() {}
	Edge(int v, int u) {
		this->v = v;
		this->u = u;
	}

	Edge(int v, int u, int w) {
		this->v = v;
		this->u = u;
		this->w = w;
	}

	Edge(istream &in, bool weighted) {
		if (weighted) in >> v >> u >> w;
		else in >> v >> u;
	}

	int other_end(int v) {
		return v ^ this->v ^ this->u;
	}

	Edge get_symmetry() {
		return Edge(this->u, this->v, this->w);
	}
	
	void print_edge(ostream &out, bool weighted) {
		out << this->v << ' ' << this->u;
		if (weighted) out << ' ' << this->w << '\n';
	}
};

bool operator ==(const Edge &a, const Edge &b) {
	return (a.v == b.v && a.u == b.u);
}

bool operator <(const Edge &a, const Edge &b) {
	return (a.v < b.v || a.v == b.v && a.u < b.u);
}

class Graph { // класс графа
	public:

	map<int, set<Edge>> g; // граф
	map<int, set<Edge>> tg; // транспонированный граф
	set<Edge> edges; // список рёбер
	bool oriented; // является ли граф ориентированным
	bool weighted; // является ли граф взвешенным
	int n, m;

	Graph() { // пустой конструктор
		g = {};
		tg = {};
		edges = {};
		oriented = 0;
		weighted = 0;
		n = 0;
		m = 0;
	}

	Graph(istream &in, bool format) { // конструктор чтения графа из потока
		if (format) cout << "Введите количество вершин в графе: ";
		in >> n;
		if (format) cout << "Введите количество рёбер в графе: ";
		in >> m;
		if (format) cout << "Является ли граф ориентированным? 0 - нет, 1 - да." << '\n';
		in >> oriented;
		if (format) cout <<	"Является ли граф взвешенным? 0 - нет, 1 - да." << '\n';
		in >> weighted;
		if (format) cout << "Введите список рёбер в формате v u" << (weighted ? " w" : "") << ":" << '\n';
		for (int i = 0; i < m; i++) {	
			Edge e = Edge(in, weighted);
			g[e.v].insert(e);
			tg[e.u].insert(e);
			if (! g.count(e.u)) g[e.u] = {};
			if (! oriented) {
				Edge es = e.get_symmetry();
				g[e.u].insert(es);
				tg[e.v].insert(es);
			}
			edges.insert(e);
		}
	}

	Graph(string filename) { // конструктор чтения графа из файла
		ifstream in(filename);
		*this = Graph(in, 0);
	}

	Graph(const Graph& graph) { // конструктор копирования
		this->g = graph.g;
		this->tg = graph.tg;
		this->edges = graph.edges;
		this->oriented = graph.oriented;
		this->weighted = graph.weighted;
		this->n = graph.n;
		this->m = graph.m;
	}
	
	void print_edges(ostream &out) { // вывод графа в поток в формате, пригодном для чтения конструктором
		out << n << ' ' << m << '\n';
		out << oriented << ' ' << weighted << '\n';
		for (auto e : edges) {
			e.print_edge(out, weighted);
		}
	}

	void print_format(ostream &out) { // вывод графа в поток в человеко-читаемом формате
		out << "В графе " << n << " вершин и " << m << " рёбер." << '\n';
		out << "Граф " << (oriented ? "" : "не") << "ориентированный и " << (weighted ? "" : "не") << "взвешенный." << '\n';
		out << "Списки смежности вершин:" << '\n';
		for (auto &[v, adj] : g) {
			out << v << ": ";
			for (auto e : adj) {
				if (weighted)
					out << "(" << e.other_end(v) << ", " << e.w << ") ";
				else out << e.other_end(v) << ' ';
			}
			out << '\n';
		}
	}
	
	bool add_vertex(int v) { // добавление вершины
		if (g.count(v)) return false;
		n++;
		g[v] = {};
		return true;
	}

	bool add_edge(Edge e) { // добавление ребра
		if (edges.count(e)) return false;
		m++;
		g[e.v].insert(e);
		tg[e.u].insert(e);
		if (! oriented) {
			g[e.u].insert(e.get_symmetry());
			tg[e.v].insert(e.get_symmetry());
		}
		edges.insert(e);
		return true;
	}

	bool remove_vertex(int v) { // удаление вершины
		if (! g.count(v)) return false;
		n--;
		g.erase(v);
		for (auto e : tg[v]) {
			g[e.other_end(v)].erase(e);
			edges.erase(e);
		}
		tg.erase(v);
		return true;
	}

	bool remove_edge(Edge e) { // удаление ребра
		if (! edges.count(e)) return false;
		m--;
		g[e.v].erase(e);
		tg[e.u].erase(e);
		if (! oriented) {
			g[e.u].erase(e.get_symmetry());
			tg[e.v].erase(e.get_symmetry());
		}
		edges.erase(e);
		return true;
	}

	// task2-14
	pair<vector<int>, bool> get_adj(int v) { // получение списка смежности
		vector<int> adj;
		if (! g.count(v)) return {adj, 0};
		for (auto e : g[v]) {
			adj.pb(e.other_end(v));
		}
		return {adj, 1};
	}
};
