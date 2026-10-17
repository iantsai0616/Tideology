/**
 * Author: std\_abs codebook
 * Description: Rarely needed polynomial operations split off Operation.h (not printed).
 * SamplingShift: given f(0..n-1), returns f(c..c+m-1). power\_proj: returns
 * $\sum_j w_j [x^j] f^i$ for $i = 0..m$. Both need fac[i] = i!, facp[i] = 1/i!.
 */
#pragma once

#include "Operation.h"

vector<ll> SamplingShift(vector<ll> a, ll c, int m){
  // given f(0), f(1), ..., f(n - 1)
  // return f(c), f(c + 1), ..., f(c + m - 1)
  int n = sz(a); // 4d649d
  for (int i = 0; i < n; ++i) a[i] = mul(a[i],facp[i]);
  Poly b(n);
  for (int i = 0; i < n; ++i) {
    b[i] = facp[i];
    if (i & 1) b[i] = sub(0, b[i]);
  }
  a = Mul(a, b, n);
  for (int i = 0; i < n; ++i) a[i] = mul(a[i], fac[i]);
  reverse(all(a));
  int w = 1;
  for (int i = 0; i < n; ++i)
    b[i] = mul(facp[i], w), w = mul(w, sub(c, i));
  a = Mul(a, b, n);
  reverse(all(a));
  for (int i = 0; i < n; ++i) a[i] = mul(a[i],facp[i]);
  a.resize(m), b.resize(m);
  for (int i = 0; i < m; ++i) b[i] = facp[i];
  a = Mul(a, b, m);
  for (int i = 0; i < m; ++i) a[i] = mul(a[i], fac[i]);
  return a;
} // e28e16
Poly power_proj(vector<ll> w, Poly f, int m) {
  // return sum_j w_j[x^j]f^i for i=0,1,...,m
  int n = 1;
  while (n < sz(f)) n <<= 1;
  f.resize(n), w.resize(n), reverse(all(w));
  int k = 1, n2 = 2 * n, n4 = 4 * n;
  Poly _P(n2), _Q(n2);
  for (int i = 0; i < n; ++i)
    _P[i] = w[i], _Q[i] = sub(0, f[i]);
  while (n > 1) {
    Poly R(n2);
    for (int i = 0; i < n2; ++i)
      R[i] = (i & 1 ? sub(0, _Q[i]) : _Q[i]);
    Poly PQ = Mul(_P, R), QQ = Mul(_Q, R);
    PQ.resize(n4), QQ.resize(n4);
    for (int i = 0, j = n2; i < n2; ++i, ++j) {
      PQ[j] = add(PQ[j], _P[i]);
      QQ[j] = add(QQ[j], add(_Q[i], R[i]));
    }
    fill(all(_P), 0), fill(all(_Q), 0);
    for (int j = 0; j < 2 * k; ++j)
      for (int i = 0; i < n / 2; ++i) {
        _P[n * j + i] = PQ[2 * n * j + 2 * i + 1];
        _Q[n * j + i] = QQ[2 * n * j + 2 * i + 0];
      }
    n /= 2, k *= 2;
  }
  Poly p(k);
  for (int i = 0; i < k; ++i) p[i] = _P[2 * i];
  reverse(all(p)), p.resize(m + 1);
  return p;
} // 5af1d9
