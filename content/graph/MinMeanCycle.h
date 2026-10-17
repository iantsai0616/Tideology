/**
 * Author: Tideology
 * Source: Karp, A characterization of the minimum cycle mean in a digraph (1978)
 * License: CC0
 * Description: Minimum mean cycle of a directed graph with edges {u, v, w}, as an
 * unreduced fraction {num, den}; den = 0 if there is no cycle. Exact for integer weights.
 * Time: O(VE) time, $O(V^2)$ memory
 * Status: stress-tested against cycle enumeration
 */
#pragma once

pair<ll, ll> karp(int n, const vector<array<ll, 3>>& E){
  const ll INF = LLONG_MAX / 4;
  vector<vector<ll>> d(n + 1, vector<ll>(n, INF));
  d[0].assign(n, 0);
  rep(k, 0, n) for(auto [u, v, w] : E)
    if(d[k][u] < INF) d[k + 1][v] = min(d[k + 1][v], d[k][u] + w);
  auto less = [](pair<ll, ll> a, pair<ll, ll> b){
    return (__int128)a.first * b.second < (__int128)b.first * a.second; };
  pair<ll, ll> best{1, 0};
  rep(v, 0, n) if(d[n][v] < INF){
    pair<ll, ll> mx{d[n][v], n};
    rep(k, 1, n) if(d[k][v] < INF)
      mx = max(mx, pair<ll, ll>{d[n][v] - d[k][v], n - k}, less);
    if(!best.second || less(mx, best)) best = mx;
  }
  return best;
}
