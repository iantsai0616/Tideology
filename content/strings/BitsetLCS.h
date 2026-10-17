/**
 * Author: Tideology
 * Source: Hyyro, Bit-parallel LCS-length computation revisited (2004)
 * License: CC0
 * Description: Length of the longest common subsequence, 64 columns per word operation.
 * Time: $O(|a| |b| / 64)$, $O(256 |b| / 64)$ memory
 * Status: stress-tested
 */
#pragma once

typedef unsigned long long ull;
int lcs(const string& a, const string& b){
  int W = sz(b) / 64 + 1, res = 0;
  vector<vector<ull>> M(256, vector<ull>(W));
  rep(j, 0, sz(b)) M[(unsigned char)b[j]][j >> 6] |= 1ULL << (j & 63);
  vector<ull> row(W);
  for(unsigned char c : a){
    ull carry = 1, borrow = 0;
    rep(w, 0, W){ // row = x & ~(x - (row << 1 | 1)), x = row | M[c]
      ull x = row[w] | M[c][w], y = row[w] << 1 | carry;
      carry = row[w] >> 63;
      ull d = x - y - borrow;
      borrow = x < y || x - y < borrow;
      row[w] = x & ~d;
    }
  }
  for(ull w : row) res += __builtin_popcountll(w);
  return res;
}
