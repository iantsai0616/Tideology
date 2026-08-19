#include "../utilities/template.h"
#include "../../content/numerical/Operation.h"

FPS naive(FPS a, FPS b, int n=1000){
  FPS c(min(n, a.n()+b.n()-1));
  rep(i, 0, a.n()) rep(j, 0, b.n()) if(i+j<n)
    c[i+j]=(c[i+j]+a[i]*b[j])%ntt_mod;
  return c;
}
int main(){
  mt19937 rng(1);
  rep(it, 0, 2000){
    int n=rng()%40+1; FPS a(n), b(n);
    for(ll &x:a) x=rng()%ntt_mod;
    for(ll &x:b) x=rng()%ntt_mod;
    assert(a.Mul(b)==naive(a, b));
    if(!a[0]) a[0]=1;
    FPS one=naive(a, a.Inv(n), n); one.resize(n);
    assert(one[0]==1); rep(i, 1, n) assert(one[i]==0);
    FPS f(n); rep(i, 1, n) f[i]=rng()%ntt_mod;
    assert(f.Exp(n).Ln(n)==f);
    int k=rng()%6; FPS p(n); p[0]=1;
    rep(z, 0, k) p=naive(p, f, n), p.resize(n);
    assert(f.Pow(k, n)==p);
    while(!b.back()) b.back()=1;
    auto [q, r]=a.DivMod(b);
    FPS got=b.Mul(q); got.iadd(r); got.resize(a.n());
    assert(got==a);
    assert(r.n()<b.n() or (b.n()==1 and r==FPS{0}));
  }
  cout<<"Tests passed!\n";
}
