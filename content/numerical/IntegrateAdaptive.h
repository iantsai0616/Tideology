/**
 * Author: Simon Lindholm
 * Description: Adaptive Simpson integration.
 * Usage: double ans = quad(l, r, [](double x){ return f(x); });
 * Status: stress-tested
 */
#pragma once

typedef double d;
template<class F> d simpson(F &f, d a, d b){
  return (f(a) + 4*f((a+b)/2) + f(b)) * (b-a) / 6;
}
template<class F> d rec(F &f, d a, d b, d eps, d s){
  d c = (a+b)/2, l = simpson(f, a, c), r = simpson(f, c, b);
  if(abs(l+r-s) <= 15*eps or b-a < 1e-10)
    return l+r+(l+r-s)/15;
  return rec(f, a, c, eps/2, l) + rec(f, c, b, eps/2, r);
}
template<class F> d quad(d a, d b, F f, d eps = 1e-8){
  return rec(f, a, b, eps, simpson(f, a, b));
}
