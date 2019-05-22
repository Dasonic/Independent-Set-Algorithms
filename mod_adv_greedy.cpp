#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

class Graph {
	private:
		vector<int> *adj_list;
		int num_vertices;
	public:
		Graph(int num_vertices) {
			this->num_vertices = num_vertices;
			this->adj_list = new vector<int>[num_vertices + 1];
		}
		void add_edge(int i, int j) {
			adj_list[i].push_back(j);
			adj_list[j].push_back(i);
		
		}
		/*
		bool is_edge(int i, int j) {
			return adj_matrix[i][j];
		}
		*/
		// Finds the vertex with the least amount of edges
		int find_min_degree() {
			unsigned int min_degree = 99999999;
			int min_vertex = -1;
			int total_size_min = 0;
			for (int i = 1; i < num_vertices; i++) {
				long unsigned int list_size = adj_list[i].size();
				// If the vertex has less edges than the minimum
				if (list_size > 0 && list_size < min_degree) {
					min_vertex = i;
					min_degree = list_size;
					total_size_min = 0;
				}
				// Else if the new vertex has the same number of edges as the minimum
				else if(list_size > 0 && list_size == min_degree) {
					recur_greedy(&i, &total_size_min, &min_vertex, &min_degree);
				}
			}
			return min_vertex;
		}
		// Remove a vertex from the adjacency list and matrix
		void remove_vertex(int vertex) {
			for (int i = 0; i < adj_list[vertex].size(); i++) {
				int remove_at = adj_list[vertex][i];
				adj_list[remove_at].clear();
			}
			adj_list[vertex].clear();
		}

		void recur_greedy(int *new_vertex, int *total_size_min, int *min_vertex, unsigned int *min_degree) {
			cout << *new_vertex << endl;
			int first_layer_nv_size = adj_list[*new_vertex].size(); // Number of vertexs directly connected to new vertex
			int total_size_new = 0;
			// Add the number of edges each endpoint vertex has for all vertexs with an endpoint at i
			for (int j = 0; j < first_layer_nv_size; j++) {
				total_size_new += adj_list[adj_list[*new_vertex][j]].size();
			}
			// If the total size for the current_min_vertex hasn't be calculated, calculate it now
			if (total_size_min == 0) {
				int first_layer_minv_size = adj_list[*min_vertex].size();
				for (int j = 0; j < first_layer_minv_size; j++) {
					total_size_min += adj_list[adj_list[*new_vertex][j]].size();
				}
			}
			// If the new vertex has less of a size than the min, update the min
			if (total_size_new < *total_size_min) {
				*min_vertex = *new_vertex;
				*min_degree = first_layer_nv_size;
			}
			else if (total_size_new == *total_size_min)
				cout << "recuring ";
				recur_greedy(new_vertex, total_size_min, min_vertex, min_degree);
			return;
		}
};

Graph * read_graph() {
	int num_nodes;
	int num_edges;
	// Open file
	std::ifstream graphData ("keller6.clq");
	std::string line;
	Graph *as;
	// While there is another line
	while (std::getline(graphData, line))
	{
		// If line starts with 'p', initialise as
		if (line[0] == 'p') {
			sscanf(line.c_str(), "%*s %*s %d %d", &num_nodes, &num_edges);
			cout << num_nodes << endl;
			as = new Graph(num_nodes);
		}
		// Else if line starts with 'e', add to as
		else if (line[0] == 'e') {
			int node1;
			int node2;
			sscanf(line.c_str(), "%*s %d %d", &node1, &node2);
			
			as->add_edge(node1, node2);
		}
	}
	graphData.close();
	return as;
}


int main(int argc, char * argv[]) {
	list<int> max_independent_set;
	Graph *as = read_graph();
	int count = 1000;
	while (count >= 0) {
		int next_vertex = as->find_min_degree();
		//cout << "Min degree: " << next_vertex << endl;
		if (next_vertex > 0) {
			max_independent_set.push_back(next_vertex);
			as->remove_vertex(next_vertex);
		} else break;
		count--;
	}
	cout << "Num vertexs: " << max_independent_set.size() << endl;
	for (int i : max_independent_set) {
		cout << i << " ";
	}
	cout << endl;
}