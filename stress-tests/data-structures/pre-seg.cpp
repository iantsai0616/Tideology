#include "../utilities/template.h"
#include "../../content/data-structures/pre-seg.h"

int main(){
  mt19937 rng(1); int n=100; Seg st(n, 10000); vi root{0}; vector<vi> a(1, vi(n));
  rep(it, 0, 10000){
    int old=rng()%sz(root), p=rng()%n, x=rng()%100000;
    root.pb(st.modify(root[old], p, x)); a.pb(a[old]); a.back()[p]=x;
    int ver=rng()%sz(root), l=rng()%n, r=rng()%n; if(l>r) swap(l, r); ++r;
    assert(st.query(root[ver], l, r)==accumulate(a[ver].begin()+l, a[ver].begin()+r, 0LL));
  }
  cout<<"Tests passed!\n";
}
