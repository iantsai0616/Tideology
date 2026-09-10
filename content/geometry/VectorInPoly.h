/**
 * Description: Tests whether cur->p lies in the polygon angle at cur.
 * Time: O(1)
 * Status: tested
 */
#pragma once

#include "Point.h"

typedef Point<ll> P;

bool betweenAngle(P a, P b, P c, P p, int strict){
  return a.cross(b, p) >= strict && a.cross(p, c) >= strict;
}
bool inCone(P prv, P cur, P nxt, P p, int strict = true){
  if(cur.cross(nxt, prv) >= 0)
    return betweenAngle(cur, nxt, prv, p, strict);
  return !betweenAngle(cur, prv, nxt, p, !strict);
}
