/**
 * Author: Tideology
 * Source: https://cp-algorithms.com/algebra/primitive-root.html
 * License: CC0
 * Description: Smallest primitive root of $n$, or 0 if none exists
 * (they exist only for $n = 1, 2, 4, p^k, 2p^k$).
 * Time: Pollard-rho on $n$ and $\phi(n)$, plus a few modpow per candidate
 * Status: tested for all $n < 3000$, Library Checker primitive\_root
 */
#pragma once

#include "Factor.h"

ull primitiveRoot(ull n){
  if(n <= 4) return n - 1;
  auto f = factor(n); sort(all(f));
  int c2 = count(all(f), 2ULL);
  f.erase(unique(all(f)), f.end());
  if(c2 > 1 || sz(f) - (c2 > 0) != 1) return 0;
  ull ph = n;
  for(ull p : f) ph = ph / p * (p - 1);
  auto q = factor(ph); sort(all(q));
  q.erase(unique(all(q)), q.end());
  for(ull g = 2;; g++) if(__gcd(g, n) == 1){
    bool ok = 1;
    for(ull p : q) ok &= modpow(g, ph / p, n) != 1;
    if(ok) return g;
  }
}
