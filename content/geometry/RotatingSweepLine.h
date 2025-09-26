/**
 * Author: Mattias de Zalenski
 * Date: 2002-11-04
 * Description: Magic formula for the volume of a polyhedron. Faces should point outwards.
 * Status: tested
 */
#pragma once
int cmp(pii a, pii b, bool same = true){
#define is_neg(k) (sgn(k.Y) < 0 || (sgn(k.Y) == 0 && sgn(k.X) < 0))
  int A = is_neg(a), B = is_neg(b);
  if(A != B)
    return A < B;
  if(sgn(cross(a, b)) == 0)
    return same ? abs2(a) < abs2(b) : -1;
  return sgn(cross(a, b)) > 0;
}
struct Event {
  pii d; int u, v;
  bool operator<(const Event &b) const {
    int ret = cmp(d, b.d, false);
    return ret == -1 ? false : ret; } // no tie-break
};
void rotatingSweepLine(const vector<pii> &p) {
  const int n = sz(p);
  vector<Event> e; e.reserve(n * (n - 1));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) // pos[i] < pos[j] when the event occurs
      if (i != j) e.pb(p[j] - p[i], i, j);
  sort(all(e));
  vector<int> ord(n), pos(n);
  iota(all(ord), 0);
  sort(all(ord), [&](int i, int j) { // initial order
      return p[i].Y != p[j].Y ? p[i].Y < p[j].Y : p[i].X < p[j].X; });
  for (int i = 0; i < n; i++) pos[ord[i]] = i;
  // initialize
  for (int i = 0, j = 0; i < sz(e); i = j) {
    // do something
    vector<pii> tmp;
    for (; j < sz(e) && !(e[i] < e[j]); j++)
      tmp.pb(pii(e[j].u, e[j].v));
    sort(all(tmp), [&](pii x, pii y){ 
        return pii(pos[x.F], pos[x.S]) < pii(pos[y.F], pos[y.S]); });
    for (auto [x, y] : tmp) // pos[x] + 1 == pos[y]
      tie(ord[pos[x]], ord[pos[y]], pos[x], pos[y]) = 
        make_tuple(ord[pos[y]], ord[pos[x]], pos[y], pos[x]);
  }
}