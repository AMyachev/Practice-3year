#include "graph.h"
#include <chrono>
#include <fstream>
#include <string>

using std::ifstream;


int main() {
	std::string name_file;
	std::cin >> name_file;
	auto start_time = std::chrono::steady_clock::now();
	ifstream fin(name_file);
	istream_iterator<int16_t> iter(fin);
	graph grh(read_edges(iter));
	characteristics v_chr(iter);
	bubble_sort(v_chr);
	if (verify_input_data(grh, v_chr) == false)
		cout << "input data do not satisfy the restriction of injection" << std::endl;
	grh.print();
	v_chr.print();

	method_branches_borders alg(&grh, &v_chr);
	pair<node_decisions_tree, int>* result = alg.process();
	alg.complete_best_solution(result->first.v_app);
	cout << "criterion value:  " << result->second << std::endl;

	cout << "--------------decision----------------" << std::endl;
	for (int i = 0; i < result->first.v_app.size(); ++i) {
		cout << (i + 1) << "  " << result->first.v_app[i]  << std::endl;
	}
	cout << "--------------decision----------------" << std::endl;

	auto end_time = std::chrono::steady_clock::now();
	auto elapsed_ns = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
	cout << "time working:  " << elapsed_ns.count() << " ms\n";
	delete result;
	system("pause");
	return 0;
}