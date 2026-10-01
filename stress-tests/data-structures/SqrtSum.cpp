#include "../utilities/template.h"

#include "../../content/data-structures/SqrtSum.h"

int main(){
  mt19937 rng(1);
  rep(it, 0, 20000){ // signed values, range sum
    int n=rng()%60, q=rng()%200;
    SqrtSum s(n); vector<ll> a(n);
    rep(_, 0, q){
      if(n and rng()%2){
        int i=rng()%n; ll v=(ll)(rng()%2000001)-1000000;
        s.add(i, v); a[i]+=v;
      } else {
        int l=rng()%(n+1), r=rng()%(n+1); if(l>r) swap(l, r);
        assert(s.query(l, r)==accumulate(a.begin()+l, a.begin()+r, 0LL));
      }
    }
  }
  rep(it, 0, 20000){ // nonnegative counts, kth
    int n=rng()%60, q=rng()%200;
    SqrtSum s(n); vector<ll> a(n);
    rep(_, 0, q){
      if(n and rng()%2){
        int i=rng()%n; ll v=(ll)(rng()%5)-2; v=max(v, -a[i]);
        s.add(i, v); a[i]+=v;
      } else {
        ll k=(ll)(rng()%(accumulate(all(a), 0LL)+3))-1, sum=0; int want=n;
        rep(p, 0, n) if((sum+=a[p])>k){ want=p; break; }
        assert(s.kth(k)==want);
      }
    }
  }
  cout<<"Tests passed!\n";
}
