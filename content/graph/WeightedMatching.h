/**
 * Author: Jeremy Lim, Joshua Andersson
 * Description: Minimum-cost matching of every row to a distinct column. N<=M.
 * Time: O(N^2 M)
 * Status: stress-tested
 */
#pragma once

template<class T> pair<T, vi> hungarian(const vector<vector<T>> &C){
  int i = sz(C), m = i ? sz(C[0]) : 0, c = 0, s, r;
  vector<T> dist(m), pot(m); vi match(i), rev(m, -1), cols(m), pre(m);
  T d = 0, nd, cost = 0;
  while(i--){
    rep(j, 0, m) dist[j] = C[i][j], cols[j] = j, pre[j] = i;
    for(s = 0;;){
      rep(j, s, m){
        c = cols[j], nd = dist[c] - pot[c];
        if(j == s or d > nd) d = nd, swap(cols[s], cols[j]);
      }
      if((r = rev[c = cols[s++]]) == -1) break;
      rep(j, 0, m) if(dist[j] > (nd = C[r][j] - C[r][c] + dist[c]))
        dist[j] = nd, pre[j] = r;
    }
    cost += dist[c];
    while(s--) pot[cols[s]] = dist[cols[s]] - d;
    for(; r != i; swap(c, match[r])) r = rev[c] = pre[c];
  }
  return {cost, match};
}
