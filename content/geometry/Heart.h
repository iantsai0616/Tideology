/**
 * Description: Triangle circumcenter, incenter, centroid and orthocenter.
 * Time: O(1)
 * Status: tested
 */
#pragma once

#include "Point.h"

typedef Point<double> P;

P circumcenter(P a, P b, P c){
  P x = b - a, y = c - a;
  return a + (y*x.dist2() - x*y.dist2()).perp()/y.cross(x)/2;
}
P incenter(P a, P b, P c){
  double x = (b - c).dist(), y = (a - c).dist(), z = (a - b).dist();
  return (a*x + b*y + c*z)/(x + y + z);
}
P centroid(P a, P b, P c){ return (a + b + c)/3; }
P orthocenter(P a, P b, P c){
  return a + b + c - circumcenter(a, b, c)*2;
}
