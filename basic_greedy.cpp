#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <list>
#include <string>

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
		// Finds the vertex with the least amount of edges
		int find_min_degree() {
			unsigned int min_degree = 99999999;
			int min_vertex = -1;
			for (int i = 1; i < num_vertices; i++) {
				long unsigned int list_size = adj_list[i].size();
				if (list_size > 0 && list_size < min_degree) {
					min_vertex = i;
					min_degree = list_size;
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
};

Graph * read_graph(string file_name) {
	int num_nodes;
	int num_edges;
	// Open file
	std::ifstream graphData (file_name);
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
	Graph *as = read_graph(argv[1]);
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