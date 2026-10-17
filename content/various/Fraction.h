/**
 * Author: Tideology
 * License: CC0
 * Description: Exact fractions with $q > 0$ and $\gcd(|p|, q) = 1$. Products overflow
 * once numerators/denominators exceed about $3 \cdot 10^9$; use \_\_int128 fields then.
 * Time: O(\log) per operation
 * Status: tested against long double
 */
#pragma once

struct Frac {
  ll p, q;
  Frac(ll a = 0, ll b = 1){ ll g = gcd(a, b); if(b < 0) g = -g; p = a / g, q = b / g; }
  Frac operator+(Frac o) const { return {p * o.q + o.p * q, q * o.q}; }
  Frac operator-(Frac o) const { return {p * o.q - o.p * q, q * o.q}; }
  Frac operator*(Frac o) const { return {p * o.p, q * o.q}; }
  Frac operator/(Frac o) const { return {p * o.q, q * o.p}; }
  bool operator<(Frac o) const { return (__int128)p * o.q < (__int128)o.p * q; }
  bool operator==(Frac o) const { return p == o.p && q == o.q; }
  friend ostream& operator<<(ostream& os, Frac f){ return os << f.p << '/' << f.q; }
};
