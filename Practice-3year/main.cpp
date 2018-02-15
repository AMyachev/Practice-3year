#include "graph.h"
#include <chrono>

#include <fstream>
using std::cout;
/*numbering of vertices from the number one*/

int main() {
	auto start_time = std::chrono::steady_clock::now();
	std::ifstream fin("D:\\practice.txt");
	std::istream_iterator<int16_t> iter(fin);
	graph grh(read_edges(iter));
	characteristics v_chr(iter);
	if (verify_input_data(grh, v_chr) == false)
		std::cout << "input data do not satisfy the restriction of injection" << std::endl;
	grh.print();
	for (register int i = 0; i < v_chr.size(); ++i)
		std::cout << v_chr[i] << " ";
	std::cout << std::endl;
	method_branches_borders alg(&grh, &v_chr);
	std::pair<node_decisions_tree, int>* result = alg.process();
	alg.complete_best_solution(result->first.v_app);
	std::cout << result->second << std::endl;
	for (int i = 0; i < result->first.v_app.size(); ++i) {
		std::cout << result->first.v_app[i] << "  " << result->first.v_app[i]  << std:: endl;
	}


	auto end_time = std::chrono::steady_clock::now();
	auto elapsed_ns = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
	std::cout << elapsed_ns.count() << " ns\n";
	delete result;
	system("pause");
	return 0;
}