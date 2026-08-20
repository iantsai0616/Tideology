/**
 * Description: Tests whether q is strictly inside the circumcircle of p.
 * Time: O(1)
 * Status: tested
 */
#pragma once

#include "Point.h"

typedef Point<ll> P;

bool inCircle(const array<P, 3>& p, P q){
  __int128 det = 0;
  rep(i, 0, 3){
    P a = p[(i + 1) % 3] - q, b = p[(i + 2) % 3] - q;
    __int128 d = (__int128)p[i].x*p[i].x + (__int128)p[i].y*p[i].y -
      (__int128)q.x*q.x - (__int128)q.y*q.y;
    det += d*((__int128)a.x*b.y - (__int128)a.y*b.x);
  }
  __int128 ori = (__int128)(p[1].x - p[0].x)*(p[2].y - p[0].y) -
    (__int128)(p[1].y - p[0].y)*(p[2].x - p[0].x);
  return ori > 0 ? det > 0 : det < 0;
}
