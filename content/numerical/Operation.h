/**
 * Description: Formal power series modulo 998244353.
 * Requires: NumberTheoreticTransform
 * Time: O(N log N) for Mul, O(N log^2 N) for Newton operations
 * Status: stress-tested against naive series
 */
#pragma once
#include "NumberTheoreticTransform.h"

struct FPS : vl {
  using vl::vl;
  FPS(const vl &a):vl(a){}
  int n() const { return sz(*this); }
  FPS cut(int m) const { FPS r=*this; r.resize(m); return r; }
  FPS& imul(ll x){
    x%=ntt_mod; if(x<0) x+=ntt_mod;
    for(ll &v:*this) v=v*x%ntt_mod;
    return *this;
  }
  FPS& iadd(const FPS &b, int s=1){
    if(n()<b.n()) resize(b.n());
    rep(i, 0, b.n()){
      (*this)[i]=((*this)[i]+s*b[i])%ntt_mod;
      if((*this)[i]<0) (*this)[i]+=ntt_mod;
    }
    return *this;
  }
  FPS Mul(const FPS &b) const { return FPS(conv(*this, b)); }
  FPS Inv(int m=-1) const {
    if(m<0) m=n();
    assert(n() and (*this)[0]);
    FPS r{nttPow((*this)[0], ntt_mod-2)};
    for(int k=2; k/2<m; k<<=1){
      int z=min(k, m); FPS q=cut(z).Mul(r).cut(z).imul(-1);
      q[0]=(q[0]+2)%ntt_mod;
      r=r.Mul(q).cut(z);
    }
    return r.cut(m);
  }
  FPS Dx() const {
    if(n()<2) return {};
    FPS r(n()-1); rep(i, 1, n()) r[i-1]=(*this)[i]*i%ntt_mod;
    return r;
  }
  FPS Sx() const {
    static vl iv{0, 1}; int m=n()+1;
    while(sz(iv)<m){
      ll i=sz(iv); iv.pb(ntt_mod-ntt_mod/i*iv[ntt_mod%i]%ntt_mod);
    }
    FPS r(m); rep(i, 0, n()) r[i+1]=(*this)[i]*iv[i+1]%ntt_mod;
    return r;
  }
  FPS Ln(int m=-1) const {
    if(m<0) m=n();
    assert(n() and (*this)[0]==1);
    return Dx().Mul(Inv(m)).Sx().cut(m);
  }
  FPS Exp(int m=-1) const {
    if(m<0) m=n();
    assert(!n() or !(*this)[0]);
    FPS r{1};
    for(int k=2; k/2<m; k<<=1){
      int z=min(k, m); FPS q=cut(z).iadd(r.Ln(z), -1);
      q[0]=(q[0]+1)%ntt_mod;
      r=r.Mul(q).cut(z);
    }
    return r.cut(m);
  }
  FPS Pow(ll k, int m=-1) const {
    if(m<0) m=n();
    if(!k){ FPS r(m); if(m) r[0]=1; return r; }
    int p=0; while(p<n() and !(*this)[p]) ++p;
    if(p==n() or (p and k>=(m+p-1)/p)) return FPS(m);
    int sh=(int)(p*k), z=m-sh; ll c=(*this)[p], ic=nttPow(c, ntt_mod-2);
    FPS f(begin()+p, end()); f=f.cut(z).imul(ic);
    f=f.Ln(z).imul(k%ntt_mod).Exp(z).imul(nttPow(c, k));
    f.insert(f.begin(), sh, 0); return f.cut(m);
  }
  pair<FPS, FPS> DivMod(FPS b) const {
    FPS a=*this;
    while(a.n()>1 and !a.back()) a.pop_back();
    while(b.n()>1 and !b.back()) b.pop_back();
    assert(b.n() and b.back());
    if(a.n()<b.n()) return {{0}, a};
    int m=a.n()-b.n()+1;
    FPS x=a, y=b; reverse(all(x)), reverse(all(y));
    FPS q=x.cut(m).Mul(y.cut(m).Inv(m)).cut(m); reverse(all(q));
    FPS r=a; r.iadd(b.Mul(q), -1); r.resize(max<int>(1, b.n()-1));
    return {q, r};
  }
};
using Poly_t=FPS;
