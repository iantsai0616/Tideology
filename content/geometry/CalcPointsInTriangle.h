/**
 * Description: Counts points strictly inside query triangles.
 * Time: O(n^2m) build, O(1) query
 * Status: stress-tested, Library Checker
 */
#pragma once

#include "Point.h"

typedef Point<ll> P;

struct PointsInTriangle {
  vector<P> a;
  vector<vi> left, on;
  vi pointL, pointM;
  PointsInTriangle(const vector<P>& a, const vector<P>& b) : a(a),
      left(sz(a), vi(sz(a))), on(sz(a), vi(sz(a))),
      pointL(sz(a)), pointM(sz(a)){
    rep(i, 0, sz(a)) for(P p : b) if(p.y == a[i].y){
      pointL[i] += p.x < a[i].x;
      pointM[i] += p.x == a[i].x;
    }
    rep(i, 0, sz(a)) rep(j, 0, sz(a)) if(a[i].y < a[j].y){
      P d = a[j] - a[i];
      for(P p : b) if(a[i].y < p.y && p.y < a[j].y){
        ll c = d.cross(p - a[i]);
        left[i][j] += c > 0;
        on[i][j] += c == 0;
      }
    }
  }
  int query(int x, int y, int z){
    auto cmp = [&](int i, int j){
      return tie(a[i].y, a[i].x) < tie(a[j].y, a[j].x);
    };
    if(cmp(y, x)) swap(x, y);
    if(cmp(z, y)) swap(y, z);
    if(cmp(y, x)) swap(x, y);
    ll d = (a[x] - a[z]).cross(a[y] - a[z]);
    if(!d) return 0;
    if(a[x].y == a[y].y)
      return left[y][z] - left[x][z] - on[x][z];
    if(a[y].y == a[z].y)
      return left[x][z] - left[x][y] - on[x][y];
    if(d < 0) return left[x][z] - left[y][z] - on[y][z] -
      left[x][y] - on[x][y] - pointL[y] - pointM[y];
    return left[x][y] + left[y][z] + pointL[y] -
      left[x][z] - on[x][z];
  }
};
