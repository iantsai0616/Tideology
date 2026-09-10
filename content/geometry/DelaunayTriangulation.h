/**
 * Description: O(N^2) Delaunay triangulation.
 * No three points may be collinear and no four cocircular.
 * Status: stress-tested
 */
#pragma once

#include "Point.h"
#include "3dHull.h"

template<class P>
vector<array<int, 3>> delaunay(const vector<P> &ps){
  vector<array<int, 3>>ans;
  if(sz(ps) == 3){
    int d = ps[0].cross(ps[1], ps[2]) < 0;
    ans.pb({0, 1 + d, 2 - d});
  }
  vector<P3>p3;
  for(P p : ps) p3.emplace_back(p.x, p.y, p.dist2());
  if(sz(ps) > 3) for(auto t : hull3d(p3)){
    P3 z = (p3[t.b] - p3[t.a]).cross(p3[t.c] - p3[t.a]);
    if(z.dot(P3(0, 0, 1)) < 0) ans.pb({t.a, t.c, t.b});
  }
  return ans;
}
