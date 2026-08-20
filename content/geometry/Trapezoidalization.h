/**
 * Description: Sweep-line order of non-overlapping segments.
 * Time: O(log n) per event/query
 * Status: stress-tested
 */
#pragma once

#include "Point.h"

template<class T>
struct SweepLine {
  using P = Point<T>;
  struct Segment { P a, b; };
  struct Event {
    T x; int type, a, b;
    bool operator<(const Event& e) const {
      return tie(x, type, a, b) < tie(e.x, e.type, e.a, e.b);
    }
  };
  struct Cmp {
    const SweepLine* s;
    bool operator()(int a, int b) const {
      if(a == b) return false;
      T x = a < 0 ? s->curQ : s->getY(a);
      T y = b < 0 ? s->curQ : s->getY(b);
      if(abs(x - y) > s->eps) return x < y;
      if(a < 0 || b < 0) return a < 0;
      T u = s->slope(a), v = s->slope(b);
      return abs(u - v) > s->eps ? u < v : a < b;
    }
  };
  T curTime, eps, curQ = 0;
  vector<Segment> seg;
  set<Event> event;
  set<int, Cmp> sweep;
  vector<typename set<int, Cmp>::iterator> it;
  vector<typename set<Event>::iterator> crossEvent;
  vi active;
  SweepLine(T t, T eps, vector<Segment> seg) : curTime(t), eps(eps),
      seg(seg), sweep(Cmp{this}), it(sz(seg)), crossEvent(sz(seg)),
      active(sz(seg)){
    rep(i, 0, sz(seg)){
      if(tie(this->seg[i].b.x, this->seg[i].b.y) <
         tie(this->seg[i].a.x, this->seg[i].a.y))
        swap(this->seg[i].a, this->seg[i].b);
      if(this->seg[i].a.x <= t && t <= this->seg[i].b.x)
        active[i] = 1, it[i] = sweep.insert(i).F;
      else it[i] = sweep.end();
      if(t < this->seg[i].a.x) event.insert({this->seg[i].a.x, 0, i, -1});
      if(t <= this->seg[i].b.x) event.insert({this->seg[i].b.x, 2, i, -1});
    }
    fill(all(crossEvent), event.end());
    for(int i : sweep) update(i);
  }
  T getY(int i) const {
    Segment s = seg[i];
    if(abs(s.a.x - s.b.x) <= eps) return s.b.y;
    return ((s.b.x - curTime)*s.a.y + (curTime - s.a.x)*s.b.y)/
      (s.b.x - s.a.x);
  }
  T slope(int i) const {
    T dx = seg[i].b.x - seg[i].a.x;
    return abs(dx) <= eps ? numeric_limits<T>::infinity() :
      (seg[i].b.y - seg[i].a.y)/dx;
  }
  void cancel(int i){
    if(i >= 0 && crossEvent[i] != event.end()){
      event.erase(crossEvent[i]); crossEvent[i] = event.end();
    }
  }
  void update(int a){
    cancel(a);
    if(a < 0 || !active[a]) return;
    auto nx = next(it[a]);
    if(nx == sweep.end()) return;
    int b = *nx;
    P r = seg[a].b - seg[a].a, s = seg[b].b - seg[b].a;
    T d = r.cross(s);
    if(abs(d) <= eps) return;
    T k = (seg[b].a - seg[a].a).cross(s)/d;
    T x = seg[a].a.x + r.x*k;
    if(x <= curTime + eps || x >= min(seg[a].b.x, seg[b].b.x) - eps)
      return;
    crossEvent[a] = event.insert({x, 1, a, b}).F;
  }
  void process(T x, bool eraseEnd){
    vector<Event> now;
    while(!event.empty() && abs(event.begin()->x - x) <= eps &&
          (eraseEnd || event.begin()->type != 2)){
      auto p = event.begin();
      if(p->type == 1) crossEvent[p->a] = event.end();
      now.pb(*p); event.erase(p);
    }
    set<int> changed, start, finish, cand;
    for(Event e : now){
      if(e.type == 0) start.insert(e.a), changed.insert(e.a);
      if(e.type == 2) finish.insert(e.a), changed.insert(e.a);
      if(e.type == 1 && active[e.a] && active[e.b] &&
         next(it[e.a]) != sweep.end() && *next(it[e.a]) == e.b)
        changed.insert(e.a), changed.insert(e.b);
    }
    for(int v : changed) if(active[v]){
      if(it[v] != sweep.begin()){
        int u = *prev(it[v]); cand.insert(u); cancel(u);
      }
      cancel(v);
    }
    for(int v : changed) if(active[v]) sweep.erase(it[v]), it[v] = sweep.end();
    curTime = x;
    for(int v : start) active[v] = 1;
    for(int v : finish) active[v] = 0;
    for(int v : changed) if(active[v]) it[v] = sweep.insert(v).F;
    for(int v : changed) if(active[v]){
      cand.insert(v);
      if(it[v] != sweep.begin()) cand.insert(*prev(it[v]));
    }
    for(int v : cand) update(v);
  }
  void setTime(T t, bool eraseEnd = false){
    assert(t + eps >= curTime);
    while(!event.empty() && event.begin()->x <= t + eps){
      T x = event.begin()->x;
      bool end = eraseEnd || x < t - eps;
      if(!end && event.begin()->type == 2) break;
      process(x, end);
    }
    curTime = t;
  }
  T nextEvent() const {
    return event.empty() ? numeric_limits<T>::infinity() : event.begin()->x;
  }
  int lowerBound(T y){
    curQ = y;
    auto p = sweep.lower_bound(-1);
    return p == sweep.end() ? -1 : *p;
  }
};
