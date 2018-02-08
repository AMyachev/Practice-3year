#include "graph.h"

#include <fstream>

/*нумерация вершин с 1*/

int main() {
	std::ifstream fin("D:\\practice.txt");
	std::istream_iterator<int16_t> iter(fin);
	int count_edges = 0;
	count_edges = *(iter++);
	graph grh(count_edges);
	for (int i = 0; i < count_edges; ++i) {
		edge grh_edge;
		grh_edge.first = *(iter++);
		grh_edge.second = *(iter++);
		grh.add(grh_edge);
	}
	grh.print();
	system("pause");
	return 0;
}