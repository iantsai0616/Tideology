#include "../utilities/template.h"

#include "../../content/numerical/Tridiagonal.h"

int main(){
  mt19937 rng(123);
  rep(n, 1, 100) rep(it, 0, 300){
    vector<T> d(n), p(max(0, n-1)), q(max(0, n-1)), x(n), b(n);
    for(T &v : p) v = (int)(rng()%11)-5;
    for(T &v : q) v = (int)(rng()%11)-5;
    rep(i, 0, n) d[i] = 20+abs(i ? q[i-1] : 0)+abs(i+1 < n ? p[i] : 0);
    for(T &v : x) v = (int)(rng()%21)-10;
    rep(i, 0, n){
      b[i] = d[i]*x[i];
      if(i) b[i] += q[i-1]*x[i-1];
      if(i+1 < n) b[i] += p[i]*x[i+1];
    }
    auto got = tridiagonal(d, p, q, b);
    rep(i, 0, n) assert(abs(got[i]-x[i]) < 1e-8);
  }
  cout << "Tests passed!\n";
}
