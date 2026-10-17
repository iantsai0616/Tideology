/**
 * Author: Tideology
 * Source: bqi343 DynaCon.h, adapted to RollbackUF
 * License: CC0
 * Description: Offline dynamic connectivity. Each edge is alive on a time interval [l, r);
 * run(f) calls f(t) for every time t < T with exactly the edges alive at t joined in uf.
 * Usage: map<pii, int> st; on add at t: st[e] = t; on remove at t: dc.add(st[e], t, e), st.erase(e);
 * at the end: for(auto [e, t0] : st) dc.add(t0, T, e); dc.run([\&](int t){ ... });
 * Time: $O((N + Q) \log Q \log N)$
 * Status: stress-tested against BFS
 */
#pragma once

#include "../data-structures/UnionFindRollback.h"

struct DynaCon {
  int L = 1; vector<vector<pii>> seg; RollbackUF uf;
  DynaCon(int n, int T) : uf(n){ while(L < T) L *= 2; seg.resize(2 * L); }
  void add(int l, int r, pii e){
    for(l += L, r += L; l < r; l /= 2, r /= 2){
      if(l & 1) seg[l++].push_back(e);
      if(r & 1) seg[--r].push_back(e);
    }
  }
  template<class Fn> void run(Fn f, int i = 1){
    int t = uf.time();
    for(auto [a, b] : seg[i]) uf.join(a, b);
    if(i >= L) f(i - L); else run(f, 2 * i), run(f, 2 * i + 1);
    uf.rollback(t);
  }
};
