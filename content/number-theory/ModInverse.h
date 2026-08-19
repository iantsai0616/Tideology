/**
 * Author: Simon Lindholm
 * Description: Inverses of [1, n) modulo a prime, assuming n <= mod.
 * Time: O(n)
 * Status: stress-tested
 */
#pragma once

vector<ll> inverses(int n, ll mod){
  vector<ll> inv(n);
  if(n > 1) inv[1] = 1;
  rep(i, 2, n) inv[i] = mod - mod / i * inv[mod % i] % mod;
  return inv;
}
