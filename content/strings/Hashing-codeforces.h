/**
 * Author: Simon Lindholm
 * Description: Hack-resistant string hash modulo two primes and 2^32.
 * Status: stress-tested
 */
#pragma once

typedef uint64_t ull;
static int C=((int)(chrono::steady_clock::now().time_since_epoch().count()
             % 999999749)+256)|1;
template<int M, class B> struct A {
  int x; B b;
  A(int x=0):x(x), b((B)x){}
  A(int x, B b):x(x), b(b){}
  A operator+(A o) const {int y=x+o.x;return {y-(y>=M)*M, b+o.b};}
  A operator-(A o) const {int y=x-o.x;return {y+(y<0)*M, b-o.b};}
  A operator*(A o) const {return {(int)(1LL*x*o.x%M), b*o.b};}
  explicit operator ull() const {return x^(ull)b<<21;}
  bool operator==(A o) const {return (ull)*this==(ull)o;}
  bool operator<(A o) const {return (ull)*this<(ull)o;}
};
using H=A<1000000007, A<1000000009, unsigned>>;

struct HashInterval {
  vector<H> ha, pw;
  HashInterval(const string &s):ha(sz(s)+1), pw(ha){
    pw[0]=1;
    rep(i, 0, sz(s)) ha[i+1]=ha[i]*C+s[i], pw[i+1]=pw[i]*C;
  }
  H hashInterval(int l, int r) const {return ha[r]-ha[l]*pw[r-l];}
};
vector<H> getHashes(const string &s, int len){
  if(sz(s)<len) return {};
  H h=0, pw=1; rep(i, 0, len) h=h*C+s[i], pw=pw*C;
  vector<H> res{h};
  rep(i, len, sz(s)) res.pb(h=h*C+s[i]-pw*s[i-len]);
  return res;
}
H hashString(const string &s){H h=0;for(char c:s)h=h*C+c;return h;}
