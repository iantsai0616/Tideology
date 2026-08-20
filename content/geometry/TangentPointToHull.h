/**
 * Description: Tangent vertices from an external point to a ccw convex hull.
 * Time: O(log n)
 * Status: stress-tested
 */
#pragma once

#include "Point.h"

typedef Point<ll> P;

template<class F> int extremeVertex(const vector<P>& p, F dir){
  int n = sz(p), l = 0, ls;
  auto cmp = [&](int i, int j){
    return sgn(dir(p[j]).cross(p[j] - p[i]));
  };
  auto extreme = [&](int i, int& s){
    s = cmp((i + 1) % n, i);
    return s >= 0 && cmp(i, (i + n - 1) % n) < 0;
  };
  int r = extreme(0, ls) ? 1 : n;
  while(l + 1 < r){
    int m = (l + r) / 2, ms;
    if(extreme(m, ms)) return m;
    if(ls != ms ? ls < ms : ls == cmp(l, m)) r = m;
    else l = m, ls = ms;
  }
  return l;
}
pii hullTangents(const vector<P>& p, P q){
  assert(sz(p) >= 3);
  return {
    extremeVertex(p, [&](P x){ return x - q; }),
    extremeVertex(p, [&](P x){ return q - x; })
  };
}
