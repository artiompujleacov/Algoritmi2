#include <bits/stdc++.h>
using namespace std;

const long long INF = 9223372036854775807;

struct Edge {
  long long to;
  long long weight;
};

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

    if (d > dist[u])
      continue;

    for (const auto &edge : graph[u]) {
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
  for (long long i = 0; i < M; ++i) {
    long long u, v, w;
    f >> u >> v >> w;
    graph[u].push_back({v, w});
  }

  f >> x >> y >> z;

  vector<long long> distX(N + 1, INF), distY(N + 1, INF), distZ(N + 1, INF);
  vector<vector<Edge>> reversedGraph(N + 1);

  for (long long u = 1; u <= N; ++u) {
    for (const auto &edge : graph[u]) {
      reversedGraph[edge.to].push_back({u, edge.weight});
    }
  }

  dijkstra(graph, x, distX);
  dijkstra(graph, y, distY);
  dijkstra(reversedGraph, z, distZ);

  long long minCost = INF;
  for (long long u = 1; u <= N; ++u) {
    if (distX[u] != INF && distY[u] != INF && distZ[u] != INF) {
      if (distX[u] > INF - distY[u] || distX[u] + distY[u] > INF - distZ[u]) {
        continue;
      }
      minCost = min(minCost, distX[u] + distY[u] + distZ[u]);
    }
  }

  o << minCost << endl;

  f.close();
  o.close();

  return 0;
}
