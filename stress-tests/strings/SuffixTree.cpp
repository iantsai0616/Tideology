#include "../utilities/template.h"

#include "../../content/strings/SuffixTree.h"

ll bruteDistinct(const string& s){
  set<string> sub;
  rep(i, 0, sz(s)) rep(j, i+1, sz(s)+1) sub.insert(s.substr(i, j-i));
  return sz(sub);
}

int bruteLcs(const string& s, const string& t){
  int ans = 0;
  rep(i, 0, sz(s)) rep(j, 0, sz(t)){
    int k = 0;
    while(i+k < sz(s) && j+k < sz(t) && s[i+k] == t[j+k]) k++;
    ans = max(ans, k);
  }
  return ans;
}

int main(){
  mt19937 rng(123);
  rep(it, 0, 10000){
    string s(rng()%11, 'a'), t(rng()%11, 'a');
    for(char &c : s) c += rng()%4;
    for(char &c : t) c += rng()%4;
    SuffixTree st(s);
    assert(st.distinctSubstrings() == bruteDistinct(s));
    auto [len, pos] = SuffixTree::LCS(s, t);
    assert(len == bruteLcs(s, t));
    string both = s+'{'+t+'|', sub = both.substr(pos, len);
    assert(s.find(sub) != string::npos && t.find(sub) != string::npos);
  }
  string s(500000, 'a');
  auto st = chrono::steady_clock::now();
  SuffixTree tree(s);
  double sec = chrono::duration<double>(chrono::steady_clock::now()-st).count();
  assert(tree.distinctSubstrings() == sz(s) && sec < 2);
  cout << "Tests passed! " << sec << "s\n";
}
