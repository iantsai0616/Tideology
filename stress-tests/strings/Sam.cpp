#include "../utilities/template.h"
#include "../../content/strings/Sam.h"

int main(){
  mt19937 rng(1);
  rep(it, 0, 5000){
    int k=rng()%5+1, n=0; vector<string> s(k);
    for(string &t:s){int m=rng()%8+1;n+=m;while(m--)t+=char('a'+rng()%3);}
    exSAM a(n); for(auto &t:s) a.insert(t); a.build(); a.solve();
    for(auto &t:s) rep(l, 0, sz(t)) rep(r, l+1, sz(t)+1){
      string p=t.substr(l, r-l); int u=0;
      for(char c:p) u=a.go[u][c-'a'];
      int cnt=0;
      for(auto &z:s) for(size_t q=z.find(p);q!=string::npos;q=z.find(p, q+1)) ++cnt;
      if(!u or a.cnt[u]!=cnt){
        cerr<<"pat "<<p<<" state "<<u<<" got "<<(u?a.cnt[u]:-1)<<" want "<<cnt<<'\n';
        for(auto z:s) cerr<<z<<' ';
        cerr<<'\n';
        assert(0);
      }
    }
  }
  cout<<"Tests passed!\n";
}
