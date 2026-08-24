/**
 * Author: Per Austrin
 * Description: Finds the distinct real roots of a polynomial in [xmin, xmax].
 * Time: O(n^2 log(1/epsilon))
 */
#pragma once

#include "Polynomial.h"

vector<double> polyRoots(Poly p, double xmin, double xmax){
  while(sz(p.a) > 1 && abs(p.a.back()) < 1e-14) p.a.pop_back();
  if(sz(p.a) <= 1) return {};
  if(sz(p.a) == 2){
    double x = -p.a[0]/p.a[1];
    return xmin <= x && x <= xmax ? vector<double>{x} : vector<double>{};
  }
  Poly der = p; der.diff();
  auto at = polyRoots(der, xmin, xmax);
  at.insert(at.begin(), xmin); at.pb(xmax);
  vector<double> ret;
  auto add = [&](double x){
    if(abs(p(x)) < 1e-8 && (ret.empty() || abs(ret.back()-x) > 1e-7)) ret.pb(x);
  };
  rep(i, 0, sz(at)){
    add(at[i]);
    if(i+1 == sz(at)) break;
    double l = at[i], r = at[i+1], fl = p(l), fr = p(r);
    if((fl > 0) == (fr > 0) || abs(fl) < 1e-8 || abs(fr) < 1e-8) continue;
    rep(it, 0, 80){
      double m = (l+r)/2, fm = p(m);
      if((fl > 0) == (fm > 0)) l = m, fl = fm;
      else r = m;
    }
    add((l+r)/2);
  }
  return ret;
}
