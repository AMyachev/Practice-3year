#pragma once
#include <iterator>
#include <iostream>
#include <stdint.h>
#include <algorithm>
#include <utility>
#include <vector>
#include <set>
#include <deque>

using std::vector;
typedef std::pair<int16_t, int16_t> edge;

class graph {
	int16_t count_vertex;
	int16_t copy_counter;
	vector<vector<edge>>* edges;
public:
	graph(vector<vector<edge>>* _edges);
	graph(const graph& grh);
	int16_t get_count_vertex() const { return count_vertex; };
	const vector<vector<edge>>* get_edges() const { return edges; };
	void print();
	~graph();
};

class characteristics : public std::vector<int16_t> {   //TODO возможно не стоит вводить определение нового класса
public:
	characteristics(std::istream_iterator<int16_t>& iter) {
		int count_weight = *(iter++);
		for (int i = 0; i < count_weight; ++i)
			this->push_back(*(iter++));
	}
};

struct node_decisions_tree {
	std::vector<int16_t> v_app;
	node_decisions_tree() {}
	node_decisions_tree(std::vector<int16_t> _v_app) : v_app(_v_app.begin(), _v_app.end()) {};
};


class deque : public std::deque<node_decisions_tree*> {
public:
	~deque() {
		for (std::deque<node_decisions_tree*>::iterator iter = this->begin(); iter != this->end(); ++iter)
			delete *iter;
	}
};

/*false - incorrect; true - correct data*/
bool verify_input_data(graph grh, characteristics v_chr);

vector<vector<edge>>* read_edges(std::istream_iterator<int16_t>& iter);


class method_branches_borders {
	graph* grh;
	characteristics* v_chr;
	void admissible_set(const vector<int16_t>& v_app, std::set<int16_t>& s_admis);
public:
	method_branches_borders(graph* _grh, characteristics* _v_chr) : grh(_grh), v_chr(_v_chr){};
	std::pair<node_decisions_tree, int>*  process();
	void complete_best_solution(vector<int16_t>& v_app);
	int16_t lower_bound(const vector<int16_t>& _v_app);
	int16_t upper_bound(const vector<int16_t>& _v_app);
};

class bad_input {};
