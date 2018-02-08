#pragma once
#include <iterator>
#include <iostream>
#include <stdint.h>
#include <utility>
#include <vector>

typedef std::pair<int16_t, int16_t> edge;
typedef std::pair<int16_t, int16_t> appointment;

class graph {
	int16_t count_vertex;
	std::vector<std::vector<edge>> edges;
public:
	void add(edge _edge);
	void print();
	void read_edges(std::istream_iterator<int16_t>& iter, int16_t );
	int16_t get_count_vertex() const;
};

class node_decisions_tree {
	std::vector<appointment> v_app;
	std::vector<node_decisions_tree*> v_pnode;
};

class bad_input {};
