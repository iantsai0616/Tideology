#include "../utilities/template.h"

#include "../../content/graph/GeneralMatching.h"

int brute(vector<vi>& g, int mask){
  if(!mask) return 0;
  int a = __builtin_ctz(mask), ans = brute(g, mask ^ (1 << a));
  for(int b : g[a]) if(mask >> b & 1){
    ans = max(ans, 1+brute(g, mask^(1 << a)^(1 << b)));
  }
  return ans;
}

int main(){
  mt19937 rng(123);
  rep(n, 1, 13) rep(it, 0, 300){
    vector<vi> g(n); vector<pii> ed;
    rep(i, 0, n) rep(j, i+1, n) if(rng() % 2){
      g[i].pb(j); g[j].pb(i); ed.pb({i, j});
    }
    GeneralMatching gm(n);
    for(auto [a, b] : ed) gm.addEdge(a, b);
    auto [cnt, mt] = gm.calc();
    assert(cnt == brute(g, (1 << n) - 1));
    assert(sz(mt) == n);
    rep(i, 0, n) if(mt[i] != -1){
      assert(mt[mt[i]] == i);
      assert(find(all(g[i]), mt[i]) != g[i].end());
    }
  }
  int n = 500; vector<pii> ed;
  rep(i, 0, n) rep(j, i+1, n) if((i*911 + j*3571) % 97 < 3) ed.pb({i, j});
  auto st = chrono::steady_clock::now();
  GeneralMatching gm(n);
  for(auto [a, b] : ed) gm.addEdge(a, b);
  auto [cnt, mt] = gm.calc();
  double sec = chrono::duration<double>(chrono::steady_clock::now()-st).count();
  assert(cnt <= n/2 && sz(mt) == n && sec < 1);
  cout << "Tests passed! " << sec << "s\n";
}
