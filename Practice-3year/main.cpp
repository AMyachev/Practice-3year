#include "graph.h"
#include <chrono>
#include <fstream>

using std::ifstream;


int main() {
	auto start_time = std::chrono::steady_clock::now();
	ifstream fin("D:\\practice.txt");
	istream_iterator<int16_t> iter(fin);
	graph grh(read_edges(iter));
	characteristics v_chr(iter);
	if (verify_input_data(grh, v_chr) == false)
		cout << "input data do not satisfy the restriction of injection" << std::endl;
	grh.print();
	for (register int i = 0; i < v_chr.size(); ++i)
		cout << v_chr[i] << " ";
	cout << std::endl;
	method_branches_borders alg(&grh, &v_chr);
	pair<node_decisions_tree, int>* result = alg.process();
	alg.complete_best_solution(result->first.v_app);
	cout << result->second << std::endl;
	for (int i = 0; i < result->first.v_app.size(); ++i) {
		cout << result->first.v_app[i] << "  " << result->first.v_app[i]  << std::endl;
	}


	auto end_time = std::chrono::steady_clock::now();
	auto elapsed_ns = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
	cout << elapsed_ns.count() << " ms\n";
	delete result;
	system("pause");
	return 0;
}