/**
 * Author: Noam527
 * Date: 2019-04-24
 * License: CC0
 * Source: folklore
 * Description:
 * Status: tested
 */
#pragma once

const ll mod = 1000000007; // faster if const

ll modpow(ll b, ll e, ll m = mod){
  ll ans = 1;
  b %= m;
  for(; e; b = b * b % m, e /= 2)
    if(e & 1) ans = ans * b % m;
  return ans;
}
