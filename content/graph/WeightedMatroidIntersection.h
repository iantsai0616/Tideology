/**
 * Author: Hashiryo
 * Source: https://hashiryo.github.io/Library/optimization/matroid_intersection.html
 * Description: Maximum-cardinality common independent set, breaking ties by
 *  maximum weight.
 * Usage:
 *  auto m1 = tuple(build1, add1, exchange1);
 *  auto m2 = tuple(build2, add2, exchange2);
 *  WeightedMatroidIntersection mi(n, m1, m2);
 *  auto [weight, I] = mi.calc(w);
 * Oracle:
 *  build(I): preprocess the current independent set I.
 *  add(e): test if I+e is independent, where e is not in I.
 *  exchange(e, f): test if I-e+f is independent, where e is in I and f is not.
 * Time: O(RB + NR^2(Q + log N)). Extra space: O(N).
 *  N = elements, R = answer size, B/Q = build/oracle time.
 * Status: stress-tested
 */
#pragma once

template <class M1, class M2> struct WeightedMatroidIntersection{
  int n;
  M1 m1; M2 m2;
  WeightedMatroidIntersection(int n, M1 m1, M2 m2)
    : n(n), m1(m1), m2(m2){}
  template <class T> pair<T, vi> calc(const vector<T> &w){
    auto &[build1, add1, exchange1] = m1;
    auto &[build2, add2, exchange2] = m2;
    assert(sz(w) == n);
    if(!n) return {T{}, {}};
    using D = __int128_t;
    D mx = *max_element(all(w)), neg = -(D(1) << 120);
    vector<D> cost(n), d(n);
    rep(i, 0, n) cost[i] = (D(w[i]) - mx) * (n + 1);
    vector<bool> in(n);
    vi ans;
    while(1){
      vi I[2], pre(n, -1);
      rep(i, 0, n) I[in[i]].pb(i);
      build1(I[1]); build2(I[1]);
      fill(all(d), neg);
      priority_queue<pair<D, int>> pq;
      for(int u : I[0]) if(add1(u)){
        d[u] = cost[u] - 1;
        pq.push({d[u], u});
      }
      int t = -1;
      while(!pq.empty()){
        auto [du, u] = pq.top(); pq.pop();
        if(du != d[u]) continue;
        if(!in[u] && add2(u)){
          t = u;
          break;
        }
        for(int v : I[!in[u]]){
          bool ok = in[u] ? exchange1(u, v) : exchange2(v, u);
          D nd = du + (in[u] ? cost[v] : -cost[v]) - 1;
          if(ok && nd > d[v]){
            d[v] = nd; pre[v] = u;
            pq.push({nd, v});
          }
        }
      }
      if(t == -1){
        ans = I[1];
        break;
      }
      for(int u = t; u != -1; u = pre[u]) in[u] = !in[u];
    }
    T sum{};
    for(int u : ans) sum += w[u];
    return {sum, ans};
  }
};
