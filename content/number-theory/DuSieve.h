/**
 * Author: Tideology
 * Source: https://oi-wiki.org/math/number-theory/du/
 * License: CC0
 * Description: $\sum_{i \le n} \phi(i) \bmod M$ for $n$ up to about $10^{11}$, using
 * $\sum_{i \le n} \Phi(\lfloor n/i \rfloor) = n(n+1)/2$. Call init() once; L should be about $n^{2/3}$.
 * For $\mu$: use the sieve of $\mu$ and $\sum_{i \le n} S_\mu(\lfloor n/i \rfloor) = 1$.
 * Time: $O(n^{2/3})$
 * Status: Library Checker sum\_of\_totient\_function
 */
#pragma once

const ll M = 998244353; const int L = 5000000;
ll sphi[L]; unordered_map<ll, ll> mp;
void init(){
  rep(i, 0, L) sphi[i] = i;
  rep(i, 2, L) if(sphi[i] == i) for(int j = i; j < L; j += i) sphi[j] -= sphi[j] / i;
  rep(i, 1, L) sphi[i] = (sphi[i] + sphi[i - 1]) % M;
}
ll Sphi(ll n){
  if(n < L) return sphi[n];
  if(mp.count(n)) return mp[n];
  ll r = (n % M) * ((n + 1) % M) % M * ((M + 1) / 2) % M;
  for(ll i = 2, j; i <= n; i = j + 1)
    j = n / (n / i), r -= (j - i + 1) % M * Sphi(n / i) % M;
  return mp[n] = (r % M + M) % M;
}
