#include <bits/stdc++.h>
using namespace std;

const long long INF = 9223372036854775807;

struct Edge {
  long long to;
  long long weight;
};

// functie care calculeaza distantele minime de la un nod de start la toate
// celelalte noduri din graf(dijkstra)
void dijkstra(vector<vector<Edge>> &graph, long long start,
              vector<long long> &dist) {
  priority_queue<pair<long long, long long>, vector<pair<long long, long long>>,
                 greater<pair<long long, long long>>>
      pq;
  pq.push({0, start});
  dist[start] = 0;

  while (!pq.empty()) {
    long long u = pq.top().second;
    long long d = pq.top().first;
    pq.pop();

    for (Edge &edge : graph[u]) {
      long long v = edge.to;
      long long w = edge.weight;

      if (dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        pq.push({dist[v], v});
      }
    }
  }
}

int main() {
  ifstream f("drumuri.in");
  ofstream o("drumuri.out");

  long long N, M, x, y, z;
  f >> N >> M;

  vector<vector<Edge>> graph(N + 1);
  vector<vector<Edge>> reversedGraph(N + 1);
  for (long long i = 0; i < M; ++i) {
    long long x, y, z;
    f >> x >> y >> z;
    graph[x].push_back({y, z});
    reversedGraph[y].push_back({x, z});
  }

  f >> x >> y >> z;

  vector<long long> distX(N + 1, INF), distY(N + 1, INF), distZ(N + 1, INF);


  // calculez distantele minime de la nodurile x, y la toate celelalte
  dijkstra(graph, x, distX);
  dijkstra(graph, y, distY);

  // calculez distantele minime de la nodul z la toate celelalte
  dijkstra(reversedGraph, z, distZ);

  long long minCost = INF;
  // caut drumul minim
  for (long long i = 1; i <= N; ++i) {
    // daca exista drum de la x la i, de la y la i si de la i la z
    // atunci actualizez costul minim
    if (distX[i] != INF && distY[i] != INF && distZ[i] != INF) {
      minCost = min(minCost, distX[i] + distY[i] + distZ[i]);
    }
  }

  o << minCost << endl;

  f.close();
  o.close();

  return 0;
}
