#pragma once
#include <iterator>
#include <iostream>
#include <stdint.h>
#include <algorithm>
#include <utility>
#include <vector>
#include <set>

typedef std::pair<int16_t, int16_t> edge;
typedef std::pair<int16_t, int16_t> appointment;

class graph {
	int16_t count_vertex;
	std::vector<std::vector<edge>> edges;
public:
	graph(std::istream_iterator<int16_t>& iter);
	void add(edge _edge);
	void print();
	void read_edges(std::istream_iterator<int16_t>& iter);
	int16_t get_count_vertex() const;
	const std::vector<std::vector<edge>>& get_edges() const;
};

class characteristics : public std::vector<int16_t> {
public:
	characteristics(std::istream_iterator<int16_t>& iter) {
		int count_weight = *(iter++);
		for (int i = 0; i < count_weight; ++i)
			this->push_back(*(iter++));
	}
};

bool verify_input_data(graph grh, characteristics v_chr);

struct node_decisions_tree {
	node_decisions_tree() {}
	node_decisions_tree(std::vector<appointment> _v_app);
	std::vector<appointment> v_app;
	std::vector<node_decisions_tree*> v_pnode;
};

class method_branches_borders {
	graph* grh;
	characteristics* v_chr;
	node_decisions_tree* root;
	void branching(node_decisions_tree* node, int16_t ind_vertex);
	int16_t farthest(const std::set<int16_t>&, int16_t to_value);
	void admissible_set(const std::vector<appointment>& v_app, std::set<int16_t>& s_admis);
public:
	method_branches_borders(graph* _grh, characteristics* _v_chr);
	std::vector<appointment>* process();
	int16_t lower_bound(const std::vector<appointment>& v_app);
	int16_t upper_bound(const std::vector<appointment>& v_app);
};

class bad_input {};