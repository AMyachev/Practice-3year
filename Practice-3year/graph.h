#pragma once
#include <iterator>
#include <iostream>
#include <stdint.h>
#include <utility>
#include <vector>

typedef std::pair<int16_t, int16_t> edge;

class graph {
	int16_t count_vertex;
	std::vector<std::vector<edge>> edges;
public:
	graph(int16_t _count_vertex);
	void add(edge _edge);
	void print();
};