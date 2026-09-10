/**
 * Author: Simon Lindholm
 * Description: Mo ordering for half-open intervals. add/del get (index, end).
 * Time: O(N sqrt(Q)) moves
 * Status: stress-tested
 */
#pragma once

template<class Add, class Del, class Calc>
auto mo(vector<pii> Q, Add add, Del del, Calc calc, int blk=350){
  using T=decltype(calc());
  int L=0, R=0; vi ord(sz(Q)); vector<T> ans(sz(Q));
  iota(all(ord), 0);
  sort(all(ord), [&](int i, int j){
    auto [a, b]=Q[i]; auto [c, d]=Q[j];
    return pii(a/blk, b^-(a/blk&1)) < pii(c/blk, d^-(c/blk&1));
  });
  for(int i:ord){
    auto [l, r]=Q[i];
    while(L>l) add(--L, 0);
    while(R<r) add(R++, 1);
    while(L<l) del(L++, 0);
    while(R>r) del(--R, 1);
    ans[i]=calc();
  }
  return ans;
}

template<class Add, class Del, class Calc>
auto moTree(vector<array<int, 2>> Q, vector<vi> &g, Add add, Del del,
            Calc calc, int root=0, int blk=350){
  using T=decltype(calc());
  int n=sz(g), ti=n, pos[2]={root, root};
  vi ord(sz(Q)), I(n*2), L(n), R(n), in(n), par(n), tmp(n);
  vector<T> ans(sz(Q)); add(root, 0), in[root]=1;
  auto dfs=[&](auto self, int u, int p, int d)->void {
    par[u]=p; L[u]=ti;
    if(d) I[u]=ti++;
    for(int v:g[u]) if(v!=p) self(self, v, u, !d);
    if(!d) I[u]=ti++;
    R[u]=ti;
  };
  dfs(dfs, root, -1, 0); iota(all(ord), 0);
  sort(all(ord), [&](int i, int j){
    auto a=Q[i], b=Q[j];
    return pii(I[a[0]]/blk, I[a[1]]^-(I[a[0]]/blk&1)) <
           pii(I[b[0]]/blk, I[b[1]]^-(I[b[0]]/blk&1));
  });
  for(int qi:ord) rep(e, 0, 2){
    int &a=pos[e], b=Q[qi][e], k=0;
    auto step=[&](int c){
      if(in[c]) del(a, e), in[a]=0; else add(c, e), in[c]=1;
      a=c;
    };
    while(not(L[b]<=L[a] and R[a]<=R[b])) tmp[k++]=b, b=par[b];
    while(a!=b) step(par[a]);
    while(k) step(tmp[--k]);
    if(e) ans[qi]=calc();
  }
  return ans;
}
