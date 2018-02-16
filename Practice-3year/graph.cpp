#include "graph.h"


/****************************graph*********************************************/

graph::graph(const graph & grh)
{
	this->copy_counter = grh.copy_counter;
	this->count_vertex = grh.count_vertex;
	this->edges = grh.edges;
	++copy_counter;
}

void graph::print() {
	cout << "---------------graph------------------" << std::endl;
	for (int i = 0; i < edges->size(); ++i) {
		for (int j = 0; j < (*edges)[i].size(); ++j) {
			cout << (*edges)[i][j].first << "  " << (*edges)[i][j].second << std::endl;
		}
	}
	cout << "---------------graph------------------" << std::endl;
}

graph::~graph() {
	--copy_counter;
	if (copy_counter == 0) delete edges;
}

/*****************************characteristics**********************************/
void characteristics::print() {
	cout << std::endl << "characteristics:  ";
	for (register int i = 0; i < this->size(); ++i)
		cout << (*this)[i] << "  ";
	cout << std::endl;
}

/****************************auxiliary*****************************************/

bool verify_input_data(const graph& grh, const characteristics& v_chr) {
	return grh.get_count_vertex() <= v_chr.size();
}

vector<vector<edge>>* read_edges(istream_iterator<int16_t>& iter) {
	edge _edge;
	size_t size;
	int16_t count_new_vertex;
	vector<vector<edge>>* edges = new vector<vector<edge>>();
	int count_edges = *(iter++);
	for (int i = 0; i < count_edges; ++i) {
		_edge.first = *(iter++);
		_edge.second = *(iter++);
		size = edges->size();
		if ((size < _edge.first) || (size < _edge.second)) {       //��������� ��� ����� ������ ������ ����
			count_new_vertex = (_edge.first > _edge.second) ? (_edge.first - size) :
				(_edge.second - size);
			for (int i = 0; i < count_new_vertex; ++i) {
				edges->push_back(std::vector<edge>());
			}
		}
		(*edges)[_edge.first - 1].push_back(_edge);
	}
	return edges;
}

/*���� ������� check_chr � v_app*/
bool method_branches_borders::find(const vector<int16_t>& v_app, int16_t check_chr)
{
	size_t size = v_app.size();
	for (register int i = 0; i < size; ++i)
		if (v_app[i] == check_chr) return true;
	return false;
}

inline int abs(int val) { return (val < 0) ? -val : val; }

void bubble_sort(vector<int16_t>& v_app) {
	for (int i = 0; i < v_app.size(); ++i) {
		for (int j = 0; j < v_app.size() - i - 1; ++j) {
			if (v_app[j] > v_app[j + 1]) {
				v_app[j] ^= (v_app[j + 1] ^= v_app[j]);
				v_app[j + 1] ^= v_app[j];
			}
		}
	}
}

/****************************method_branches_borders***************************/

/*����� ������ � �����*/
pair<node_decisions_tree, int>* method_branches_borders::process()
{
	node_decisions_tree* temp_node = nullptr;
	deque_pnode algorithm_path;
	node_decisions_tree* best_node = new node_decisions_tree();
	int best_lower_bound = lower_bound(best_node->v_app);
	int current_upper_bound = 0;
	int current_lower_bound = 0;
	algorithm_path.push_back(best_node);
	for (int i = 0; i < algorithm_path.size(); ++i) {
		current_upper_bound = upper_bound(algorithm_path[i]->v_app);
		current_lower_bound = lower_bound(algorithm_path[i]->v_app);
		if (current_upper_bound < best_lower_bound) continue;
		if (current_lower_bound >= best_lower_bound) {
			best_lower_bound = current_lower_bound;
			if (current_lower_bound == current_upper_bound) {
				best_node = algorithm_path[i];
				continue;
			}
		}
		for (int j = 0; j < size_chr; ++j) {
			if (find(algorithm_path[i]->v_app, (*v_chr)[j]) == false) {
				temp_node = new node_decisions_tree(algorithm_path[i]->v_app);
				temp_node->v_app.push_back((*v_chr)[j]);
				algorithm_path.push_back(temp_node);
			}
		}
	}
	return new pair<node_decisions_tree, int>(*best_node, best_lower_bound);
}

/*����� ��������� ������ ������ ����� ��������� �������*/
int16_t method_branches_borders::lower_bound(const vector<int16_t>& _v_app) {
	vector<int16_t> v_app(_v_app.begin(), _v_app.end());
	for (int i = 0; v_app.size() != size_edges; ++i) {
		if (find(v_app, (*v_chr)[i]) == false) v_app.push_back((*v_chr)[i]);
	}
	const vector<vector<edge>>* edges = grh->get_edges();
	edge temp_edge;
	int sum = 0;
	int temp = 0;
	for (int i = 0; i < size_edges; ++i) {
		for (int j = 0; j < hash_sizes[i]; ++j) {
			temp_edge = (*edges)[i][j];
			temp = v_app[temp_edge.first - 1] - v_app[temp_edge.second - 1];
			sum += abs(temp);
		}
	}
	return sum;
}

/*w_max, w_min - ������������ � ����������� �������������� �� ��������� ������������� �������������
v_chr - �������������(�� �������� � ��������) ��������� �������������
check1, check2 - 1(2) ����������, ��� ������� ����� �����������; 0 - �� ���������*/
int16_t method_branches_borders::upper_bound(const vector<int16_t>& v_app) {
	int16_t w_max = 0;
	int16_t w_min = 0;
	for (int i = size_chr - 1; i >= 0; --i)
		if (find(v_app, (*v_chr)[i]) == false) {
			w_max = (*v_chr)[i];
			break;
		}
	for (int i = 0; i < size_chr; ++i)
		if (find(v_app, (*v_chr)[i]) == false) {
			w_min = (*v_chr)[i];
			break;
		}

	edge temp_edge;
	int sum = 0;
	int temp;
	int check1;
	int check2;
	size_t size_v_app = v_app.size();
	const vector<vector<edge>>* edges = grh->get_edges();
	for (int i = 0; i < size_edges; ++i) {
		for (int j = 0; j < hash_sizes[i]; ++j) {
			temp_edge = (*edges)[i][j];
			check1 = ((temp_edge.first - 1) < size_v_app) ? 1 : 0;
			check2 = ((temp_edge.second - 1) < size_v_app) ? 2 : 0;
			switch (check1 + check2) {
			case 0:
				temp = w_max - w_min;
				break;
			case 1:
				temp = v_app[temp_edge.first - 1] -
					((abs(v_app[temp_edge.first - 1] - w_max) > abs(v_app[temp_edge.first - 1] - w_min)) ?
						w_max : w_min);
				break;
			case 2:
				temp = v_app[temp_edge.second - 1] -
					((abs(v_app[temp_edge.second - 1] - w_max) > abs(v_app[temp_edge.second - 1] - w_min)) ?
						w_max : w_min);
				break;
			case 3:
				temp = v_app[temp_edge.first - 1] - v_app[temp_edge.second - 1];
				break;
			}
			sum += abs(temp);
		}
	}
	return sum;
}

/*����� ������ � ������ ����� ����������� � ������� ������� � ������������� ����;
�������� ��� ��� �� ��������, ������� ����������� ��� ���������� ����������� ������� � lower_bound*/
void method_branches_borders::complete_best_solution(vector<int16_t>& v_app)
{
	size_t count_vertex = grh->get_count_vertex();
	for (int i = 0; v_app.size() != count_vertex; ++i) {
		if (find(v_app, (*v_chr)[i]) == false) v_app.push_back((*v_chr)[i]);
	}
}