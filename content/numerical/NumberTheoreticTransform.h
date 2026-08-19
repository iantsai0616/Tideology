/**
 * Source: KACTL-style cached roots, DIF/DIT convolution
 * Description: NTT/convolution modulo 998244353, up to size 2^23.
 * Time: O(N log N)
 * Status: stress-tested and benchmarked
 */
#pragma once

const ll ntt_mod = 998244353, ntt_root = 62;
typedef vector<ll> vl;
ll nttPow(ll a, ll n){
  ll r = 1; for(; n; n >>= 1, a = a * a % ntt_mod) if(n & 1) r = r * a % ntt_mod;
  return r;
}

void nttRaw(vl &a, bool inv = false){
  int n = sz(a); static vl rt(2, 1), irt(2, 1);
  for(static int k = 2; k < n; k *= 2){
    rt.resize(2 * k); irt.resize(2 * k);
    ll z = nttPow(ntt_root, (ntt_mod - 1) / (2 * k)), iz = nttPow(z, ntt_mod - 2);
    rt[k] = irt[k] = 1;
    rep(i, 1, k) rt[k + i] = rt[k + i - 1] * z % ntt_mod,
               irt[k + i] = irt[k + i - 1] * iz % ntt_mod;
  }
  if(!inv) for(int k = n / 2; k; k /= 2)
    for(int i = 0; i < n; i += 2 * k) rep(j, 0, k){
      ll x = a[i + j], y = a[i + j + k];
      a[i + j] = x + y < ntt_mod ? x + y : x + y - ntt_mod;
      a[i + j + k] = (x - y + ntt_mod) * rt[k + j] % ntt_mod;
    }
  else{
    for(int k = 1; k < n; k *= 2)
      for(int i = 0; i < n; i += 2 * k) rep(j, 0, k){
        ll x = a[i + j], y = a[i + j + k] * irt[k + j] % ntt_mod;
        a[i + j] = x + y < ntt_mod ? x + y : x + y - ntt_mod;
        a[i + j + k] = x - y < 0 ? x - y + ntt_mod : x - y;
      }
    ll z = nttPow(n, ntt_mod - 2); for(ll &x : a) x = x * z % ntt_mod;
  }
}
void ntt(vl &a){
  int n = sz(a); assert(n and !(n & (n - 1)) and n <= (1 << 23));
  nttRaw(a);
  for(int i = 1, j = 0; i < n; i++){
    int b = n / 2; for(; j & b; b /= 2) j ^= b;
    j ^= b; if(i < j) swap(a[i], a[j]);
  }
}
vl conv(const vl &a, const vl &b){
  if(a.empty() or b.empty()) return {};
  if(min(a.size(), b.size()) <= 60){
    vl c(sz(a) + sz(b) - 1);
    rep(i, 0, sz(a)) rep(j, 0, sz(b)) c[i + j] = (c[i + j] + a[i] * b[j]) % ntt_mod;
    return c;
  }
  int s = sz(a) + sz(b) - 1, n = 1; while(n < s) n *= 2;
  assert(n <= (1 << 23)); vl x(a), y(b); x.resize(n); y.resize(n);
  nttRaw(x); nttRaw(y);
  rep(i, 0, n) x[i] = x[i] * y[i] % ntt_mod;
  nttRaw(x, true); x.resize(s); return x;
}
