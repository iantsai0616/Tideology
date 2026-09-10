#include "../utilities/template.h"

#include "../../content/strings/SuffixArray.h"
#include "../../content/strings/SuffixArraySAIS.h"
#include "../../content/strings/SuffixArrayDC3.h"

pair<vi, vi> brute(const string &s){
  int n = sz(s);
  vi sa(n + 1), lcp(n + 1);
  iota(all(sa), 0);
  sort(all(sa), [&](int i, int j){
    return lexicographical_compare(s.begin() + i, s.end(),
      s.begin() + j, s.end(), [](char a, char b){
        return (unsigned char)a < (unsigned char)b;
      });
  });
  rep(i, 1, n + 1){
    int a = sa[i - 1], b = sa[i];
    while(a + lcp[i] < n && b + lcp[i] < n &&
      s[a + lcp[i]] == s[b + lcp[i]]){
      lcp[i]++;
    }
  }
  return {sa, lcp};
}

template<class T>
void check(const string &s, string name){
  auto [sa, lcp] = brute(s);
  T got(s);
  if(got.sa != sa || got.lcp != lcp){
    auto print = [&](string label, const vi &v){
      cerr << '\n' << label << ':';
      for(int x : v) cerr << ' ' << x;
    };
    cerr << name << " failed, n = " << sz(s) << "\ninput:";
    for(unsigned char c : s) cerr << ' ' << (int)c;
    print("want sa", sa), print("got sa", got.sa);
    print("want lcp", lcp), print("got lcp", got.lcp);
    cerr << '\n';
  }
  assert(got.sa == sa);
  assert(got.lcp == lcp);
}

void checkAll(const string &s){
  check<SuffixArray>(s, "doubling");
  check<SAIS>(s, "SA-IS");
  check<DC3>(s, "DC3");
}

template<class T>
void bench(const string &s, string name){
  auto st = chrono::steady_clock::now();
  T got(s);
  auto ms = chrono::duration_cast<chrono::milliseconds>(
    chrono::steady_clock::now() - st).count();
  cerr << name << ": " << ms << " ms, checksum = "
    << accumulate(all(got.sa), 0LL) << '\n';
}

signed main(signed argc, char **){
  if(argc > 1){
    mt19937 rng(712367);
    string random(1'000'000, 0), same(1'000'000, 'a');
    for(char &c : random) c = (char)(rng() % 26 + 'a');
    for(auto &[s, label] : vector<pair<string*, string>>{
      {&random, "random"}, {&same, "same"}}){
      cerr << label << '\n';
      bench<SuffixArray>(*s, "doubling");
      bench<SAIS>(*s, "SA-IS");
      bench<DC3>(*s, "DC3");
    }
    return 0;
  }
  for(string s : {string(), string("a"), string("banana"),
    string("aaaaaaaa"), string("abababab"), string("mississippi")}){
    checkAll(s);
  }
  checkAll(string(1, (char)128));
  string bytes;
  rep(i, 1, 256) bytes += (char)i;
  checkAll(bytes);
  mt19937 rng(712367);
  rep(it, 0, 20000){
    int n = rng() % 50, alpha = rng() % 12 + 1;
    string s(n, 0);
    rep(i, 0, n) s[i] = (char)(rng() % alpha + 1);
    checkAll(s);
  }
  cout << "Tests passed!\n";
}
