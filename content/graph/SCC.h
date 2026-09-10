/**
 * Description: Iterative Kosaraju SCC. sccid is in reverse topological order.
 * Time: O(V+E)
 * Status: stress-tested, Library Checker
 */
#pragma once

struct SCC{
  int n, cnt = 0;
  vector<vi>g, rg;
  vi sccid;
  SCC(int n): n(n), g(n), rg(n), sccid(n, -1){}
  void add_edge(int u, int v){
    g[u].pb(v);
    rg[v].pb(u);
  }
  int build(){
    vi it(n), order, st;
    vector<bool>vis(n);
    rep(s, 0, n) if(!vis[s]){
      st.pb(s);
      vis[s] = 1;
      while(sz(st)){
        int u = st.back();
        if(it[u] == sz(g[u])){
          order.pb(u);
          st.pop_back();
        }else{
          int v = g[u][it[u]++];
          if(!vis[v]) vis[v] = 1, st.pb(v);
        }
      }
    }
    cnt = 0;
    sccid.assign(n, -1);
    reverse(all(order));
    for(int s : order) if(sccid[s] == -1){
      st.clear();
      st.pb(s);
      sccid[s] = cnt;
      while(sz(st)){
        int u = st.back();
        st.pop_back();
        for(int v : rg[u]) if(sccid[v] == -1) sccid[v] = cnt, st.pb(v);
      }
      cnt++;
    }
    for(int &x : sccid) x = cnt - 1 - x;
    return cnt;
  }
};
