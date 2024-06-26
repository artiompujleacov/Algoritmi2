#include <algorithm>
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

/* ca sursa de inspiratie mi-a servit:
"https://www.geeksforgeeks.org/2-satisfiability-2-sat-problem/" */

vector<vector<int>> adj, adj_rev;
vector<bool> visited;
vector<int> order, component;


// dfs1 pentru Kosaraju
void dfs1(int v) {
  visited[v] = true;
  for (int u : adj[v]) {
    if (!visited[u])
      dfs1(u);
  }
  order.push_back(v);
}


// dfs2 pentru Kosaraju
void dfs2(int v, int c) {
  component[v] = c;
  for (int u : adj_rev[v]) {
    if (component[u] == -1)
      dfs2(u, c);
  }
}

int main() {
  ifstream cin("scandal.in");
  ofstream cout("scandal.out");
  int N, M;
  cin >> N >> M;

  adj.resize(2 * N);
  adj_rev.resize(2 * N);
  visited.resize(2 * N);
  component.resize(2 * N, -1);

  for (int i = 0; i < M; ++i) {
    int x, y, c;
    cin >> x >> y >> c;
    --x;
    --y;

    // in dependenta de caz, adaug muchiile in graf intr-un fel anumit
    switch (c) {
    case 0:
      adj[x + N].push_back(y);
      adj[y + N].push_back(x);
      adj_rev[y].push_back(x + N);
      adj_rev[x].push_back(y + N);
      break;
    case 1:
      adj[x + N].push_back(y + N);
      adj[y].push_back(x);
      adj_rev[y + N].push_back(x + N);
      adj_rev[x].push_back(y);
      break;
    case 2:
      adj[y + N].push_back(x + N);
      adj[x].push_back(y);
      adj_rev[x + N].push_back(y + N);
      adj_rev[y].push_back(x);
      break;
    case 3:
      adj[x].push_back(y + N);
      adj[y].push_back(x + N);
      adj_rev[y + N].push_back(x);
      adj_rev[x + N].push_back(y);
      break;
    }
  }

  // pasul 1 din Kosaraju
  for (int i = 0; i < 2 * N; ++i) {
    if (!visited[i])
      dfs1(i);
  }

  int c = 0;
  // pasul 2 din Kosaraju
  for (int i = 0; i < 2 * N; ++i) {
    int v = order[2 * N - 1 - i];
    if (component[v] == -1)
      dfs2(v, c++);
  }

  vector<int> result;
  // verific daca e satisfiabil
  for (int i = 0; i < N; ++i) {
    if (component[i] > component[i + N]) {
      result.push_back(i + 1);
    }
  }

  cout << result.size() << endl;
  for (int guest : result) {
    cout << guest << endl;
  }

  cin.close();
  cout.close();
  return 0;
}
