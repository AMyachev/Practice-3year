#include "graph.h"

graph::graph(std::istream_iterator<int16_t>& iter) {
	read_edges(iter);
}

void graph::add(edge _edge) {
	if (edges.size() < _edge.first) {
		for (int i = 0; i < _edge.first - edges.size(); ++i) {
			edges.push_back(std::vector<edge>());
		}
	}
	edges[_edge.first - 1].push_back(_edge);
}

void graph::print() {
	for (int i = 0; i < edges.size(); ++i) {
		for (int j = 0; j < edges[i].size(); ++j) {
			std::cout << edges[i][j].first << "  " << edges[i][j].second << std::endl;
		}
	}
}

void graph::read_edges(std::istream_iterator<int16_t>& iter) {
	int count_edges = *(iter++);
	for (int i = 0; i < count_edges; ++i) {
		edge grh_edge;
		grh_edge.first = *(iter++);
		grh_edge.second = *(iter++);
		add(grh_edge);
	}
	count_vertex = edges.size();
}

int16_t graph::get_count_vertex() const {
	return count_vertex;
}

const std::vector<std::vector<edge>>& graph::get_edges() const
{
	return edges;
}

/*false - incorrect; true - correct data*/
bool verify_input_data(graph grh, characteristics v_chr) {
	return grh.get_count_vertex() <= v_chr.size();
}

node_decisions_tree::node_decisions_tree(std::vector<appointment> _v_app): v_app(_v_app.begin(), _v_app.end()) {}

void method_branches_borders::admissible_set(const std::vector<appointment>& v_app, std::set<int16_t>& s_admis)
{
	s_admis.insert(v_chr->begin(), v_chr->end());
	for (int i = 0; i < v_app.size(); ++i) {
		s_admis.erase(s_admis.find(v_app[i].second));
	}
}

void method_branches_borders::branching(node_decisions_tree * node, int16_t id_vertex) {
	std::set<int16_t> s_admis; 
    admissible_set(node->v_app, s_admis);
	for (int16_t i = 0; i < s_admis.size(); ++i) {
		node->v_pnode.push_back(new node_decisions_tree(node->v_app));
		node->v_pnode[i]->v_app.push_back(appointment(id_vertex, (*v_chr)[i]));
	}
}

method_branches_borders::method_branches_borders(graph * _grh, characteristics * _v_chr) {
	grh = _grh;
	v_chr = _v_chr;
	root = new node_decisions_tree();
}

std::vector<appointment>* method_branches_borders::process()
{
	branching(root, 1);

	return nullptr;
}

int16_t method_branches_borders::lower_bound(const std::vector<appointment>& v_app) {
	std::set<int16_t> s_admis;
	admissible_set(v_app, s_admis);
	const std::vector<std::vector<edge>>& edges = grh->get_edges();
	for (int i = 0; i < v_app.size(); ++i) {
		for (int j = 0; j < edges[i].size(); ++j) {

		}
	}
	return int16_t();
}
int16_t method_branches_borders::upper_bound(const std::vector<appointment>& v_app) {
	return int16_t();
}