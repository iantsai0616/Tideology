/**
 * Description: Minkowski sum of two ccw convex polygons.
 * Time: O(n+m)
 * Status: stress-tested
 */
#pragma once

#include "Point.h"

template<class P> void reorderPoly(vector<P>& p){
  rotate(p.begin(), min_element(all(p), [](P a, P b){
    return tie(a.y, a.x) < tie(b.y, b.x);
  }), p.end());
}
template<class P> vector<P> minkowski(vector<P> a, vector<P> b){
  if(a.empty() || b.empty()) return {};
  if(sz(a) == 1){ for(P& p : b) p = p + a[0]; return b; }
  if(sz(b) == 1){ for(P& p : a) p = p + b[0]; return a; }
  reorderPoly(a); reorderPoly(b);
  int n = sz(a), m = sz(b), i = 0, j = 0;
  a.pb(a[0]); a.pb(a[1]); b.pb(b[0]); b.pb(b[1]);
  vector<P> ans;
  while(i < n || j < m){
    ans.pb(a[i] + b[j]);
    auto x = a[i + 1] - a[i], y = b[j + 1] - b[j];
    auto c = x.cross(y);
    bool u = i < n && (j == m || c >= 0);
    bool v = j < m && (i == n || c <= 0);
    i += u; j += v;
  }
  return ans;
}
