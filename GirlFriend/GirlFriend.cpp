/* Read input from STDIN. Print your output to STDOUT*/

#include<iostream>
#include <list>
#include <queue>
using namespace std;
# define MAX_VALUE 0x3f3f3f3f

typedef pair<int, int> edge;

class Graph
{
	int NoOfVertices;
	list<edge>* path;

public:
	Graph(int noOfVertices);
	void addPath(int u, int v, int w);
	void shortestDistanceFromSource(int s);
};

Graph::Graph(int noOfVertices)
{
	this->NoOfVertices = noOfVertices;
	path = new list<edge>[NoOfVertices];
}

void Graph::addPath(int u, int v, int w)
{
	path[u].push_back(make_pair(v, w));
	path[v].push_back(make_pair(u, w));
}

void Graph::shortestDistanceFromSource(int src)
{
	priority_queue<edge, vector <edge>, greater<edge>> pq;
	vector<int> distance(NoOfVertices, MAX_VALUE);

	pq.push(make_pair(0, src));
	distance[src] = 0;

	vector<bool> f(NoOfVertices, false);
	while (!pq.empty())
	{
		int u = pq.top().second;
		pq.pop();
		f[u] = true;

		list<edge>::iterator i;
		for (i = path[u].begin(); i != path[u].end(); ++i)
		{
			int v = (*i).first;
			int weight = (*i).second;

			int diff = weight - distance[u];
			if (diff > 0)
			{
				weight = diff;
			}
			else
			{
				weight = 0;
			}
			if (f[v] == false && distance[v] > distance[u] + weight)
			{

				distance[v] = distance[u] + weight;
				pq.push(make_pair(distance[v], v));
			}
		}
	}
	if (distance[NoOfVertices - 1] == MAX_VALUE)
		cout << "NOT POSSIBLE";
	else
		cout << distance[NoOfVertices - 1];
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int noOfHouses, noOfPath;

	cin >> noOfHouses;
	cin >> noOfPath;

	Graph g(noOfHouses);


	for (int i = 0;i < noOfPath;i++)
	{
		int s, d, w;
		cin >> s;
		cin >> d;
		cin >> w;
		g.addPath(s - 1, d - 1, w);

	}

	g.shortestDistanceFromSource(0);

	return 0;
}