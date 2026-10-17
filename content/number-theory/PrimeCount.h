/**
 * Author: Benjamin Qi
 * Source: https://github.com/bqi343/cp-notebook (PrimeCnt.h)
 * License: CC0
 * Description: Number of primes $\le N$ (Lucy-style). countPrimes(1e13) = 346065536839.
 * Time: $O(N^{3/4} / \log N)$, about 0.03s for $N = 10^{11}$
 * Status: tested against sieve for $N \le 2 \cdot 10^6$, Library Checker counting\_primes
 */
#pragma once

ll countPrimes(ll N){
  if(N <= 1) return 0;
  int sq = (int)sqrtl(N), pc = 0;
  vector<ll> big((sq + 1) / 2), small(sq + 1);
  rep(i, 1, sq + 1) small[i] = (i - 1) / 2;
  rep(i, 0, sz(big)) big[i] = (N / (2 * i + 1) - 1) / 2;
  vector<bool> skip(sq + 1);
  for(int p = 3; p <= sq; p += 2) if(!skip[p]){
    for(int j = p; j <= sq; j += 2 * p) skip[j] = 1;
    rep(j, 0, min((ll)sz(big), (N / p / p + 1) / 2)){
      ll prod = (ll)(2 * j + 1) * p;
      big[j] -= (prod > sq ? small[(ll)((double)N / prod)] : big[prod / 2]) - pc;
    }
    for(int j = sq, q = sq / p; q >= p; --q) for(; j >= q * p; --j)
      small[j] -= small[q] - pc;
    ++pc;
  }
  return big[0] + 1;
}
