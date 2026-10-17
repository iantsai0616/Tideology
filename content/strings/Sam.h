/**
 * Description: Generalized suffix automaton for lowercase strings.
 * Construct with total length, insert strings, build, then solve for cnt.
 * Time: O(N alphabet)
 * Status: stress-tested
 */
#pragma once

struct exSAM{
  static const int C = 27;
  vector<int>len, link, ord, cnt;
  vector<array<signed, C>>go; // not ll: memory
  int last;
  exSAM(int n){
    len.reserve(2 * n + 2), link.reserve(2 * n + 2), cnt.reserve(2 * n + 2), go.reserve(2 * n + 2);
    node(); link[0] = -1, last = 0;
  }
  int node(){
    len.pb(0), link.pb(0), cnt.pb(0), go.pb({}); return sz(len) - 1;
  }
  void extend(int c){
    int cur = node(), p = last; len[cur] = len[last] + 1, cnt[cur] = 1, last = cur;
    for(; p != -1 and !go[p][c]; p = link[p]) go[p][c] = cur;
    if(p == -1) return link[cur] = 0, void();
    int q = go[p][c];
    if(len[p] + 1 == len[q]) return link[cur] = q, void();
    int cl = node(); go[cl] = go[q], len[cl] = len[p] + 1, link[cl] = link[q];
    for(; p != -1 and go[p][c] == q; p = link[p]) go[p][c] = cl;
    link[q] = link[cur] = cl;
  }
  void insert(const string &s){
    for(char c : s) extend(c - 'a');
    extend(26);
  }
  void build(){
    int n = sz(len); ord.resize(n); vector<int>sum(len[last] + 1);
    rep(i, 0, n) ++sum[len[i]];
    partial_sum(all(sum), sum.begin());
    rep(i, 0, n) ord[--sum[len[i]]] = i;
  }
  void solve(){
    for(int i = sz(ord) - 1; i; --i){
      int u = ord[i]; cnt[link[u]] += cnt[u];
    }
  }
};
