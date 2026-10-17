/**
 * Author: cp-algorithms
 * Source: https://cp-algorithms.com/algebra/big-integer.html
 * License: CC BY-SA 4.0
 * Description: Non-negative big integers, base $10^9$, little-endian, no leading zeros.
 * Time: O(n) for add, sub, divs; O(nm) for mul
 * Status: tested against Python
 */
#pragma once

typedef vector<ll> lnum;
const int base = 1000000000;
void trim(lnum &a){ while(sz(a) > 1 && a.back() == 0) a.pop_back(); }
lnum read(const string &s){
  lnum a;
  for(int i = sz(s); i > 0; i -= 9) a.push_back(stoll(s.substr(max<int>(0, i - 9), i - max<int>(0, i - 9))));
  trim(a); return a;
}
void print(const lnum &a){
  cout << (a.empty() ? 0 : a.back());
  for(int i = sz(a) - 2; i >= 0; --i) cout << setw(9) << setfill('0') << a[i];
}
bool lessThan(const lnum &a, const lnum &b){
  if(sz(a) != sz(b)) return sz(a) < sz(b);
  return lexicographical_compare(a.rbegin(), a.rend(), b.rbegin(), b.rend());
}
void add(lnum &a, const lnum &b){ // a += b
  ll c = 0;
  for(int i = 0; i < max(sz(a), sz(b)) || c; ++i){
    if(i == sz(a)) a.push_back(0);
    a[i] += c + (i < sz(b) ? b[i] : 0);
    c = a[i] >= base; if(c) a[i] -= base;
  }
}
void sub(lnum &a, const lnum &b){ // a -= b, a >= b
  ll c = 0;
  for(int i = 0; i < sz(b) || c; ++i){
    a[i] -= c + (i < sz(b) ? b[i] : 0);
    c = a[i] < 0; if(c) a[i] += base;
  }
  trim(a);
}
lnum mul(const lnum &a, const lnum &b){
  lnum c(sz(a) + sz(b));
  rep(i, 0, sz(a)){
    ll carry = 0;
    for(int j = 0; j < sz(b) || carry; ++j){
      ll cur = c[i + j] + a[i] * (j < sz(b) ? b[j] : 0) + carry;
      c[i + j] = cur % base, carry = cur / base;
    }
  }
  trim(c); return c;
}
ll divs(lnum &a, ll b){ // a /= b (b < base), returns remainder
  ll c = 0;
  for(int i = sz(a) - 1; i >= 0; --i){
    ll cur = a[i] + c * base;
    a[i] = cur / b, c = cur % b;
  }
  trim(a); return c;
}
