/**
 * Author: Oleksandr Bacherikov, chilli
 * Source: KACTL HullDiameter.h (rotating calipers), adapted to pair points
 * License: Boost Software License
 * Description: Squared diameter (farthest pair) of a convex polygon given in CCW order
 * without collinear points.
 * Time: O(n)
 * Status: stress-tested, Library Checker furthest\_pair
 */

pair<ll, pii> hullDiameter(const vector<pll>& h){
  int n = sz(h), j = n < 2 ? 0 : 1;
  pair<ll, pii> res{0, {0, 0}};
  rep(i, 0, j) for(;; j = (j + 1) % n){
    res = max(res, {abs2(h[i] - h[j]), {i, j}});
    if(cross(h[(j + 1) % n] - h[j], h[i + 1] - h[i]) >= 0) break;
  }
  return res;
}
