/**
 * Author: Hashiryo, UFMG
 * Source: https://hashiryo.github.io/Library/optimization/matroid_intersection.html,
 *  https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Primitivas/matroid.cpp
 * Description: Maximum-cardinality common independent set of two matroids.
 * Usage:
 *  auto m1 = tuple(build1, add1, exchange1);
 *  auto m2 = tuple(build2, add2, exchange2);
 *  MatroidIntersection mi(n, m1, m2);
 *  vi I = mi.calc();
 * Oracle:
 *  build(I): preprocess the current independent set I.
 *  add(e): test if I+e is independent, where e is not in I.
 *  exchange(e, f): test if I-e+f is independent, where e is in I and f is not.
 * Time: O(RB + NR^2Q). Extra space: O(N).
 *  N = elements, R = answer size, B/Q = build/oracle time.
 * Status: stress-tested
 */
#pragma once

template <class M1, class M2> struct MatroidIntersection{
  int n;
  M1 m1; M2 m2;
  MatroidIntersection(int n, M1 m1, M2 m2) : n(n), m1(m1), m2(m2){}
  vi calc(){
    auto &[build1, add1, exchange1] = m1;
    auto &[build2, add2, exchange2] = m2;
    vector<bool> in(n);
    while(1){
      vi I[2], pre(n, -2);
      vector<bool> sink(n);
      rep(i, 0, n) I[in[i]].pb(i);
      build1(I[1]); build2(I[1]);
      queue<int> q;
      for(int u : I[0]){
        sink[u] = add2(u);
        if(add1(u)) pre[u] = -1, q.push(u);
      }
      int t = -1;
      while(!q.empty() && t == -1){
        int u = q.front(); q.pop();
        if(!in[u] && sink[u]){
          t = u;
          break;
        }
        for(int v : I[!in[u]]){
          if(pre[v] != -2) continue;
          bool ok = in[u] ? exchange1(u, v) : exchange2(v, u);
          if(ok) pre[v] = u, q.push(v);
        }
      }
      if(t == -1) return I[1];
      for(int u = t; u != -1; u = pre[u]) in[u] = !in[u];
    }
  }
};
