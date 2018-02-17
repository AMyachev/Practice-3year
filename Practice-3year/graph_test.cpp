#include "graph_test.h"

bool test_verify_input_data() {
	bool check_test = true;
	vector<vector<edge>>* edges = new vector<vector<edge>>();
	edges->push_back(vector<edge>());
	edges->push_back(vector<edge>());
	(*edges)[0].push_back(edge(1, 2));
	(*edges)[1].push_back(edge(2, 1));
	graph grh(edges);
	characteristics chr;
	chr.push_back(1); chr.push_back(2); chr.push_back(4); chr.push_back(7);
	if (verify_input_data(grh, chr) != true) check_test = false;
	(*edges)[0].push_back(edge(1, 2));
	if (verify_input_data(grh, chr) != false) check_test = false;
	(*edges)[0].pop_back();
	chr.push_back(4);
	if (verify_input_data(grh, chr) != false) check_test = false;
	chr.pop_back();

	vector<vector<edge>>* edges1 = new vector<vector<edge>>();
	edges1->push_back(vector<edge>());
	edges1->push_back(vector<edge>());
	edges1->push_back(vector<edge>());
	edges1->push_back(vector<edge>());
	edges1->push_back(vector<edge>());
	(*edges1)[1].push_back(edge(2, 1));
	(*edges1)[2].push_back(edge(3, 1));
	(*edges1)[3].push_back(edge(4, 1));
	(*edges1)[4].push_back(edge(5, 1));
	graph grh1(edges1);
	if (verify_input_data(grh1, chr) != false) check_test = false;
	return check_test;
}