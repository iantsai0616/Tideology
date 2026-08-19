/**
 * Description: Simple bipartite matching. r[v] is the left match of right v.
 * Time: O(VE)
 * Status: stress-tested
 */
#pragma once

struct DFSMatching{
  int n, m;
  vector<vi>g;
  vi r, vis;
  DFSMatching(int N, int M): n(N), m(M), g(N){}
  void addEdge(int u, int v){
    g[u].pb(v);
  }
  bool dfs(int u){
    if(vis[u]) return 0;
    vis[u] = 1;
    for(int v : g[u]){
      if(r[v] == -1 or dfs(r[v])){
        r[v] = u;
        return 1;
      }
    }
    return 0;
  }
  pair<int, vi> calc(){
    int ans = 0;
    r.assign(m, -1);
    rep(i, 0, n){
      vis.assign(n, 0);
      ans += dfs(i);
    }
    return {ans, r};
  }
};
