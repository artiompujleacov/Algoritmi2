#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

const int MOD = 1e9 + 7;
vector<vector<int>> graph1, graph2;
vector<int> dp;

void topologicalSort(vector<vector<int>> &adj, int V, stack<int> &Stack) {
  vector<int> in_degree(V, 0);
  for (int u = 0; u < V; ++u) {
    for (int v : adj[u]) {
      in_degree[v]++;
    }
  }
  for (int u = 0; u < V; ++u) {
    if (in_degree[u] == 0) {
      Stack.push(u);
    }
  }
  while (!Stack.empty()) {
    int u = Stack.top();
    Stack.pop();
    for (int v : adj[u]) {
      if (--in_degree[v] == 0) {
        Stack.push(v);
      }
    }
  }
}

int main() {
  ifstream f("numarare.in");
  ofstream o("numarare.out");
  int N, M;
  f >> N >> M;

  graph1 = vector<vector<int>>(N + 1);
  graph2 = vector<vector<int>>(N + 1);
  dp = vector<int>(N + 1, 0);

  for (int i = 0; i < M; i++) {
    int x, y;
    f >> x >> y;
    graph1[x].push_back(y);
  }

  for (int i = 0; i < M; i++) {
    int x, y;
    f >> x >> y;
    graph2[x].push_back(y);
  }

  stack<int> topo_order;
  topologicalSort(graph1, N + 1, topo_order);

  dp[1] = 1;
  for (int u = 1; u <= N; ++u) {
    for (int v : graph1[u]) {
      if (find(graph2[u].begin(), graph2[u].end(), v) != graph2[u].end()) {
        dp[v] = (dp[v] + dp[u]) % MOD;
      }
    }
  }

  o << dp[N] << "\n";

  f.close();
  o.close();

  return 0;
}
