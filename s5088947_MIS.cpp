#include <iostream>
#include <fstream>
#include <list>
#include <map>

using namespace std;

class Graph {
	private:
		//bool **adj_matrix;
		//list<int> *adj_list;
		int num_vertices;
		map<int, list<int>> test_list;
	public:
		Graph(int num_vertices) {
			this->num_vertices = num_vertices;
			// Declare adjacency matrix
			//adj_matrix[num_vertices][num_vertices] = {false};
			//cout << adj_matrix[300][400] << endl;
			// Declare adjacency list
			//adj_list = new list<int>[num_vertices];
		}
		void add_edge(int i, int j) {
			cout << "In add edge" << endl;
			/*
			cout << adj_matrix[300][400] << endl;
			adj_matrix[i][j] = true;
			adj_matrix[j][i] = true;
			cout << "after matrix" << endl;
			*/
			test_list[i].push_back(j);
			test_list[j].push_back(i);
			/*
			adj_list[i].push_back(j);
			adj_list[j].push_back(i);
			cout << "after list" <<endl;
			*/
		}
		/*
		bool is_edge(int i, int j) {
			return adj_matrix[i][j];
		}
		*/
		// Finds the vertex with the least amount of edges
		int find_min_degree() {
			unsigned int min_degree = 99999999;
			//tuple min_vertex = make_tuple(-1, -1);
			int min_vertex = -1;
			for (int i = 0; i < num_vertices; i++) {
				long unsigned int list_size = test_list[i].size();
				if (list_size > 0 && list_size < min_degree) {
					min_vertex = i;
					min_degree = list_size;
				}
			}
			return min_vertex;
		}
		// Remove a vertex from the adjacency list and matrix
		void remove_vertex(int vertex) {
			for (int i = 0; i < test_list[vertex].size(); i++) {
				int joining_vertex = test_list[vertex].pop_front();
				std::list<int>::iterator findIter = find(test_list[joining_vertex].begin(), test_list[joining_vertex].end(), vertex);
				cout << "Value at " << findIter << endl;
				test_list[joining_vertex].erase(findIter);
			}
			/*
			for(int i = 0; i < num_vertices; i++) {
				if (adj_matrix[vertex][i] == true){
					adj_matrix[vertex][i] = false;
					adj_matrix[i][vertex] = false;
					adj_list[i].remove(vertex);
					adj_list[vertex].remove(i);
				}
			}
			*/
		}
};

Graph * read_graph() {
	int num_nodes;
	int num_edges;
	// Open file
	cout << "before ifstream" <<endl;
	std::ifstream graphData ("brock800_1.clq");
	std::string line;
	Graph *as;
	// While there is another line
	while (std::getline(graphData, line))
	{
		//cout << "getting line" << endl;
		// If line starts with 'p', initialise as
		if (line[0] == 'p') {
			sscanf(line.c_str(), "%*s %*s %d %d", &num_nodes, &num_edges);
			cout << num_nodes << endl;
			as = new Graph(num_nodes);
		}
		// Else if line starts with 'e', add to as
		else if (line[0] == 'e') {
			cout << "found an edge" << endl;
			int node1;
			int node2;
			sscanf(line.c_str(), "%*s %d %d", &node1, &node2);
			cout << "after scanf" << endl;
			
			as->add_edge(node1, node2);
			as->add_edge(node1, node2);
		}
	}
	cout << "closing graph" << endl;
	graphData.close();
	return as;
}


int main(int argc, char * argv[]) {
	list<int> max_independent_set;
	Graph *as = read_graph();
	do {
		int next_vertex = as->find_min_degree();
		if (next_vertex != 0) {
			max_independent_set.push_back(next_vertex);
			as->remove_vertex(next_vertex);
		} else break;
	} while (true);
	cout << "Num vertexs: " << max_independent_set.size() << endl;
	for (int i : max_independent_set) {
		cout << i << " ";
	}
}