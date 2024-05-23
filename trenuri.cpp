#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

using namespace std;


int longest_path(map<string, vector<string>> &graph, string node,
                 map<string, int> &longest_paths) {
  // daca am calculat deja lungimea celui mai lung drum care incepe din nodul
  // curent, returnez acea valoare
  if (longest_paths.count(node)) {
    return longest_paths.at(node);
  }
  int max_path_length = 0;
  // iterez prin vecinii nodului curent si calculez lungimea celui mai lung
  // drum care incepe dintr-unul din vecinii nodului curent
  for (vector<string>::iterator it = graph[node].begin();
       it != graph[node].end(); ++it) {
    int path_length = longest_path(graph, *it, longest_paths);
    max_path_length = max(max_path_length, path_length + 1);
  }

  longest_paths[node] = max_path_length;

  return max_path_length;
}

int main() {
  ifstream fin("trenuri.in");
  ofstream fout("trenuri.out");

  string source, destination;
  int N;

  getline(fin, source, ' ');
  getline(fin, destination);
  fin >> N;
  fin.ignore();

  map<string, vector<string>> graph;

  for (int i = 0; i < N; i++) {
    string line;
    getline(fin, line);
    stringstream ss(line);

    string x, y;
    ss >> x >> y;
    graph[x].push_back(y);
  }

  map<string, int> longest_paths;
  int max_path_length = longest_path(graph, source, longest_paths) + 1;

  fout << max_path_length << endl;

  fin.close();
  fout.close();
  return 0;
}
