/**
 * Description: Vertex-biconnected components and the block-cut forest.
 *  Original vertices are [0, n), component nodes are [n, n+nbcc).
 * Time: O(V+E)
 * Status: stress-tested, including parallel edges
 */
#pragma once

struct BCC{
  int n, m = 0, nbcc = 0, ti = 0;
  vector<vector<pii>>g;
  vector<vi>tree, comp;
  vi in, low;
  BCC(int n): n(n), g(n){}
  void add_edge(int u, int v){
    g[u].pb({v, m});
    g[v].pb({u, m++});
  }
  void add_comp(int u, int v, vi &stk){
    int id = n + nbcc++;
    tree.pb({}); comp.pb({});
    while(1){
      int x = stk.back(); stk.pop_back();
      tree[id].pb(x), tree[x].pb(id), comp.back().pb(x);
      if(x == v) break;
    }
    tree[id].pb(u), tree[u].pb(id), comp.back().pb(u);
  }
  void build(){
    nbcc = ti = 0; in.assign(n, -1); low.resize(n);
    tree.assign(n, {}); comp.clear(); tree.reserve(n + m);
    vi it(n), par(n, -1), pe(n, -1), stk, dfs;
    rep(s, 0, n) if(in[s] == -1){
      if(g[s].empty()){
        int id = n + nbcc++;
        tree.pb({s}); tree[s].pb(id); comp.pb({s});
        in[s] = low[s] = ti++;
        continue;
      }
      in[s] = low[s] = ti++; stk.pb(s); dfs.pb(s);
      while(sz(dfs)){
        int u = dfs.back();
        if(it[u] < sz(g[u])){
          auto [v, e] = g[u][it[u]++];
          if(e == pe[u]) continue;
          if(in[v] == -1){
            par[v] = u; pe[v] = e; in[v] = low[v] = ti++;
            stk.pb(v); dfs.pb(v);
          }else low[u] = min(low[u], in[v]);
        }else{
          dfs.pop_back();
          if(pe[u] != -1){
            int p = par[u];
            low[p] = min(low[p], low[u]);
            if(low[u] >= in[p]) add_comp(p, u, stk);
          }
        }
      }
      stk.clear();
    }
  }
  bool is_cut(int u) const { return sz(tree[u]) > 1; }
  const vi &bcc(int id) const { return comp[id]; }
};
