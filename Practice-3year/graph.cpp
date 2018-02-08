#include "graph.h"

graph::graph(int16_t _count_vertex): edges(_count_vertex) {
	count_vertex = _count_vertex;
}

void graph::add(edge _edge) {
	edges[_edge.first - 1].push_back(_edge);
}

void graph::print() {
	for (int i = 0; i < edges.size(); ++i) {
		for (int j = 0; j < edges[i].size(); ++j) {
			std::cout << edges[i][j].first << "  " << edges[i][j].second << std::endl;
		}
	}
}
