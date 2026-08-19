/**
 * Description: Directed or undirected Euler trail/cycle.
 * Time: O(V+E)
 * Status: stress-tested
 */
#pragma once

struct EulerWalk{
  int n, m = 0;
  bool undir;
  vector<vector<pii>>g;
  EulerWalk(int N, bool undir_ = false): n(N), undir(undir_), g(N){}
  void addEdge(int u, int v){
    g[u].pb({v, m});
    if(undir) g[v].pb({u, m});
    m++;
  }
  vi calc(int src = 0){
    vi deg(n), it(n), used(m), ans, st = {src};
    deg[src]++;
    while(sz(st)){
      int u = st.back(), &i = it[u];
      if(i == sz(g[u])){
        ans.pb(u);
        st.pop_back();
        continue;
      }
      auto [v, id] = g[u][i++];
      if(!used[id]){
        deg[u]--;
        deg[v]++;
        used[id] = 1;
        st.pb(v);
      }
    }
    for(int x : deg) if(x < 0 or sz(ans) != m + 1) return {};
    reverse(all(ans));
    return ans;
  }
};
