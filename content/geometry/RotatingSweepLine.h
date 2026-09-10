/**
 * Description: Maintains the order of points while a directed line rotates.
 * run(f) calls f(direction, order, position) before each equal-angle swap.
 * Time: O(n^2 log n)
 * Status: stress-tested
 */
#pragma once

#include "PolarAngleComp.h"

struct RotatingSweepLine {
  struct Event { P d; int u, v; };
  vector<P> p;
  vector<Event> event;
  vi ord, pos;
  RotatingSweepLine(const vector<P>& p) : p(p), ord(sz(p)), pos(sz(p)){
    event.reserve(sz(p)*(sz(p) - 1));
    rep(i, 0, sz(p)) rep(j, 0, sz(p)) if(i != j)
      event.pb({p[j] - p[i], i, j});
    sort(all(event), [](Event a, Event b){ return polarCmp(a.d, b.d); });
    reset();
  }
  void reset(){
    iota(all(ord), 0);
    sort(all(ord), [&](int i, int j){
      return tie(p[i].y, p[i].x) < tie(p[j].y, p[j].x);
    });
    rep(i, 0, sz(p)) pos[ord[i]] = i;
  }
  template<class F> void run(F f){
    reset();
    for(int i = 0, j = 0; i < sz(event); i = j){
      f(event[i].d, ord, pos);
      vector<pii> cur;
      for(;j < sz(event) && polarCmp(event[i].d, event[j].d, false) == -1;j++)
        cur.pb({event[j].u, event[j].v});
      sort(all(cur), [&](pii a, pii b){
        return pii(pos[a.F], pos[a.S]) < pii(pos[b.F], pos[b.S]);
      });
      for(auto [x, y] : cur){
        swap(ord[pos[x]], ord[pos[y]]);
        swap(pos[x], pos[y]);
      }
    }
  }
};
