/**
 * Description: Binary lifting for upward jumps and LCA.
 * The root must be its own parent.
 * Time: O(N log N) build, O(log N) query
 * Status: stress-tested
 */
#pragma once

struct BinaryLifting{
  int n, lg = 1;
  vector<vi>up;
  vi dep;
  BinaryLifting(const vi &par, const vi &depth): n(sz(par)), dep(depth){
    while((1LL << lg) < n) lg++;
    up.assign(lg, par);
    rep(i, 1, lg) rep(v, 0, n) up[i][v] = up[i - 1][up[i - 1][v]];
  }
  int jump(int u, int k){
    rep(i, 0, lg) if(k >> i & 1) u = up[i][u];
    return u;
  }
  int lca(int u, int v){
    if(dep[u] < dep[v]) swap(u, v);
    u = jump(u, dep[u] - dep[v]);
    if(u == v) return u;
    for(int i = lg; i--;){
      if(up[i][u] != up[i][v]) u = up[i][u], v = up[i][v];
    }
    return up[0][u];
  }
};
