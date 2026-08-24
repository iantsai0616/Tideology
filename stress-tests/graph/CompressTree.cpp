#include "../utilities/template.h"

#include "../../content/graph/CompressTree.h"

int main(){
  vector<vi> g(7);
  for(auto [a, b] : vector<pii>{{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}, {5, 6}}){
    g[a].pb(b); g[b].pb(a);
  }
  LCA lca(g);
  assert(compressTree(lca, {}).empty());
  auto t = compressTree(lca, {3, 4, 6});
  assert(t == vector<pii>({{0, 0}, {0, 1}, {1, 3}, {1, 4}, {0, 6}}));
  cout << "Tests passed!\n";
}
