#include "../utilities/template.h"
#include "../../content/numerical/NumberTheoreticTransform.h"

vl naive(const vl &a, const vl &b){
  if(a.empty() or b.empty()) return {};
  vl c(sz(a)+sz(b)-1);
  rep(i, 0, sz(a)) rep(j, 0, sz(b))
    c[i+j]=(c[i+j]+a[i]*b[j])%ntt_mod;
  return c;
}
int main(){
  mt19937 rng(1);
  rep(it, 0, 5000){
    vl a(rng()%60), b(rng()%60);
    for(ll &x:a) x=rng()%ntt_mod;
    for(ll &x:b) x=rng()%ntt_mod;
    assert(conv(a, b)==naive(a, b));
  }
  vl a(16); for(ll &x:a) x=rng()%ntt_mod;
  vl b=a; ntt(b);
  rep(k, 0, 16){
    ll s=0;
    rep(i, 0, 16) s=(s+a[i]*nttPow(ntt_root, k*i*(ntt_mod-1)/16))%ntt_mod;
    assert(s==b[k]);
  }
  cout<<"Tests passed!\n";
}
