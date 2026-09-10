#include "../utilities/template.h"
#include "../../content/graph/BellmanFord.h"

int main(){
  mt19937 rng(1);
  rep(it, 0, 20000){
    int n = rng() % 8 + 1, s = rng() % n;
    BellmanFord bf(n);
    vector<tuple<int, int, ll>>ed;
    rep(u, 0, n) rep(v, 0, n) if(rng() % 4 == 0){
      ll w = (int)(rng() % 21) - 10;
      bf.addEdge(u, v, w);
      ed.pb({u, v, w});
    }
    auto [got, par] = bf.calc(s);
    const ll INF = 1LL << 62;
    vector<ll>want(n, INF);
    want[s] = 0;
    rep(i, 1, n) for(auto [u, v, w] : ed)
      if(want[u] != INF) chmin(want[v], want[u] + w);
    rep(i, 0, n) for(auto [u, v, w] : ed){
      if(want[u] == -INF) want[v] = -INF;
      else if(want[u] != INF and want[u] + w < want[v]) want[v] = -INF;
    }
    assert(got == want);
    rep(v, 0, n) if(v != s and got[v] != INF and got[v] != -INF){
      bool ok = 0;
      for(auto [u, x, w] : ed) if(x == v and u == par[v] and got[u] + w == got[v]) ok = 1;
      assert(ok);
    }
  }
  cout << "Tests passed!\n";
}
