/**
 * Author: Juha Karkkainen, Peter Sanders, Stefan Burkhardt
 * License: Unknown
 * Description: Linear suffix array by DC3/skew. Includes the empty suffix.
 * Time: O(n)
 * Status: stress-tested, yosupo
 */
#pragma once

struct DC3 {
  vi sa, lcp;
  bool leq(int a, int b, int c, int d){
    return a < c || (a == c && b <= d);
  }
  bool leq(int a, int b, int c, int d, int e, int f){
    return a < d || (a == d && leq(b, c, e, f));
  }
  void radix(const vi &a, vi &b, const vi &r, int add, int n, int lim){
    vi cnt(lim + 1);
    rep(i, 0, n) cnt[r[a[i] + add]]++;
    for(int i = 0, sum = 0; i <= lim; i++){
      int x = cnt[i]; cnt[i] = sum, sum += x;
    }
    rep(i, 0, n) b[cnt[r[a[i] + add]]++] = a[i];
  }
  vi build(vi &s, int n, int lim){
    if(n == 0) return {};
    if(n == 1) return {0};
    int n0 = (n + 2) / 3, n1 = (n + 1) / 3;
    int n2 = n / 3, n02 = n0 + n2;
    vi s12(n02 + 3), sa12(n02 + 3), s0(n0), sa0(n0);
    for(int i = 0, j = 0; i < n + n0 - n1; i++){
      if(i % 3) s12[j++] = i;
    }
    radix(s12, sa12, s, 2, n02, lim);
    radix(sa12, s12, s, 1, n02, lim);
    radix(s12, sa12, s, 0, n02, lim);
    int names = 0, a = -1, b = -1, c = -1;
    rep(i, 0, n02){
      int x = sa12[i];
      if(s[x] != a || s[x + 1] != b || s[x + 2] != c){
        names++, a = s[x], b = s[x + 1], c = s[x + 2];
      }
      s12[x / 3 + (x % 3 == 2) * n0] = names;
    }
    if(names < n02){
      vi rec = build(s12, n02, names);
      rep(i, 0, n02) sa12[i] = rec[i], s12[rec[i]] = i + 1;
    }
    else rep(i, 0, n02) sa12[s12[i] - 1] = i;
    for(int i = 0, j = 0; i < n02; i++){
      if(sa12[i] < n0) s0[j++] = 3 * sa12[i];
    }
    radix(s0, sa0, s, 0, n0, lim);
    vi ans; ans.reserve(n);
    int p = 0, t = n0 - n1;
    auto pos = [&](int x){
      return x < n0 ? 3 * x + 1 : 3 * (x - n0) + 2;
    };
    while(p < n0 && t < n02){
      int x = pos(sa12[t]), y = sa0[p];
      bool take = sa12[t] < n0 ?
        leq(s[x], s12[sa12[t] + n0], s[y], s12[y / 3]) :
        leq(s[x], s[x + 1], s12[sa12[t] - n0 + 1],
          s[y], s[y + 1], s12[y / 3 + n0]);
      ans.pb(take ? x : y);
      if(take) t++; else p++;
    }
    while(p < n0) ans.pb(sa0[p++]);
    while(t < n02) ans.pb(pos(sa12[t++]));
    return ans;
  }
  DC3(string s){
    int n = sz(s), k = 0;
    vi a(n + 3), rk(n + 1);
    rep(i, 0, n) a[i] = (unsigned char)s[i];
    vi raw = build(a, n, 255);
    sa.pb(n); sa.insert(sa.end(), all(raw));
    lcp.assign(n + 1, 0);
    rep(i, 0, n + 1) rk[sa[i]] = i;
    rep(i, 0, n){
      if(k) k--;
      int j = sa[rk[i] - 1];
      while(i + k < n && j + k < n && a[i + k] == a[j + k]) k++;
      lcp[rk[i]] = k;
    }
  }
};
