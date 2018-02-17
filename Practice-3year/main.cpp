#include "graph.h"
#include <chrono>
#include <fstream>
#include <string>

using std::ifstream;
using std::string;
using std::cin;


int main() {
	format_input_data();
	string continue_work;
	string name_file;
	do {
		cout << "enter the full file name" << endl;
		cin >> name_file;
		auto start_time = std::chrono::steady_clock::now();
		ifstream fin(name_file);
		if (fin.is_open()) {
			istream_iterator<int16_t> iter(fin);
			graph grh(read_edges(iter));
			characteristics v_chr(iter);
			bubble_sort(v_chr);
			if (verify_input_data(grh, v_chr) == false)
				cout << "input data do not satisfy the restriction of injection" << endl;
			grh.print();
			v_chr.print();

			method_branches_borders alg(&grh, &v_chr);
			pair<node_decisions_tree, int>* result = alg.process();
			alg.complete_best_solution(result->first.v_app);
			cout << "criterion value:  " << result->second << endl;

			cout << "--------------decision----------------" << endl;
			for (int i = 0; i < result->first.v_app.size(); ++i) {
				cout << (i + 1) << "  " << result->first.v_app[i] << endl;
			}
			cout << "--------------decision----------------" << endl;

			auto end_time = std::chrono::steady_clock::now();
			auto elapsed_ns = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
			cout << "time working:  " << elapsed_ns.count() << " ms\n";
			delete result;
		}
		else {
			cout << "file with this name does not exist" << endl;
		}
		cout << "continue work? (y or n): " << endl;
		cin >> continue_work;
	} while (continue_work == "y");
	return 0;
}