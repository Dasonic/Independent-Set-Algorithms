#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <iterator>

using namespace std;



void read_graph(multimap<int, int> *adj_map) {
	int num_nodes;
	int num_edges;
	// Open file
	std::ifstream graphData ("brock800_1.clq");
	std::string line;
	// While there is another line
	while (std::getline(graphData, line))
	{
		//cout << "getting line" << endl;
		// If line starts with 'p', initialise as
		if (line[0] == 'p') {
			sscanf(line.c_str(), "%*s %*s %d %d", &num_nodes, &num_edges);
			cout << "# Vertexes: " << num_nodes << endl;
		}
		// Else if line starts with 'e', add to as
		else if (line[0] == 'e') {
			int node1;
			int node2;
			sscanf(line.c_str(), "%*s %d %d", &node1, &node2);
			
			adj_map->insert(make_pair(node1, node2));
			adj_map->insert(make_pair(node2, node1));
		}
	}
	cout << "closing graph" << endl;
	graphData.close();
	return;
}

int find_min_degree(multimap<int, int> *adj_map) {
	return 1;
}

void remove_vertex(multimap<int, int> *adj_map, int to_remove) {
	auto ret = adj_map->equal_range(to_remove);
	cout << "Entered removed vertex" << endl;
	for (auto it = ret.first; it != ret.second; ++it) {
		typedef multimap<int, int>::iterator iterator;
		std::pair<iterator, iterator> iterpair = adj_map->equal_range(it->second);
		cout << "About to erase" << endl;
		// Erase (b,15) pair
		//
		iterator iter = iterpair.first;
		for (; iter != iterpair.second; ++it) {
			if (iter->second == 15) { 
				adj_map->erase(iter);
				break;
				cout << "pair erased" << endl;
			}
		}	
	}
	cout << "Exiting removed vertex" << endl;
}


int main(int argc, char * argv[]) {
	list<int> max_independent_set;
	multimap<int, int> adj_map;
	read_graph(&adj_map);
	do {
		int next_vertex = find_min_degree(&adj_map);
		if (next_vertex != 0) {
			max_independent_set.push_back(next_vertex);
			remove_vertex(&adj_map, next_vertex);
		} else break;
	} while (true);
	cout << "Num vertexs: " << max_independent_set.size() << endl;
	for (int i : max_independent_set) {
		cout << i << " ";
	}
}