/**
 * Description: Minimum vertex cover in a bipartite graph.
 * Returns left vertices as u and right vertices as n+v.
 * Time: O(E sqrt(V))
 * Status: stress-tested
 */
#pragma once

#include "hopcroftKarp.h"

struct MinimumVertexCover : HopcroftKarp{
  using HopcroftKarp::HopcroftKarp;
  vi cover(){
    auto [cnt, mt] = calc();
    vector<bool>left(n, 1), seen(m);
    for(int u : mt) if(u != -1) left[u] = 0;
    vi q, ans;
    rep(i, 0, n) if(left[i]) q.pb(i);
    while(sz(q)){
      int u = q.back();
      q.pop_back();
      left[u] = 1;
      for(int v : g[u]) if(!seen[v] and mt[v] != -1){
        seen[v] = 1;
        q.pb(mt[v]);
      }
    }
    rep(i, 0, n) if(!left[i]) ans.pb(i);
    rep(i, 0, m) if(seen[i]) ans.pb(n + i);
    assert(sz(ans) == cnt);
    return ans;
  }
};
