/**
 * Description: Exact convolution modulo M using three NTT primes and CRT.
 * Supports transform lengths up to 2^21.
 * Time: O(N log N)
 * Status: stress-tested, Library Checker
 */
#pragma once

typedef vector<ll> vl;
namespace conv_mod {
template<int P> ll pw(ll a, ll n){
  ll r = 1;
  for(; n; n >>= 1, a = a*a%P) if(n&1) r = r*a%P;
  return r;
}
template<int P, int G> void ntt(vl& a, bool inv){
  int n = sz(a);
  for(int i = 1, j = 0; i < n; i++){
    int bit = n >> 1;
    for(; j&bit; bit >>= 1) j ^= bit;
    j ^= bit;
    if(i < j) swap(a[i], a[j]);
  }
  for(int len = 2; len <= n; len <<= 1){
    ll wl = pw<P>(G, (P-1)/len);
    if(inv) wl = pw<P>(wl, P-2);
    for(int i = 0; i < n; i += len){
      ll w = 1;
      rep(j, 0, len/2){
        ll u = a[i+j], v = a[i+j+len/2]*w%P;
        a[i+j] = (u+v)%P;
        a[i+j+len/2] = (u-v+P)%P;
        w = w*wl%P;
      }
    }
  }
  if(inv){
    ll ni = pw<P>(n, P-2);
    for(ll &x : a) x = x*ni%P;
  }
}
template<int P, int G> vl conv(const vl& a, const vl& b, int n, int s){
  vl x(n), y(n);
  rep(i, 0, sz(a)) x[i] = a[i]%P;
  rep(i, 0, sz(b)) y[i] = b[i]%P;
  ntt<P, G>(x, 0); ntt<P, G>(y, 0);
  rep(i, 0, n) x[i] = x[i]*y[i]%P;
  ntt<P, G>(x, 1); x.resize(s);
  return x;
}
}

template<int M> vl convMod(const vl& a, const vl& b){
  if(a.empty() || b.empty()) return {};
  const ll p0 = 998244353, p1 = 1004535809, p2 = 469762049;
  int s = sz(a)+sz(b)-1, n = 1;
  while(n < s) n <<= 1;
  auto x = conv_mod::conv<p0, 3>(a, b, n, s);
  auto y = conv_mod::conv<p1, 3>(a, b, n, s);
  auto z = conv_mod::conv<p2, 3>(a, b, n, s);
  ll i01 = conv_mod::pw<p1>(p0, p1-2);
  ll p01 = p0*p1, i012 = conv_mod::pw<p2>(p01%p2, p2-2);
  vl ret(s);
  rep(i, 0, s){
    ll b1 = (y[i]-x[i]+p1)%p1*i01%p1;
    ll b2 = (z[i]-(x[i]+p0*b1)%p2+p2)%p2*i012%p2;
    ret[i] = (x[i]+(__int128)p0*b1+(__int128)p01*b2)%M;
  }
  return ret;
}
