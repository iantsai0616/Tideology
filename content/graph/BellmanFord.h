/**
 * Description: Single-source shortest paths with negative cycles.
 * Unreachable vertices have INF; vertices after a negative cycle have -INF.
 * Time: O(VE)
 * Status: stress-tested
 */
#pragma once

struct BellmanFord{
  struct Edge{ int u, v; ll w; };
  const ll INF = 1LL << 62;
  int n;
  vector<Edge>ed;
  BellmanFord(int N): n(N){}
  void addEdge(int u, int v, ll w){
    ed.pb({u, v, w});
  }
  pair<vector<ll>, vi> calc(int s){
    vector<ll>d(n, INF);
    vi par(n, -1);
    d[s] = 0;
    rep(i, 0, n){
      for(auto [u, v, w] : ed) if(d[u] != INF){
        ll nd = max(-INF, d[u] + w);
        if(nd < d[v]) d[v] = i == n - 1 ? -INF : nd, par[v] = u;
      }
    }
    rep(i, 0, n) for(auto [u, v, w] : ed)
      if(d[u] == -INF) d[v] = -INF;
    return {d, par};
  }
};
