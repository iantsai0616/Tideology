/**
 * Description: Exact half-plane intersection for ax+by+c<=0.
 * inf must bound every feasible point.
 * Time: O(n log n)
 * Status: stress-tested
 */
#pragma once

#include "PolarAngleComp.h"

typedef Point<long double> DP;

struct IHalfPlane {
  ll a, b, c;
  IHalfPlane(ll a, ll b, ll c) : a(a), b(b), c(c){}
  P dir() const { return P(a, b); }
};
bool iLess(IHalfPlane a, IHalfPlane b){
  int c = polarCmp(a.dir(), b.dir(), false);
  if(c != -1) return c;
  return (__int128)(abs(b.a) + abs(b.b))*a.c >
         (__int128)(abs(a.a) + abs(a.b))*b.c;
}
bool iInside(IHalfPlane l, IHalfPlane a, IHalfPlane b){
  __int128 d = (__int128)a.a*b.b - (__int128)a.b*b.a;
  __int128 x = (__int128)a.c*b.a - (__int128)b.c*a.a;
  __int128 y = (__int128)a.c*b.b - (__int128)b.c*a.b;
  __int128 v = x*l.b - y*l.a + d*l.c;
  return d > 0 ? v <= 0 : v >= 0;
}
DP iInter(IHalfPlane a, IHalfPlane b){
  long double d = (long double)a.a*(long double)b.b -
    (long double)a.b*(long double)b.a;
  return DP(((long double)b.c*(long double)a.b -
             (long double)a.c*(long double)b.b)/d,
            ((long double)a.c*(long double)b.a -
             (long double)b.c*(long double)a.a)/d);
}
vector<DP> integerHalfPlaneIntersection(vector<IHalfPlane> h,
    ll inf = (1LL << 60)){
  h.pb({1, 0, -inf}); h.pb({-1, 0, -inf});
  h.pb({0, 1, -inf}); h.pb({0, -1, -inf});
  sort(all(h), iLess);
  deque<IHalfPlane> q;
  for(IHalfPlane x : h){
    while(sz(q) > 1 && !iInside(x, q[sz(q) - 2], q.back())) q.pop_back();
    while(sz(q) > 1 && !iInside(x, q[0], q[1])) q.pop_front();
    if(!q.empty() && polarCmp(x.dir(), q.back().dir(), false) == -1)
      continue;
    if(!q.empty() && !x.dir().cross(q.back().dir())) return {};
    q.pb(x);
  }
  while(sz(q) > 2 && !iInside(q[0], q[sz(q) - 2], q.back())) q.pop_back();
  while(sz(q) > 2 && !iInside(q.back(), q[0], q[1])) q.pop_front();
  if(sz(q) < 3) return {};
  vector<DP> ans;
  rep(i, 0, sz(q)) ans.pb(iInter(q[i], q[(i + 1) % sz(q)]));
  return ans;
}
