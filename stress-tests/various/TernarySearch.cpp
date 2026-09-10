#include "../utilities/template.h"

#include "../../content/various/TernarySearch.h"

int main(){
  mt19937 rng(123);
  rep(n, 1, 1000) rep(it, 0, 100){
    int l = rng()%n, r = l+rng()%(n-l); vi a(n);
    rep(i, 0, n){
      if(i < l) a[i] = i-l;
      else if(i <= r) a[i] = 0;
      else a[i] = r-i;
    }
    assert(ternSearch(0, n-1, [&](int i){ return a[i]; }) == l);
  }
  cout << "Tests passed!\n";
}
