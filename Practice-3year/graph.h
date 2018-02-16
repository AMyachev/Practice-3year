#pragma once
#include <iterator>
#include <iostream>
#include <stdint.h>
#include <algorithm>
#include <vector>
#include <deque>

using std::istream_iterator;
using std::pair;
using std::cout;
using std::vector;
using std::deque;

typedef pair<int16_t, int16_t> edge;

class graph {
	int16_t count_vertex;
	int16_t copy_counter;
	vector<vector<edge>>* edges;
public:
	graph(vector<vector<edge>>* _edges) :edges(_edges), count_vertex(_edges->size()),
		copy_counter(1) {};
	graph(const graph& grh);
	int16_t get_count_vertex() const { return count_vertex; };
	const vector<vector<edge>>* get_edges() const { return edges; };
	void print();
	~graph();
};

class characteristics : public std::vector<int16_t> {
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
	node_decisions_tree(vector<int16_t> _v_app) : v_app(_v_app.begin(), _v_app.end()) {};
};

class deque_pnode : public deque<node_decisions_tree*> {
public:
	~deque_pnode() {
		for (deque<node_decisions_tree*>::iterator iter = this->begin(); iter != this->end(); ++iter)
			delete *iter;
	}
};

class method_branches_borders {
	graph* grh;
	characteristics* v_chr;
	size_t size_chr;
	size_t size_edges;
	size_t* hash_sizes;
public:
	method_branches_borders(graph* _grh, characteristics* _v_chr) : grh(_grh), v_chr(_v_chr),
		size_chr(v_chr->size()), size_edges(_grh->get_count_vertex()) {
		size_t count = _grh->get_count_vertex();
		hash_sizes = new size_t[count];
		const vector<vector<edge>>* edges = grh->get_edges();
		for (register int i = 0; i < count; ++i)
			*(hash_sizes + i) = (*edges)[i].size();
	};
	pair<node_decisions_tree, int>*  process();
	void complete_best_solution(vector<int16_t>& v_app);
	int16_t lower_bound(const vector<int16_t>& _v_app);
	int16_t upper_bound(const vector<int16_t>& _v_app);
	bool find(const vector<int16_t>& v_app, int16_t check_chr);
	~method_branches_borders() {
		delete[] hash_sizes;
	}
};

bool verify_input_data(graph grh, characteristics v_chr);

vector<vector<edge>>* read_edges(istream_iterator<int16_t>& iter);


