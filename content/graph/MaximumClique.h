/**
 * Author: chilli, SJTU, Janez Konc
 * Description: Fast maximum clique for a symmetric bitset graph, n <= 200.
 * Status: stress-tested
 */
#pragma once

typedef vector<bitset<200>> vb;
struct Maxclique {
  double limit=.025, pk=0;
  struct Vertex { int i, d=0; };
  using vv=vector<Vertex>;
  vb e; vv V; vector<vi> C; vi qmax, q, steps, old;
  void init(vv &r){
    if(r.empty()) return;
    for(auto &v:r) v.d=0;
    for(auto &v:r) for(auto u:r) v.d+=e[v.i][u.i];
    sort(all(r), [](auto a, auto b){return a.d>b.d;});
    int mx=r[0].d;
    rep(i, 0, sz(r)) r[i].d=min(i, mx)+1;
  }
  void expand(vv &R, int lev=1){
    steps[lev]+=steps[lev-1]-old[lev]; old[lev]=steps[lev-1];
    while(sz(R)){
      if(sz(q)+R.back().d<=sz(qmax)) return;
      q.pb(R.back().i); vv T;
      for(auto v:R) if(e[R.back().i][v.i]) T.pb({v.i});
      if(sz(T)){
        if((double)steps[lev]++/++pk<limit) init(T);
        int j=0, mx=1, mn=max<int>(sz(qmax)-sz(q)+1, 1);
        C[1].clear(), C[2].clear();
        for(auto v:T){
          int k=1;
          while(any_of(all(C[k]), [&](int i){return e[v.i][i];})) ++k;
          if(k>mx) mx=k, C[mx+1].clear();
          if(k<mn) T[j++].i=v.i;
          C[k].pb(v.i);
        }
        if(j) T[j-1].d=0;
        rep(k, mn, mx+1) for(int i:C[k]) T[j].i=i, T[j++].d=k;
        expand(T, lev+1);
      } else if(sz(q)>sz(qmax)) qmax=q;
      q.pop_back(), R.pop_back();
    }
  }
  vi maxClique(){ if(V.empty()) return {}; init(V), expand(V); return qmax; }
  Maxclique(vb e):e(e), C(sz(e)+2), steps(C.size()), old(steps){
    rep(i, 0, sz(e)) V.pb({i});
  }
};
