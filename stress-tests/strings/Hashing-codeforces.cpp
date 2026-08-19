#include "../utilities/template.h"
#include "../../content/strings/Hashing-codeforces.h"

int main(){
  mt19937 rng(1);
  rep(it, 0, 10000){
    int n=rng()%12; string s;
    rep(i, 0, n) s+=char('a'+rng()%10);
    HashInterval h(s); set<string> a; set<ull> b;
    rep(i, 0, n+1) rep(j, i, n+1){
      string t=s.substr(i, j-i);
      assert((ull)h.hashInterval(i, j)==(ull)hashString(t));
      a.insert(t), b.insert((ull)hashString(t));
    }
    assert(a.size()==b.size());
    rep(k, 1, n+1){
      auto v=getHashes(s, k);
      rep(i, 0, sz(v)) assert((ull)v[i]==(ull)h.hashInterval(i, i+k));
    }
  }
  cout<<"Tests passed!\n";
}
