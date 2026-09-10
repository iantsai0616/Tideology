#include "../utilities/template.h"
#include "../../content/number-theory/ModInverse.h"

ll pw(ll a, ll e, ll m){
  ll r=1; for(;e;e>>=1, a=a*a%m) if(e&1) r=r*a%m;
  return r;
}
int main(){
  for(int p:{2, 3, 5, 101, 1009}){
    auto iv=inverses(p, p);
    rep(i, 1, p) assert(iv[i]==pw(i, p-2, p));
  }
  cout<<"Tests passed!\n";
}
