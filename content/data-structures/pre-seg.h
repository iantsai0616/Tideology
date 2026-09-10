/**
 * Description: Persistent segment tree: point assign and range sum on [0, n).
 * Usage: Seg st(n); int root2=st.modify(root1, p, x); st.query(root2, l, r);
 * Time: O(log n) per operation
 * Status: stress-tested
 */
#pragma once

struct Seg {
  struct Node { int ch[2]{}; ll val=0; };
  vector<Node> t{{}};
  int n;
  Seg(int n, int q = 0) : n(n){ if(q) t.reserve(1+q*(__lg(n)+1)); }
  int modify(int u, int l, int r, int p, ll x){
    int v = sz(t); t.pb(t[u]);
    if(r-l == 1) return t[v].val=x, v;
    int m=(l+r)/2, d=p>=m;
    if(d) t[v].ch[1]=modify(t[v].ch[1], m, r, p, x);
    else t[v].ch[0]=modify(t[v].ch[0], l, m, p, x);
    t[v].val=t[t[v].ch[0]].val+t[t[v].ch[1]].val;
    return v;
  }
  int modify(int root, int p, ll x){
    assert(0<=p and p<n); return modify(root, 0, n, p, x);
  }
  ll query(int u, int l, int r, int a, int b) const {
    if(!u or b<=l or r<=a) return 0;
    if(a<=l and r<=b) return t[u].val;
    int m=(l+r)/2;
    return query(t[u].ch[0], l, m, a, b)+query(t[u].ch[1], m, r, a, b);
  }
  ll query(int root, int l, int r) const {
    return query(root, 0, n, l, r);
  }
};
