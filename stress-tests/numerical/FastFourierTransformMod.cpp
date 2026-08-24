#include "../utilities/template.h"

const ll mod = 1000000007;

#include "../../content/numerical/FastFourierTransformMod.h"

vl simpleConv(vl a, vl b){
  if(a.empty() || b.empty()) return {};
  int s = sz(a) + sz(b) - 1;
  vl c(s);
  rep(i, 0, sz(a)) rep(j, 0, sz(b))
    c[i+j] = (c[i+j] + (ll)a[i] * b[j]) % mod;
  for(auto &x: c) if(x < 0) x += mod;
  return c;
}

int ra(){
  static unsigned X;
  X *= 123671231;
  X += 1238713;
  X ^= 1237618;
  return (X >> 1);
}

int main(){
  vl a, b;
  rep(it, 0, 6000){
    a.resize(ra() % 100);
    b.resize(ra() % 100);
    for(auto &x: a) x = ra() % mod;
    for(auto &x: b) x = ra() % mod;
    auto v1 = simpleConv(a, b);
    auto v2 = convMod<mod>(a, b);
    assert(v1 == v2);
  }
  int n = 1 << 18;
  a.assign(n, mod-1); b.assign(n, mod-1);
  auto c = convMod<mod>(a, b);
  rep(i, 0, sz(c)) assert(c[i] == min(i+1, 2*n-1-i));
  n = 1 << 19; a.resize(n); b.resize(n);
  for(ll &x : a) x = ra()%mod;
  for(ll &x : b) x = ra()%mod;
  c = convMod<mod>(a, b);
  rep(s, 0, 200){
    int k = (ll)s*(sz(c)-1)/199; ll ans = 0;
    for(int i = max(0, k-n+1); i <= min(n-1, k); i++)
      ans = (ans+a[i]*b[k-i])%mod;
    assert(c[k] == ans);
  }
  cout<<"Tests passed!"<<endl;
}
