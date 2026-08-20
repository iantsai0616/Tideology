/**
 * Description: Orders nonzero integer vectors counter-clockwise from +x.
 * Status: tested
 */
#pragma once

#include "Point.h"

typedef Point<ll> P;

// -1 if parallel and same=false, otherwise returns a<b.
int polarCmp(P a, P b, bool same = true){
  auto neg = [](P p){ return p.y < 0 || (p.y == 0 && p.x < 0); };
  int x = neg(a), y = neg(b);
  if(x != y) return x < y;
  __int128 c = (__int128)a.x*b.y - (__int128)a.y*b.x;
  if(!c) return same ? a.dist2() < b.dist2() : -1;
  return c > 0;
}
