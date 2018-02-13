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

/*int16_t method_branches_borders::farthest(const std::set<int16_t>& s_admis, int16_t to_value) {
	int max_diff = 0;
	size_t size = s_admis.size();
	for (std::set<int16_t>::iterator iter = s_admis.begin(); iter != s_admis.end(); ++iter) {
		if (to_value - *iter > max_diff) max_diff = to_value - *iter;
		if (*iter - to_value > max_diff) max_diff = *iter - to_value;
	}
	return max_diff;
}*/

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

int16_t method_branches_borders::lower_bound(const std::vector<appointment>& _v_app) {
	std::set<int16_t> s_admis;
	admissible_set(_v_app, s_admis);
	std::vector<appointment> v_app(_v_app.begin(), _v_app.end());
	size_t size = v_app.size();
	size_t count = grh->get_count_vertex() - size;
	std::set<int16_t>::iterator iter = s_admis.begin();
	for (int i = 0; i < count; ++i) {
		v_app.push_back(appointment(i + size + 1, *(iter++)));
	}
	const std::vector<std::vector<edge>>& edges = grh->get_edges();
	edge temp_edge;
	int sum = 0;
	int temp = 0;
	for (int i = 0; i < edges.size(); ++i) {
		for (int j = 0; j < edges[i].size(); ++j) {
			temp_edge = edges[i][j];
			temp = v_app[temp_edge.first - 1].second - v_app[temp_edge.second - 1].second;
			if (temp < 0) temp = -temp;
			sum += temp;
		}
	}
	return sum;
}

int16_t method_branches_borders::upper_bound(const std::vector<appointment>& _v_app) {
	std::set<int16_t> s_admis;
	admissible_set(_v_app, s_admis);
	std::vector<appointment> v_app(_v_app.begin(), _v_app.end());
	int w_max = *(--s_admis.end());
	int w_min_ad = *(s_admis.begin());
	int w_min = v_app[0].second;
	int w_max_v = v_app[0].second;
	for (int i = 1; i < v_app.size(); ++i) {
		if (w_min > v_app[i].second) w_min = v_app[i].second;
		if (w_max_v < v_app[i].second) w_max_v = v_app[i].second;
	}
	if (w_max < w_min) {
		w_max = w_min_ad;
		w_min = w_max_v;
	}
	const std::vector<std::vector<edge>>& edges = grh->get_edges();
	edge temp_edge;
	int sum = 0;
	int temp = 0;
	for (int i = 0; i < edges.size(); ++i) {
		for (int j = 0; j < edges[i].size(); ++j) {
			temp_edge = edges[i][j];
			if ((temp_edge.first - 1 < v_app.size()) && (temp_edge.second - 1 < v_app.size())) {
				temp = v_app[temp_edge.first - 1].second - v_app[temp_edge.second - 1].second;
			}
			else {
				temp = w_max - w_min;
			}
			if (temp < 0) temp = -temp;
			sum += temp;
		}
	}
	return sum;
}


/*int16_t method_branches_borders::lower_bound(const std::vector<appointment>& v_app) {  
	size_t size;
	std::set<int16_t> s_admis;
	admissible_set(v_app, s_admis);
	std::vector<appointment> current_v_app(v_app.begin(), v_app.end());
	const std::vector<std::vector<edge>>& edges = grh->get_edges();
	appointment temp_app;
	for (int i = 0; i < current_v_app.size(); ++i) {
		size = edges[current_v_app[i].first - 1].size();
		for (int j = 0; j < size; ++j) {
			temp_app = edges[current_v_app[i].first - 1][j];
			if (std::find_if(current_v_app.begin(), current_v_app.end(),
				[&temp_app](appointment app) {return (app.first == temp_app.first) && (app.second == temp_app.second); }) \
				== current_v_app.end()) {
				current_v_app.push_back(appointment(current_v_app[i].first - 1, farthest(s_admis, current_v_app[i].second)));
			}
		}
	}
	if (current_v_app.size() != grh->get_count_vertex()) {
		for (int i = 0; i < current_v_app.size(); ++i) {
			if (std::find_if(current_v_app.begin(), current_v_app.end(),[&i](appointment app) {return app.first == i + 1;}) \
				== current_v_app.end()) {
				size = edges[i].size();
				for (int j = 0; j < size; ++j) {
					temp_app = edges[i][j];
					if (std::find_if(current_v_app.begin(), current_v_app.end(),
						[&temp_app](appointment app) {return (app.first == temp_app.first) && (app.second == temp_app.second); }) \
						== current_v_app.end()) {
						current_v_app.push_back(appointment(i + 1, farthest(s_admis, current_v_app[i].second)));
					}
				}
			}
		}
	}
	std::sort(current_v_app.begin(), current_v_app.end(),
		[](appointment first_app, appointment second_app) \
	{return first_app.first < second_app.first;});
	int sum = 0;
	int temp = 0;
	for (int i = 0; i < edges.size(); ++i) {
		for (int j = 0; j < edges[i].size(); ++j) {
			temp = current_v_app[edges[i][j].first - 1].second - current_v_app[edges[i][j].second - 1].second;
			if (temp < 0) temp = -temp;
			sum += temp;
		}
	}
	return sum;
}*/
