/**
 * Description: Li Chao tree on known x-coordinates; supports line/segment add.
 * Usage: LiChao tr(xs); tr.add({m, b}); tr.add({m, b}, l, r); tr.query(x);
 * Time: O(log N) per line/query, O(log^2 N) per segment
 * Status: stress-tested
 */
#pragma once

struct Line {
  ll m=0, b=0;
  ll operator()(ll x) const { return m*x+b; }
};
struct LiChao {
  const ll INF = 4e18;
  vector<ll> x; vector<Line> st;
  bool mn;
  LiChao(vector<ll> x, bool mn=true) : x(x), mn(mn){
    sort(all(this->x)); this->x.erase(unique(all(this->x)), this->x.end());
    assert(sz(this->x));
    st.assign(4*sz(this->x), {0, mn?INF:-INF});
  }
  bool better(Line a, Line b, int p){ return mn ? a(x[p])<b(x[p]) : a(x[p])>b(x[p]); }
  void add(Line f, int l, int r, int p){
    int m=(l+r)/2; bool a=better(f, st[p], l), b=better(f, st[p], m);
    if(b) swap(f, st[p]);
    if(r-l==1) return;
    if(a!=b) add(f, l, m, p*2); else add(f, m, r, p*2+1);
  }
  void add(Line f){ add(f, 0, sz(x), 1); }
  void add(Line f, int a, int b, int l, int r, int p){
    if(b<=l or r<=a) return;
    if(a<=l and r<=b) return add(f, l, r, p);
    int m=(l+r)/2;
    add(f, a, b, l, m, p*2); add(f, a, b, m, r, p*2+1);
  }
  void add(Line f, ll l, ll r){ // x in [l, r]
    int a=lower_bound(all(x), l)-x.begin(), b=upper_bound(all(x), r)-x.begin();
    if(a<b) add(f, a, b, 0, sz(x), 1);
  }
  ll query(int p, int l, int r, int q){
    ll ans=st[p](x[q]);
    if(r-l==1) return ans;
    int m=(l+r)/2; ll z=q<m?query(p*2, l, m, q):query(p*2+1, m, r, q);
    return mn?min(ans, z):max(ans, z);
  }
  ll query(ll q){
    q=lower_bound(all(x), q)-x.begin(); assert(q<sz(x));
    return query(1, 0, sz(x), q);
  }
};
