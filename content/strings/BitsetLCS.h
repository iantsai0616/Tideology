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
  int W = sz(b) / 64 + 1, res = sz(b);
  vector<vector<ull>> M(256, vector<ull>(W));
  rep(j, 0, sz(b)) M[(unsigned char)b[j]][j >> 6] |= 1ULL << (j & 63);
  vector<ull> V(W, ~0ULL); // V = (V + (V & M[c])) | (V & ~M[c])
  for(unsigned char c : a){
    unsigned __int128 carry = 0;
    rep(w, 0, W){
      ull u = V[w] & M[c][w];
      carry += (unsigned __int128)V[w] + u;
      V[w] = (ull)carry | (V[w] - u), carry >>= 64;
    }
  }
  rep(j, 0, sz(b)) res -= V[j >> 6] >> (j & 63) & 1;
  return res;
}
