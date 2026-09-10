/**
 * Author: AtCoder Library
 * License: CC0
 * Description: Linear suffix array by SA-IS. Includes the empty suffix.
 * Time: O(n)
 * Status: stress-tested, yosupo
 */
#pragma once

struct SAIS {
  vi sa, lcp;
  vi build(const vi &s, int lim){
    int n = sz(s);
    if(n == 1) return {0};
    vi ret(n, -1), ls(n), sumL(lim + 1), sumS(lim + 1);
    for(int i = n - 2; i >= 0; i--){
      ls[i] = s[i] == s[i + 1] ? ls[i + 1] : s[i] < s[i + 1];
    }
    rep(i, 0, n) (ls[i] ? sumL[s[i] + 1] : sumS[s[i]])++;
    rep(i, 0, lim + 1){
      sumS[i] += sumL[i];
      if(i < lim) sumL[i + 1] += sumS[i];
    }
    auto induce = [&](const vi &lms){
      fill(all(ret), -1);
      vi buf = sumS;
      for(int x : lms) ret[buf[s[x]]++] = x;
      buf = sumL, ret[buf[s[n - 1]]++] = n - 1;
      rep(i, 0, n){
        int x = ret[i] - 1;
        if(x >= 0 && !ls[x]) ret[buf[s[x]]++] = x;
      }
      buf = sumL;
      for(int i = n; i--;){
        int x = ret[i] - 1;
        if(x >= 0 && ls[x]) ret[--buf[s[x] + 1]] = x;
      }
    };
    vi id(n + 1, -1), lms;
    rep(i, 1, n) if(!ls[i - 1] && ls[i]) id[i] = sz(lms), lms.pb(i);
    induce(lms);
    if(sz(lms)){
      vi ord;
      for(int x : ret) if(id[x] != -1) ord.pb(x);
      vi rec(sz(lms)); int names = 0;
      rec[id[ord[0]]] = 0;
      rep(i, 1, sz(lms)){
        int l = ord[i - 1], r = ord[i];
        int el = id[l] + 1 < sz(lms) ? lms[id[l] + 1] : n;
        int er = id[r] + 1 < sz(lms) ? lms[id[r] + 1] : n;
        bool same = el - l == er - r;
        while(same && l < el && s[l] == s[r]) l++, r++;
        if(l == n || s[l] != s[r]) same = false;
        rec[id[ord[i]]] = same ? names : ++names;
      }
      vi recSa = build(rec, names);
      rep(i, 0, sz(lms)) ord[i] = lms[recSa[i]];
      induce(ord);
    }
    return ret;
  }
  SAIS(string s){
    int n = sz(s), k = 0;
    vi a(n + 1), rk(n + 1);
    rep(i, 0, n) a[i] = (unsigned char)s[i];
    sa = build(a, 255), lcp.assign(n + 1, 0);
    rep(i, 0, n + 1) rk[sa[i]] = i;
    rep(i, 0, n){
      if(k) k--;
      int j = sa[rk[i] - 1];
      while(a[i + k] == a[j + k]) k++;
      lcp[rk[i]] = k;
    }
  }
};
