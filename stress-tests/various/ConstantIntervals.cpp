#include "../utilities/template.h"

#include "../../content/various/ConstantIntervals.h"

int main(){
  mt19937 rng(123);
  rep(n, 0, 100) rep(it, 0, 1000){
    vi a(n); int cur = 0;
    for(int &x : a) x = cur += rng()%3 == 0;
    vector<array<int, 3>> got, ans;
    constantIntervals(0, n, [&](int i){ return a[i]; },
      [&](int l, int r, int x){ got.pb({l, r, x}); });
    for(int l = 0, r; l < n; l = r){
      r = l+1;
      while(r < n && a[r] == a[l]) r++;
      ans.pb({l, r, a[l]});
    }
    assert(got == ans);
  }
  cout << "Tests passed!\n";
}
