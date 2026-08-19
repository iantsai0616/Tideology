#include "../utilities/template.h"
#include "../../content/graph/MinimumVertexCover.h"

int main(){
  rep(it, 0, 300000){
    int n = rand() % 20, m = rand() % 20, p = rand();
    HopcroftKarp hk(n, m);
    MinimumVertexCover vc(n, m);
    vector<pii>ed;
    rep(i, 0, n) rep(j, 0, m) if(rand() < p){
      hk.addEdge(i, j);
      vc.addEdge(i, j);
      ed.pb({i, j});
    }
    auto [cnt, r] = hk.calc();
    vi cover = vc.cover();
    assert(sz(cover) == cnt);
    vector<bool>left(n), right(m);
    for(int x : cover){
      if(x < n) left[x] = 1;
      else right[x - n] = 1;
    }
    for(auto [u, v] : ed) assert(left[u] or right[v]);
    int got = 0;
    rep(v, 0, m) if(r[v] != -1) got++;
    assert(got == cnt);
  }
  cout << "Tests passed!\n";
}
