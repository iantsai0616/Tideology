/**
 * Author: Unknown
 * Source: https://e-maxx.ru/algo/ukkonen
 * Description: Ukkonen suffix tree for lowercase strings. Nodes store [l, r).
 * Time: O(28N)
 * Status: stress-tested
 */
#pragma once

struct SuffixTree {
  enum { ALPHA = 28 };
  int toi(char c){ return c-'a'; }
  string a;
  vector<array<int, ALPHA>> t;
  vi l, r, p, s;
  int v = 0, q = 0, m = 2;
  void ukkadd(int i, int c){ suff:
    if(r[v] <= q){
      if(t[v][c] == -1){
        t[v][c] = m; l[m] = i; p[m++] = v; v = s[v]; q = r[v];
        goto suff;
      }
      v = t[v][c]; q = l[v];
    }
    if(q == -1 || c == toi(a[q])) q++;
    else{
      l[m+1] = i; p[m+1] = m; l[m] = l[v]; r[m] = q;
      p[m] = p[v]; t[m][c] = m+1; t[m][toi(a[q])] = v;
      l[v] = q; p[v] = m; t[p[m]][toi(a[l[m]])] = m;
      v = s[p[m]]; q = l[m];
      while(q < r[m]) v = t[v][toi(a[q])], q += r[v]-l[v];
      s[m] = q == r[m] ? v : m+2;
      q = r[v]-(q-r[m]); m += 2;
      goto suff;
    }
  }
  SuffixTree(string a) : a(a), t(2*sz(a)+5), l(t.size()), r(t.size(), sz(a)),
      p(t.size()), s(t.size()){
    for(auto &x : t) x.fill(-1);
    t[1].fill(0); s[0] = 1;
    l[0] = l[1] = -1; r[0] = r[1] = p[0] = p[1] = 0;
    rep(i, 0, sz(a)) ukkadd(i, toi(a[i]));
  }
  ll distinctSubstrings(){
    ll ans = 0;
    rep(i, 2, m) ans += r[i]-l[i];
    return ans;
  }
  pii best;
  int lcs(int node, int i1, int i2, int len){
    if(l[node] <= i1 && i1 < r[node]) return 1;
    if(l[node] <= i2 && i2 < r[node]) return 2;
    int mask = 0;
    if(node) len += r[node]-l[node];
    rep(c, 0, ALPHA) if(t[node][c] != -1){
      mask |= lcs(t[node][c], i1, i2, len);
    }
    if(mask == 3) best = max(best, {len, r[node]-len});
    return mask;
  }
  static pii LCS(string s, string t){
    SuffixTree st(s+'{'+t+'|');
    st.lcs(0, sz(s), sz(s)+1+sz(t), 0);
    return st.best;
  }
};
