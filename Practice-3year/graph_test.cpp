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

bool test_lower_bound() {
	bool check_test = true;
	vector<vector<edge>>* edges = new vector<vector<edge>>();
	edges->push_back(vector<edge>()); edges->push_back(vector<edge>());
	edges->push_back(vector<edge>()); edges->push_back(vector<edge>());
	(*edges)[0].push_back(edge(1, 2));
	(*edges)[1].push_back(edge(2, 3));
	(*edges)[2].push_back(edge(3, 4));
	(*edges)[3].push_back(edge(4, 2));
	graph grh(edges);
	characteristics chr;
	chr.push_back(1); chr.push_back(2); chr.push_back(4); chr.push_back(7);
	method_branches_borders mbb(&grh, &chr);
	vector<int16_t> v_app;
	v_app.push_back(1); v_app.push_back(2); v_app.push_back(4); v_app.push_back(7);
	if (mbb.lower_bound(v_app) != 11) check_test = false;
	vector<int16_t> v_app1;
	v_app1.push_back(4); v_app1.push_back(7); v_app1.push_back(1); v_app1.push_back(2);
	if (mbb.lower_bound(v_app1) != 15) check_test = false;
	vector<int16_t> v_app2;
	v_app2.push_back(4); v_app2.push_back(2);
	if (mbb.lower_bound(v_app2) != 14) check_test = false;
	return check_test;
}

bool test_upper_bound() {
	bool check_test = true;
	vector<vector<edge>>* edges = new vector<vector<edge>>();
	edges->push_back(vector<edge>()); edges->push_back(vector<edge>());
	edges->push_back(vector<edge>()); edges->push_back(vector<edge>());
	(*edges)[0].push_back(edge(1, 2));
	(*edges)[1].push_back(edge(2, 3));
	(*edges)[2].push_back(edge(3, 4));
	(*edges)[3].push_back(edge(4, 2));
	graph grh(edges);
	characteristics chr;
	chr.push_back(1); chr.push_back(2); chr.push_back(4); chr.push_back(7);
	method_branches_borders mbb(&grh, &chr);
	vector<int16_t> v_app;
	v_app.push_back(1);
	if (mbb.upper_bound(v_app) != 21) check_test = false;
	v_app.push_back(4);
	if (mbb.upper_bound(v_app) != 14) check_test = false;
	return check_test;
}

bool test_process() {
	bool check_test = true;
	vector<vector<edge>>* edges = new vector<vector<edge>>();
	edges->push_back(vector<edge>()); edges->push_back(vector<edge>());
	edges->push_back(vector<edge>()); edges->push_back(vector<edge>());
	(*edges)[0].push_back(edge(1, 2));
	(*edges)[1].push_back(edge(2, 3));
	(*edges)[2].push_back(edge(3, 4));
	(*edges)[3].push_back(edge(4, 2));
	graph grh(edges);
	characteristics chr;
	chr.push_back(1); chr.push_back(2); chr.push_back(4); chr.push_back(7);
	method_branches_borders mbb(&grh, &chr);
	pair<node_decisions_tree, int>* decision = mbb.process();
	if (decision->second != 17) check_test = false;
	if (decision->first.v_app[0] != 2) check_test = false;
	if (decision->first.v_app[1] != 7) check_test = false;
	if (decision->first.v_app[2] != 4) check_test = false;
	if (decision->first.v_app[3] != 1) check_test = false;
	return true;
}