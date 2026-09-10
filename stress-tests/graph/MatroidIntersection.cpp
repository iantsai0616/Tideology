#include "../utilities/template.h"
#include "../../content/graph/MatroidIntersection.h"

bool independent(const vi &I, const vi &color, const vi &cap){
  vi cnt(sz(cap));
  for(int e : I) if(++cnt[color[e]] > cap[color[e]]) return false;
  return true;
}
struct TableMatroid{
  vector<char> ok;
  int mask = 0;
  TableMatroid(vector<char> ok) : ok(ok){}
  void build(const vi &I){
    mask = 0;
    for(int e : I) mask |= 1 << e;
  }
  bool oracle(int e){ return ok[mask | (1 << e)]; }
  bool oracle(int e, int f){ return ok[(mask ^ (1 << e)) | (1 << f)]; }
};
auto asTuple(TableMatroid &m){
  return tuple(
    [&](const vi &I){ m.build(I); },
    [&](int e){ return m.oracle(e); },
    [&](int e, int f){ return m.oracle(e, f); });
}
vector<char> linearMatroid(const vector<unsigned long long> &a){
  int n = sz(a);
  vector<char> ok(1 << n);
  rep(mask, 0, 1 << n){
    unsigned long long basis[64]{};
    bool good = 1;
    rep(i, 0, n) if(mask >> i & 1){
      auto x = a[i];
      while(x){
        int b = 63 - __builtin_clzll(x);
        if(!basis[b]){
          basis[b] = x;
          break;
        }
        x ^= basis[b];
      }
      if(!x){
        good = 0;
        break;
      }
    }
    ok[mask] = good;
  }
  return ok;
}
int getMask(const vi &I, int n){
  int mask = 0;
  for(int e : I){
    assert(0 <= e && e < n && !(mask >> e & 1));
    mask |= 1 << e;
  }
  return mask;
}
int main(){
  {
    vi color{0, 0, 1, 1}, shape{0, 1, 0, 2}, cap1{1, 2}, cap2{1, 1, 1};
    vi cnt1(sz(cap1)), cnt2(sz(cap2));
    auto m1 = tuple(
      [&](const vi &I){
        fill(all(cnt1), 0);
        for(int e : I) cnt1[color[e]]++;
      },
      [&](int e){ return cnt1[color[e]] < cap1[color[e]]; },
      [&](int e, int f){
        return color[e] == color[f] || cnt1[color[f]] < cap1[color[f]];
      });
    auto m2 = tuple(
      [&](const vi &I){
        fill(all(cnt2), 0);
        for(int e : I) cnt2[shape[e]]++;
      },
      [&](int e){ return cnt2[shape[e]] < cap2[shape[e]]; },
      [&](int e, int f){
        return shape[e] == shape[f] || cnt2[shape[f]] < cap2[shape[f]];
      });
    MatroidIntersection mi(4, m1, m2);
    vi I = mi.calc();
    assert(sz(I) == 3);
    assert(independent(I, color, cap1));
    assert(independent(I, shape, cap2));
  }
  mt19937_64 rng(1);
  rep(tc, 0, 1000){
    int n = rng() % 10 + 1, dim = rng() % 10 + 1;
    vector<unsigned long long> a(n), b(n);
    rep(i, 0, n) a[i] = rng() & ((1ULL << dim) - 1);
    rep(i, 0, n) b[i] = rng() & ((1ULL << dim) - 1);
    auto oka = linearMatroid(a), okb = linearMatroid(b);
    int bestSize = 0;
    rep(mask, 0, 1 << n) if(oka[mask] && okb[mask]){
      chmax(bestSize, __builtin_popcount(mask));
    }
    TableMatroid ma(oka), mb(okb);
    MatroidIntersection mi(n, asTuple(ma), asTuple(mb));
    vi I = mi.calc();
    int mask = getMask(I, n);
    assert(oka[mask] && okb[mask] && sz(I) == bestSize);
  }
  {
    int k = 50, n = k * k;
    vi row(n), col(n), cap(k, 1);
    rep(i, 0, k) rep(j, 0, k){
      int e = i * k + j;
      row[e] = i; col[e] = j;
    }
    vi cnt1(k), cnt2(k);
    auto m1 = tuple(
      [&](const vi &I){
        fill(all(cnt1), 0);
        for(int e : I) cnt1[row[e]]++;
      },
      [&](int e){ return cnt1[row[e]] < cap[row[e]]; },
      [&](int e, int f){ return row[e] == row[f] || cnt1[row[f]] < cap[row[f]]; });
    auto m2 = tuple(
      [&](const vi &I){
        fill(all(cnt2), 0);
        for(int e : I) cnt2[col[e]]++;
      },
      [&](int e){ return cnt2[col[e]] < cap[col[e]]; },
      [&](int e, int f){ return col[e] == col[f] || cnt2[col[f]] < cap[col[f]]; });
    MatroidIntersection mi(n, m1, m2);
    vi I = mi.calc();
    assert(sz(I) == k && independent(I, row, cap) && independent(I, col, cap));
  }
  cout << "Tests passed!\n";
}
