#include "graph.h"


/****************************graph*********************************************/
graph::graph(vector<vector<edge>>* _edges):edges(_edges), count_vertex(_edges->size()), copy_counter(1){}

graph::graph(const graph & grh)
{
	this->copy_counter = grh.copy_counter;
	this->count_vertex = grh.count_vertex;
	this->edges = grh.edges;
	++copy_counter;
}

void graph::print() {
	for (int i = 0; i < edges->size(); ++i) {
		for (int j = 0; j < (*edges)[i].size(); ++j) {
			std::cout << (*edges)[i][j].first << "  " << (*edges)[i][j].second << std::endl;
		}
	}
}

graph::~graph() {
	--copy_counter;
	if (copy_counter == 0) delete edges;
}


/****************************auxiliary*****************************************/
bool verify_input_data(graph grh, characteristics v_chr) {
	return grh.get_count_vertex() <= v_chr.size();
}

vector<vector<edge>>* read_edges(std::istream_iterator<int16_t>& iter) {
	edge _edge;
	vector<vector<edge>>* edges = new vector<vector<edge>>();
	int count_edges = *(iter++);
	for (int i = 0; i < count_edges; ++i) {
		_edge.first = *(iter++);
		_edge.second = *(iter++);

		if ((edges->size() < _edge.first) || (edges->size() < _edge.second)) {
			size_t size = edges->size();
			int count_new_vertex = (_edge.first > _edge.second) ? (_edge.first - size) :
				(_edge.second - size);
			for (int i = 0; i < count_new_vertex; ++i) {
				edges->push_back(std::vector<edge>());
			}
		}
		(*edges)[_edge.first - 1].push_back(_edge);
	}
	return edges;
}

int abs(int val) {
	return (val < 0) ? -val : val;
}


/****************************method_branches_borders***************************/

void method_branches_borders::admissible_set(const vector<int16_t>& v_app, std::set<int16_t>& s_admis)
{
	s_admis.insert(v_chr->begin(), v_chr->end());
	for (int i = 0; i < v_app.size(); ++i) {
		s_admis.erase(s_admis.find(v_app[i]));
	}
}

std::pair<node_decisions_tree*, int>* method_branches_borders::process()
{
	size_t size = 0;
	node_decisions_tree* temp_node = nullptr;
	std::deque<node_decisions_tree*> algorithm_path;
	node_decisions_tree* best_node = new node_decisions_tree();
	int best_lower_bound = lower_bound(best_node->v_app);
	int current_upper_bound = 0;
	int current_lower_bound = 0;
	algorithm_path.push_back(best_node);
	for (int i = 0; i < algorithm_path.size(); ++i) {
		current_upper_bound = upper_bound(algorithm_path[i]->v_app);
		current_lower_bound = lower_bound(algorithm_path[i]->v_app);
		std::set<int16_t> s_admis;
		admissible_set(algorithm_path[i]->v_app, s_admis);
		size = s_admis.size();
		std::set<int16_t>::iterator iter = s_admis.begin();
		if (current_upper_bound < best_lower_bound) continue;
		if (current_lower_bound >= best_lower_bound) {
			best_lower_bound = current_lower_bound;
			if (current_lower_bound == current_upper_bound) {
				best_node = algorithm_path[i];
				continue;
			}
		}
		if (size != 0) {
			for (int j = 0; j < size; ++j) {
				temp_node = new node_decisions_tree(algorithm_path[i]->v_app);
				temp_node->v_app.push_back(*(iter++));
				algorithm_path.push_back(temp_node);
			}
		}
	}

	return new std::pair<node_decisions_tree*, int>(best_node, best_lower_bound);
}

int16_t method_branches_borders::lower_bound(const vector<int16_t>& _v_app) {
	std::set<int16_t> s_admis;
	admissible_set(_v_app, s_admis);
	std::vector<int16_t> v_app(_v_app.begin(), _v_app.end());
	size_t size = v_app.size();
	size_t count = grh->get_count_vertex() - size;
	std::set<int16_t>::iterator iter = s_admis.begin();
	for (int i = 0; i < count; ++i) {
		v_app.push_back(*(iter++));
	}
	const std::vector<std::vector<edge>>* edges = grh->get_edges();
	edge temp_edge;
	int sum = 0;
	int temp = 0;
	for (int i = 0; i < (*edges).size(); ++i) {
		for (int j = 0; j < (*edges)[i].size(); ++j) {
			temp_edge = (*edges)[i][j];
			temp = v_app[temp_edge.first - 1] - v_app[temp_edge.second - 1];
			if (temp < 0) temp = -temp;
			sum += temp;
		}
	}
	return sum;
}

int16_t method_branches_borders::upper_bound(const vector<int16_t>& _v_app) {
	std::set<int16_t> s_admis;
	admissible_set(_v_app, s_admis);
	std::vector<int16_t> v_app(_v_app.begin(), _v_app.end());
	int size = v_app.size();
	int w_max_ad = *(--s_admis.end());
	int w_min_ad = *(s_admis.begin());
	const std::vector<std::vector<edge>>* edges = grh->get_edges();
	edge temp_edge;
	int sum = 0;
	int temp = 0;
	for (int i = 0; i < (*edges).size(); ++i) {
		for (int j = 0; j < (*edges)[i].size(); ++j) {
			temp_edge = (*edges)[i][j];
			bool check1 = temp_edge.first - 1 < size;
			bool check2 = temp_edge.second - 1 < size;
			if (check1 && check2) {
				temp = v_app[temp_edge.first - 1] - v_app[temp_edge.second - 1];
			}
			else if (check1) {
				temp = v_app[temp_edge.first - 1] -
					((abs(v_app[temp_edge.first - 1] - w_max_ad) > abs(v_app[temp_edge.first - 1] - w_min_ad)) ?
						w_max_ad : w_min_ad);
			}
			else if (check2) {
				temp = v_app[temp_edge.second - 1] -
					((abs(v_app[temp_edge.second - 1] - w_max_ad) > abs(v_app[temp_edge.second - 1] - w_min_ad)) ?
						w_max_ad : w_min_ad);
			}
			else {
				temp = w_max_ad - w_min_ad;
			}
			sum += abs(temp);
		}
	}
	return sum;
}

/*int16_t method_branches_borders::passage_in_depth()
{
	std::set<int16_t> s_admis;
	std::vector<appointment> v_app;
	admissible_set(v_app, s_admis);


}*/

void method_branches_borders::complete_best_solution(vector<int16_t>& v_app)
{
		std::set<int16_t> s_admis;
		admissible_set(v_app, s_admis);
		size_t size = v_app.size();
		size_t count = grh->get_count_vertex() - size;
		std::set<int16_t>::iterator iter = s_admis.begin();
		for (int i = 0; i < count; ++i) {
			v_app.push_back(*(iter++));
		}
}
