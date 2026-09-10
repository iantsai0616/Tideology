/**
 * Author: chilli, pajenegod
 * Date: 2020-02-20
 * License: CC0
 * Source: Folklore
 * Description: Data structure for computing lowest common ancestors in a tree
 * (with 0 as root). C should be an adjacency list of the tree, either directed
 * or undirected.
 * Time: $O(N \log N + Q)$
 * Status: stress-tested
 */
#pragma once

#include "../data-structures/RMQ.h"

struct LCA {
  int T = 0;
  vi time, path, ret;
  RMQ<int> rmq;

  LCA(vector<vi>& C) : time(sz(C)), rmq((build(C), ret)){}
  void build(vector<vi>& C){
    vi par(sz(C), -1), st = {0};
    while(!st.empty()){
      int v = st.back(); st.pop_back();
      if(v) path.pb(par[v]), ret.pb(time[par[v]]);
      time[v] = T++;
      for(int i = sz(C[v]); i--;){
        int y = C[v][i];
        if(y != par[v]) par[y] = v, st.pb(y);
      }
    }
  }

  int lca(int a, int b){
    if(a == b) return a;
    tie(a, b) = minmax(time[a], time[b]);
    return path[rmq.query(a, b)];
  }
  //dist(a, b){return depth[a] + depth[b] - 2*depth[lca(a, b)];}
};
