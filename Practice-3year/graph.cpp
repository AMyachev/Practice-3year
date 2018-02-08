#include "graph.h"

void graph::add(edge _edge) {
	if (edges.size() < _edge.first) {
		for (int i = 0; i < _edge.first - edges.size(); ++i) {
			edges.push_back(std::vector<edge>());
		}
	}
	edges[_edge.first - 1].push_back(_edge);
}

void graph::print() {
	for (int i = 0; i < edges.size(); ++i) {
		for (int j = 0; j < edges[i].size(); ++j) {
			std::cout << edges[i][j].first << "  " << edges[i][j].second << std::endl;
		}
	}
}

void graph::read_edges(std::istream_iterator<int16_t>& iter, int16_t count_edges) {
	for (int i = 0; i < count_edges; ++i) {
		edge grh_edge;
		grh_edge.first = *(iter++);
		grh_edge.second = *(iter++);
		add(grh_edge);
	}
	count_vertex = edges.size();
}

int16_t graph::get_count_vertex() const {
	return count_vertex;
}
