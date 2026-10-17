/**
 * Author: Tideology
 * Source: design of 8BQube / kiseki palindromic tree, rewritten
 * License: CC0
 * Description: Palindromic tree. Node 0 is the odd root (len -1), node 1 the even root (len 0);
 * other nodes are the distinct palindromes in order of first occurrence.
 * After add(c), last is the longest palindromic suffix. count() makes cnt[v] = number of occurrences.
 * For $n = 10^6$ call reserve(n + 2) on the vectors first.
 * Time: O(n) amortized, $O(n \sigma)$ memory
 * Status: stress-tested, Library Checker eertree
 */
#pragma once

struct Eertree {
  vector<array<int32_t, 26>> nx; vi len, link, par, cnt;
  string s; int last = 1;
  Eertree(){ node(-1, 0, -1), node(0, 0, -1); }
  int node(int l, int k, int p){
    nx.push_back({}), len.push_back(l), link.push_back(k);
    par.push_back(p), cnt.push_back(0); return sz(len) - 1;
  }
  int get(int v, int i){
    while(i - len[v] < 1 || s[i - len[v] - 1] != s[i]) v = link[v];
    return v;
  }
  void add(char ch){
    s += ch; int i = sz(s) - 1, c = ch - 'a', v = get(last, i);
    if(!nx[v][c]){
      int k = v ? nx[get(link[v], i)][c] : 1;
      int u = node(len[v] + 2, k, v); nx[v][c] = u;
    }
    cnt[last = nx[v][c]]++;
  }
  void count(){ for(int v = sz(len) - 1; v > 1; v--) cnt[link[v]] += cnt[v]; }
};
