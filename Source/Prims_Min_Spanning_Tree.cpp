// HW3.cpp : Defines the entry point for the console application.

#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <functional>
#include <utility>
#include "Graph.hpp"

using namespace std;
// Prototypes
vector<int> prims(Graph &graph, int source);

int main()
{
	Graph g(9);
	g.add_edge(0, 1, 4);
	g.add_edge(0, 7, 8);
	g.add_edge(1, 2, 8);
	g.add_edge(1, 7, 11);
	g.add_edge(2, 3, 7);
	g.add_edge(2, 8, 2);
	g.add_edge(2, 5, 4);
	g.add_edge(3, 4, 9);
	g.add_edge(3, 5, 14);
	g.add_edge(4, 5, 10);
	g.add_edge(5, 6, 2);
	g.add_edge(6, 7, 1);
	g.add_edge(6, 8, 6);
	g.add_edge(7, 8, 7);

	cout << g.V();
	g.print_Graph();

	vector<int> MST = prims(g, 0);

	for (int i = 1; i < g.V(); i++)
	{
		cout << MST[i] << " - " << i << endl;
	}

	getchar();
	return 0;
}

vector<int> prims(Graph &graph, int source)
{
	priority_queue< pair<double, int>, vector< pair<double, int> >, greater<pair<double, int> >> pq;
	vector<int> parent(graph.V(), -1);
	vector<double> dist(graph.V(), INT_MAX);

	pq.push(make_pair(dist[0], source));

	for (int v = 0; v < graph.V(); v++)
	{
		if (v != source)
		{
			dist[v] = DBL_MAX;
		}
		pq.push(make_pair(dist[v], v));
	}


	while (!pq.empty())
	{
		int u = pq.top().second;
		pq.pop();
		vector<int> neighbors = graph.neighbors(u);

		for (auto v : neighbors)
		{
			double cur_dist = graph.edge_weight(u, v);
			bool visited = (find(parent.begin(), parent.end(), v) != parent.end());

			if (!visited && dist[v] > cur_dist)
			{
				dist[v] = cur_dist;
				pq.push(make_pair(dist[v], v));
				parent[v] = u;
			}
		}
	}
	return parent;
}