/**
 * Author: chilli, Ramchandra Apte, Noam527, Simon Lindholm
 * Description: Portable a*b mod M for 0 <= a, b < M < 2^64.
 * Time: O(1) for modmul, O(log e) for modpow
 * Status: stress-tested
 */
#pragma once

typedef unsigned long long ull;
ull modmul(ull a, ull b, ull M){
  return (ull)((unsigned __int128)a * b % M);
}
ull modpow(ull a, ull e, ull M){
  ull r = 1;
  for(; e; e >>= 1, a = modmul(a, a, M))
    if(e & 1) r = modmul(r, a, M);
  return r;
}
