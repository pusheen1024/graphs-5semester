#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <fstream>
#include "graph.h"
#include "task3.cpp"
#include "task4.cpp"
#include "task5.cpp"
#include "task6.cpp"
#include "task7.cpp"
#include "task8.cpp"
#include "task9.cpp"
#include "task10.cpp"

#define pb push_back

using namespace std;

pair<Graph, bool> create_graph() {
	cout << "Каким образом Вы хотите создать граф?" << '\n';
	cout << "1) Создать пустой граф;" << '\n';
	cout << "2) Считать граф с консоли;" << '\n';
	cout << "3) Считать граф из файла;" << '\n';

	int choice;
	cin >> choice;
	Graph graph;
	if (choice == 1) {
		graph = Graph();
		return {graph, 1};
	}
	else if (choice == 2) {
		graph = Graph(cin, 1);
		return {graph, 1};
	}
	else if (choice == 3) {
		cout << "Введите имя файла: ";
		string filename;
		cin >> filename;
		graph = Graph(filename);
		return {graph, 1};
	}
	else {
		cout << "Некорректный выбор!" << '\n';
		return {graph, 0};
	}
}

int main() {
	Graph g;
	while (true) {
		auto [graph, ans] = create_graph();
		if (ans) {
			g = graph;
			break;
		}
	}
	cout << "Текущий вид графа:" << '\n';
	g.print_format(cout);
	while (true) {
		cout << "Что Вы хотите сделать?" << '\n';
		cout << "1) Добавить вершину;" << '\n';
		cout << "2) Удалить вершину;" << '\n';
		cout << "3) Добавить ребро;" << '\n';
		cout << "4) Удалить ребро;" << '\n';
		cout << "5) Пересоздать граф;" << '\n';
		cout << "// ЗАДАНИЯ" << '\n';
		cout << "6) (1a.14) Вывести все вершины графа, смежные с данной;" << '\n';
		cout << "7) (1a.8) Вывести те вершины, у которых полустепень исхода больше полустепени захода;" << '\n';
		cout << "8) (1б.16) Проверить, содержатся ли все вершины и все рёбра графа G1 в графе G2;" << '\n';
		cout << "9) (2.27) Найти длины кратчайших (по числу дуг) путей из вершины u во все остальные." << '\n';
		cout << "10) (2.11) Найти цикломатическое число графа — минимальное число рёбер, которые надо удалить, чтобы граф стал ациклическим." << '\n';
		cout << "11) (3.p) Построить каркас минимального веса с помощью алгоритма Прима." << '\n';
		cout << "12) (4.11) Найти центр графа." << '\n';
		cout << "13) (4.23) Вывести все отрицательные циклы." << '\n';
		cout << "14) (4.22) Найти k кратчайших путей между вершинами u и v." << '\n';
		cout << "15) Выйти из программы." << '\n';
		int choice;
		cin >> choice;
		if (choice == 1) {
			cout << "Введите номер добавляемой вершины: " << '\n';
			int v;
			cin >> v;
			if (g.add_vertex(v)) {
				cout << "Вершина успешно добавлена!" << '\n';
			}
			else {
				cout << "Такая вершина уже есть в графе." << '\n';
				continue;
			}
		}
		else if (choice == 2) {
			cout << "Введите номер удаляемой вершины: " << '\n';
			int v;
			cin >> v;
			if (g.remove_vertex(v)) {
				cout << "Вершина успешно удалена!" << '\n';
			}
			else {
				cout << "Такой вершины нет в графе." << '\n';
				continue;
			}
		}
		else if (choice == 3) {
			cout << "Введите ребро: ";
			Edge e = Edge(cin, g.weighted);
			if (g.add_edge(e)) {
				cout << "Ребро успешно добавлено!" << '\n';
			}
			else {
				cout << "Такое ребро уже есть в графе." << '\n';
				continue;
			}
		}
		else if (choice == 4) {
			cout << "Введите ребро: ";
			Edge e = Edge(cin, g.weighted);
			if (g.remove_edge(e)) {
				cout << "Ребро успешно удалено!" << '\n';
			}
			else {
				cout << "Такого ребра нет в графе." << '\n';
				continue;
			}
		}
		else if (choice == 5) {
			while (true) {
				auto [graph, ans] = create_graph();
				if (ans) {
					g = graph;
					break;
				}
			}
		}
		else if (choice == 6) {
			cout << "Введите номер вершины: ";
			int v;
			cin >> v;
			auto adj = g.get_adj(v);
			if (! adj.second) {
			   cout << "Такой вершины нет в графе." << '\n';
			   continue;
			}	   
			cout << "Смежные с вершиной " << v << " вершины: ";
			for (int u : adj.first) cout << u << ' ';
			cout << '\n';
			continue;
		}

		else if (choice == 7) {
			if (! g.oriented) cout << "Для неориентированных графов вопрос не имеет смысла." << '\n';
			else {
				auto res = get_vertices(g);
				for (int v : res) cout << v << ' ';
				cout << '\n';
			}
			continue;
		}
		else if (choice == 8) {
			cout << "Граф G1 - текущий граф. Введите граф G2" << '\n';
			Graph g2;
			while (true) {
				auto [graph, ans] = create_graph();
				if (ans) {
					g2 = graph;
					break;
				}
			}
			if (is_subset(g, g2)) cout << "Первый граф содержится во втором." << '\n';
			else cout << "Первый граф не содержится во втором." << '\n';
			continue;
		}
		else if (choice == 9) {
			cout << "Введите номер вершины: ";
			int v;
			cin >> v;
			auto dist = bfs(g, v);
			cout << "Кратчайшие расстояния до вершин:" << '\n';
			for (auto &[v, d] : dist) {
				cout << v << " - " << d << '\n';
			}
			continue;
		}
		else if (choice == 10) {
			if (g.oriented) cout << "Невозможно решить эту задачу для ориентированных графов." << '\n';
			else cout << "Цикломатическое число графа = " << cyclomatic_number(g) << '\n';
			continue;
		}
		else if (choice == 11) {
			if (g.oriented || ! g.weighted) cout << "Неподходящий тип графа." << '\n';
			else {
				auto ans = prim(g);
				cout << "Минимальное остовное дерево:" << '\n';
				ans.print_format(cout);
			}
			continue;			
		}
		else if (choice == 12) {
			if (g.oriented) cout << "Задачу можно решить только для неориентированных графов." << '\n';
			else {
				auto center = get_center(g);
				if (! center.empty()) {
					cout << "Вершины, вошедшие в центр: ";
					for (int v : center) cout << v << ' ';
					cout << '\n';
				}
			}
			continue;
		}
		else if (choice == 13) {
			if (g.oriented || ! g.weighted) cout << "Неподходящий тип графа." << '\n';
			else auto cycles = negative_cycles(g);
			continue;
		}
		else if (choice == 14) {
			int v, u, k;
			cout << "Введите вершины u и v: ";
			cin >> v >> u;
			cout << "Введите число k: " << '\n';
			k_shortest_paths(g, v, u, k);
			continue;
		}
		else if (choice == 15) break;
		else {
			cout << "Некорректный выбор!" << '\n';
			continue;
		}
		cout << "Текущий вид графа:" << '\n';
		g.print_format(cout); 
	}
}
