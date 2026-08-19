#include "../utilities/template.h"
#include "../../content/various/Unrolling.h"

int main(){
  rep(l, 0, 20) rep(r, l, 20){
    vi a; unroll4(l, r, [&](int i){a.pb(i);});
    vi b(r-l); iota(all(b), l); assert(a==b);
  }
  cout<<"Tests passed!\n";
}
