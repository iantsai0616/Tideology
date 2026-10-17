/**
 * Author: Tideology
 * Source: Ji Ruyi's segment tree beats, https://codeforces.com/blog/entry/57319
 * License: CC0
 * Description: Range chmin, chmax, add, and range sum on $[l, r)$.
 * Usage: Beats t(v); t.upd(0, l, r, x); // 0: chmin, 1: chmax, 2: add
 * t.sum(l, r);
 * Time: amortized $O(\log^2 N)$ per operation
 * Status: stress-tested, Library Checker range\_chmin\_chmax\_add\_range\_sum
 */
#pragma once

struct Beats {
  const ll INF = 4e18;
  struct Node { ll s, a, mx, mx2, cx, mn, mn2, cn; };
  int n; vector<Node> t;
  Beats(const vector<ll>& v) : n(sz(v)), t(4 * n){ build(1, 0, n, v); }
  void pull(int x){
    Node &p = t[x], &l = t[2*x], &r = t[2*x+1];
    p.s = l.s + r.s;
    p.mx = max(l.mx, r.mx), p.mn = min(l.mn, r.mn);
    p.mx2 = max(l.mx == p.mx ? l.mx2 : l.mx, r.mx == p.mx ? r.mx2 : r.mx);
    p.mn2 = min(l.mn == p.mn ? l.mn2 : l.mn, r.mn == p.mn ? r.mn2 : r.mn);
    p.cx = (l.mx == p.mx) * l.cx + (r.mx == p.mx) * r.cx;
    p.cn = (l.mn == p.mn) * l.cn + (r.mn == p.mn) * r.cn;
  }
  void build(int x, int l, int r, const vector<ll>& v){
    if(r - l == 1){ t[x] = {v[l], 0, v[l], -INF, 1, v[l], INF, 1}; return; }
    int m = (l + r) / 2;
    build(2*x, l, m, v), build(2*x+1, m, r, v); t[x].a = 0; pull(x);
  }
  void addT(int x, int len, ll v){
    Node &p = t[x]; p.s += v * len, p.a += v, p.mx += v, p.mn += v;
    if(p.mx2 != -INF) p.mx2 += v;
    if(p.mn2 != INF) p.mn2 += v;
  }
  void minT(int x, ll v){ // requires mx2 < v
    Node &p = t[x]; if(p.mx <= v) return;
    p.s += (v - p.mx) * p.cx;
    if(p.mn == p.mx) p.mn = v; else if(p.mn2 == p.mx) p.mn2 = v;
    p.mx = v;
  }
  void maxT(int x, ll v){ // requires mn2 > v
    Node &p = t[x]; if(p.mn >= v) return;
    p.s += (v - p.mn) * p.cn;
    if(p.mx == p.mn) p.mx = v; else if(p.mx2 == p.mn) p.mx2 = v;
    p.mn = v;
  }
  void push(int x, int l, int r){
    int m = (l + r) / 2;
    if(t[x].a) addT(2*x, m - l, t[x].a), addT(2*x+1, r - m, t[x].a), t[x].a = 0;
    rep(c, 2*x, 2*x+2) minT(c, t[x].mx), maxT(c, t[x].mn);
  }
  void upd(int op, int a, int b, ll v, int x = 1, int l = 0, int r = -1){
    if(r < 0) r = n;
    if(b <= l || r <= a || (op == 0 && t[x].mx <= v) || (op == 1 && t[x].mn >= v)) return;
    if(a <= l && r <= b && (op == 2 || (op == 0 && t[x].mx2 < v) || (op == 1 && t[x].mn2 > v)))
      return op == 2 ? addT(x, r - l, v) : op ? maxT(x, v) : minT(x, v);
    push(x, l, r); int m = (l + r) / 2;
    upd(op, a, b, v, 2*x, l, m), upd(op, a, b, v, 2*x+1, m, r); pull(x);
  }
  ll sum(int a, int b, int x = 1, int l = 0, int r = -1){
    if(r < 0) r = n;
    if(b <= l || r <= a) return 0;
    if(a <= l && r <= b) return t[x].s;
    push(x, l, r); int m = (l + r) / 2;
    return sum(a, b, 2*x, l, m) + sum(a, b, 2*x+1, m, r);
  }
};
