#include "../utilities/template.h"

#include "../../content/combinatorial/multinomial.h"

ll brute(vi& cnt, int left){
  if(!left) return 1;
  ll ans = 0;
  rep(i, 0, sz(cnt)) if(cnt[i]){
    cnt[i]--; ans += brute(cnt, left-1); cnt[i]++;
  }
  return ans;
}

int main(){
  mt19937 rng(123);
  rep(it, 0, 3000){
    vi cnt(1 + rng()%5); int sum = 0;
    for(int &x : cnt) x = rng()%4, sum += x;
    if(sum > 11){ it--; continue; }
    vi cp = cnt;
    assert(multinomial(cnt) == brute(cp, sum));
  }
  cout << "Tests passed!\n";
}
