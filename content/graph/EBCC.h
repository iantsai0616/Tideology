/**
 * Description: Bridges and edge-biconnected components of an undirected graph.
 * Time: O(V+E)
 * Status: stress-tested, including parallel edges
 */
#pragma once

struct EBCC{
  int n, m = 0, nbcc = 0, ti = 0;
  vector<vector<pii>>g;
  vi in, low, id, is_bridge;
  EBCC(int n): n(n), g(n){}
  void add_edge(int u, int v){
    g[u].pb({v, m});
    g[v].pb({u, m++});
  }
  int build(){
    nbcc = ti = 0; in.assign(n, -1); low.resize(n); id.assign(n, -1);
    is_bridge.assign(m, 0);
    vi it(n), par(n, -1), pe(n, -1), stk;
    rep(s, 0, n) if(in[s] == -1){
      in[s] = low[s] = ti++; stk.pb(s);
      while(sz(stk)){
        int u = stk.back();
        if(it[u] < sz(g[u])){
          auto [v, e] = g[u][it[u]++];
          if(e == pe[u]) continue;
          if(in[v] == -1){
            par[v] = u; pe[v] = e; in[v] = low[v] = ti++; stk.pb(v);
          }else low[u] = min(low[u], in[v]);
        }else{
          stk.pop_back();
          if(pe[u] != -1){
            int p = par[u];
            low[p] = min(low[p], low[u]);
            if(low[u] > in[p]) is_bridge[pe[u]] = 1;
          }
        }
      }
    }
    rep(s, 0, n) if(id[s] == -1){
      id[s] = nbcc++; stk.pb(s);
      while(sz(stk)){
        int u = stk.back(); stk.pop_back();
        for(auto [v, e] : g[u]) if(!is_bridge[e] and id[v] == -1){
          id[v] = id[s]; stk.pb(v);
        }
      }
    }
    return nbcc;
  }
};
