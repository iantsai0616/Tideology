#include "../utilities/template.h"

#include "../../content/graph/MinCut.h"
#include "../../content/graph/Dinic.h"

int main(){
  mt19937 rng(123);
  rep(it, 0, 3000){
    int n = 2+rng()%9, s = 0, t = n-1;
    vector<array<int, 3>> ed; Dinic dinic(n);
    rep(i, 0, n) rep(j, 0, n) if(i != j && rng()%4 == 0){
      int c = rng()%10; ed.pb({i, j, c}); dinic.addEdge(i, j, c);
    }
    ll flow = dinic.calc(s, t), brute = LLONG_MAX;
    rep(mask, 0, 1 << n) if((mask & 1) && !(mask >> t & 1)){
      ll cut = 0;
      for(auto [a, b, c] : ed) if((mask >> a & 1) && !(mask >> b & 1)) cut += c;
      brute = min(brute, cut);
    }
    assert(flow == brute && dinic.leftOfMinCut(s) && !dinic.leftOfMinCut(t));
    ll cut = 0;
    for(auto [a, b, c] : ed){
      if(dinic.leftOfMinCut(a) && !dinic.leftOfMinCut(b)) cut += c;
    }
    assert(cut == flow);
  }
  cout << "Tests passed!\n";
}
