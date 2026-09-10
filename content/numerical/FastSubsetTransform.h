/**
 * Author: Lucian Bicsi
 * Date: 2015-06-25
 * License: GNU Free Documentation License 1.2
 * Source: csacademy
 * Description: Transform to a basis with fast convolutions of the form
 * $\displaystyle c[z] = \sum\nolimits_{z = x \oplus y} a[x] \cdot b[y]$,
 * where $\oplus$ is one of AND, OR, XOR. The size of $a$ must be a power of two.
 * Time: O(N \log N)
 * Status: stress-tested
 */
#pragma once

void FST(vi& a, bool inv, int mod = 0){
  for(int n = sz(a), step = 1; step < n; step *= 2){
    for(int i = 0; i < n; i += 2 * step) rep(j, i, i+step){
      int &u = a[j], &v = a[j + step], x = u, y = v;
      if(mod){
        if(inv){ u = y - x; if(u < 0) u += mod; v = x; }
        else { u = y; v = x + y; if(v >= mod) v -= mod; }
      }
      else tie(u, v) = inv ? pii(y - x, x) : pii(y, x + y); // AND
        // inv ? pii(v, u - v) : pii(u + v, u); // OR /// include-line
        // pii(u + v, u - v);                   // XOR /// include-line
    }
  }
  // if(inv) for(int& x : a) x /= sz(a); // XOR only /// include-line
}
vi conv(vi a, vi b, int mod = 0){
  FST(a, 0, mod); FST(b, 0, mod);
  rep(i, 0, sz(a)) a[i] = mod ? (int)((ll)a[i]*b[i] % mod) : a[i]*b[i];
  FST(a, 1, mod); return a;
}
