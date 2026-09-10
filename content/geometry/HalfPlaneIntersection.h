/**
 * Description: Intersection of left sides of directed lines.
 * inf must bound every feasible point.
 * Time: O(n log n)
 * Status: stress-tested
 */
#pragma once

#include "Point.h"

typedef Point<double> P;
const double hpiEps = 1e-9;

struct HalfPlane {
  P p, d;
  double angle;
  HalfPlane(P a, P b) : p(a), d(b - a), angle(atan2(d.y, d.x)){}
  bool out(P q) const { return d.cross(q - p) < -hpiEps; }
  bool operator<(const HalfPlane& h) const { return angle < h.angle; }
};
P hpInter(const HalfPlane& a, const HalfPlane& b){
  return a.p + a.d*((b.p - a.p).cross(b.d)/a.d.cross(b.d));
}
vector<P> halfPlaneIntersection(vector<HalfPlane> h, double inf = 1e18){
  P box[] = {P(inf, inf), P(-inf, inf), P(-inf, -inf), P(inf, -inf)};
  rep(i, 0, 4) h.emplace_back(box[i], box[(i + 1) % 4]);
  sort(all(h));
  deque<HalfPlane> q;
  for(HalfPlane x : h){
    while(sz(q) > 1 && x.out(hpInter(q.back(), q[sz(q) - 2]))) q.pop_back();
    while(sz(q) > 1 && x.out(hpInter(q[0], q[1]))) q.pop_front();
    if(!q.empty() && abs(x.d.cross(q.back().d)) < hpiEps){
      if(x.d.dot(q.back().d) < 0) return {};
      if(x.out(q.back().p)) q.pop_back();
      else continue;
    }
    q.pb(x);
  }
  while(sz(q) > 2 && q[0].out(hpInter(q.back(), q[sz(q) - 2]))) q.pop_back();
  while(sz(q) > 2 && q.back().out(hpInter(q[0], q[1]))) q.pop_front();
  if(sz(q) < 3) return {};
  vector<P> ans;
  rep(i, 0, sz(q)) ans.pb(hpInter(q[i], q[(i + 1) % sz(q)]));
  return ans;
}
