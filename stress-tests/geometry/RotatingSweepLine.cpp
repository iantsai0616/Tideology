#include "../utilities/template.h"
#include "../../content/geometry/RotatingSweepLine.h"

int main(){
  rep(it, 0, 2000){
    vector<P> p;
    while(sz(p) < 8){
      P q(rand() % 15 - 7, rand() % 15 - 7);
      if(find(all(p), q) == p.end()) p.pb(q);
    }
    RotatingSweepLine sw(p);
    vi start = sw.ord;
    sw.run([&](P d, const vi& ord, const vi&){
      rep(i, 1, sz(ord)){
        P a = p[ord[i - 1]], b = p[ord[i]];
        __int128 x = (__int128)d.x*a.y - (__int128)d.y*a.x;
        __int128 y = (__int128)d.x*b.y - (__int128)d.y*b.x;
        __int128 u = (__int128)d.x*a.x + (__int128)d.y*a.y;
        __int128 v = (__int128)d.x*b.x + (__int128)d.y*b.y;
        assert(x < y || (x == y && u <= v));
      }
    });
    assert(sw.ord == start);
  }
  cout << "Tests passed!\n";
}
