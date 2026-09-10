#include "../utilities/template.h"
#include "../../content/graph/DFSMatching.h"
#include "../../content/graph/hopcroftKarp.h"

int main(){
  mt19937 rng(2);
  rep(it, 0, 30000){
    int n = rng() % 8, m = rng() % 8;
    DFSMatching dm(n, m);
    HopcroftKarp hk(n, m);
    vector<vi>g(n);
    rep(u, 0, n) rep(v, 0, m) if(rng() % 3 == 0){
      g[u].pb(v);
      dm.addEdge(u, v);
      hk.addEdge(u, v);
    }
    vi dp(1 << m, -1);
    dp[0] = 0;
    rep(u, 0, n){
      vi ndp = dp;
      rep(msk, 0, 1 << m) if(dp[msk] != -1) for(int v : g[u]) if(!(msk >> v & 1))
        chmax(ndp[msk | 1 << v], dp[msk] + 1);
      dp.swap(ndp);
    }
    int want = *max_element(all(dp));
    for(auto [cnt, r] : {dm.calc(), hk.calc()}){
      assert(cnt == want and sz(r) == m);
      vector<bool>used(n);
      int sum = 0;
      rep(v, 0, m) if(r[v] != -1){
        assert(0 <= r[v] and r[v] < n and !used[r[v]]);
        assert(find(all(g[r[v]]), v) != g[r[v]].end());
        used[r[v]] = 1;
        sum++;
      }
      assert(sum == cnt);
    }
  }
  cout << "Tests passed!\n";
}
