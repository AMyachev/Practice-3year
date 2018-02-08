#include "graph.h"

#include <fstream>

/*numbering of vertices from the number one*/

int main() {
	std::ifstream fin("D:\\practice.txt");
	std::istream_iterator<int16_t> iter(fin);
	try {
		int count_edges = 0;
		count_edges = *(iter++);
		graph grh;
		grh.read_edges(iter, count_edges);              // graph ready
		int count_weight = 0;
		count_weight = *(iter++);
		if (count_weight < grh.get_count_vertex()) throw bad_input();
		std::vector<int16_t> v_wght;
		for (int i = 0; i < count_weight; ++i)
			v_wght.push_back(*(iter++));
		grh.print();
		for (int i = 0; i < v_wght.size(); ++i)
			std::cout << v_wght[i] << " ";
		std::cout << std::endl;
	}
	catch (bad_input) {
		std::cout << "input data do not satisfy the restriction of injection" << std::endl;
	}
	system("pause");
	return 0;
}