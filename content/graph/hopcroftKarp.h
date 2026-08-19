/**
 * Description: Maximum bipartite matching. r[v] is the left match of right v.
 * Time: O(E sqrt(V))
 * Status: stress-tested
 */
#pragma once

struct HopcroftKarp{
  int n, m;
  vector<vi>g;
  vi l, r, d, q;
  HopcroftKarp(int N, int M): n(N), m(M), g(N), q(N){}
  void addEdge(int u, int v){
    g[u].pb(v);
  }
  bool dfs(int u){
    int z = exchange(d[u], 0) + 1;
    for(int v : g[u]){
      if(r[v] == -1 or (d[r[v]] == z and dfs(r[v]))){
        l[u] = v;
        r[v] = u;
        return 1;
      }
    }
    return 0;
  }
  pair<int, vi> calc(){
    int ans = 0;
    l.assign(n, -1);
    r.assign(m, -1);
    for(;;){
      int s = 0, t = 0;
      bool found = 0;
      d.assign(n, 0);
      rep(i, 0, n) if(l[i] == -1) q[t++] = i, d[i] = 1;
      while(s < t){
        int u = q[s++];
        for(int v : g[u]){
          if(r[v] == -1) found = 1;
          else if(!d[r[v]]) d[r[v]] = d[u] + 1, q[t++] = r[v];
        }
      }
      if(!found) return {ans, r};
      rep(i, 0, n) if(l[i] == -1) ans += dfs(i);
    }
  }
};
