/**
 * Author: Simon Lindholm
 * Source: KACTL ClosestPair.h, adapted to pair points
 * License: CC0
 * Description: Indices of a closest pair of points ($n \ge 2$). Needs GeometryTemplate.
 * Time: O(n \log n)
 * Status: stress-tested, Library Checker closest\_pair
 */

pii closestPair(const vector<pll>& v){
  int n = sz(v), j = 0; vi id(n); iota(all(id), 0);
  sort(all(id), [&](int a, int b){ return v[a].Y < v[b].Y; });
  set<pair<pll, int>> S; pair<ll, pii> ret{LLONG_MAX, {0, 1}};
  for(int i : id){
    pll p = v[i]; ll d = 1 + (ll)sqrtl(ret.F);
    while(v[id[j]].Y <= p.Y - d) S.erase({v[id[j]], id[j]}), j++;
    auto lo = S.lower_bound({{p.X - d, LLONG_MIN}, -1});
    auto hi = S.upper_bound({{p.X + d, LLONG_MAX}, n});
    for(; lo != hi; ++lo) ret = min(ret, {abs2(lo->F - p), {lo->S, i}});
    if(!ret.F) break; // else O(n^2) on equal points
    S.insert({p, i});
  }
  return ret.S;
}
