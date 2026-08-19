/**
 * Description: Offline compressed 2D Fenwick tree for point-add/prefix-sum.
 * Time: O(log^2 N)
 * Status: stress-tested
 */
#pragma once

#include "FenwickTree.h"

struct FT2{
  vector<vi>ys;
  vector<FT>ft;
  FT2(int n, const vector<pii> &points): ys(n){
    for(auto [x, y] : points)
      for(; x < n; x |= x + 1) ys[x].pb(y);
    for(vi &v : ys){
      sort(all(v));
      v.erase(unique(all(v)), v.end());
      ft.emplace_back(sz(v));
    }
  }
  int ind(int x, int y){
    return lower_bound(all(ys[x]), y) - ys[x].begin();
  }
  void update(int x, int y, ll dif){
    for(; x < sz(ys); x |= x + 1) ft[x].update(ind(x, y), dif);
  }
  ll query(int x, int y){
    ll ans = 0;
    for(; x; x &= x - 1) ans += ft[x - 1].query(ind(x - 1, y));
    return ans;
  }
};
