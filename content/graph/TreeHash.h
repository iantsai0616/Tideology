/**
 * Author: Tideology
 * Source: https://peehs-moorhsum.blog.uoj.ac/blog/7891
 * License: CC0
 * Description: Rooted tree hash (sum of mixed child hashes; equal trees hash equal,
 * collisions are unlikely). unrootedHash takes the min over the 1-2 centroids.
 * ahu gives exact ids (res needs size n): equal ids iff the rooted subtrees are isomorphic.
 * Recursion depth is the tree height.
 * Time: O(N) for hashes, $O(N \log N)$ for ahu
 * Status: stress-tested, Library Checker rooted\_tree\_isomorphism\_classification
 */
#pragma once

typedef unsigned long long ull;
const ull MASK = chrono::steady_clock::now().time_since_epoch().count();
ull mix(ull x){ x ^= MASK; x ^= x << 13; x ^= x >> 7; x ^= x << 17; return x ^ MASK; }
ull treeHash(vector<vi>& g, int u, int p = -1){
  ull h = 1;
  for(int v : g[u]) if(v != p) h += mix(treeHash(g, v, u));
  return h;
}
vi centroids(vector<vi>& g){
  int n = sz(g); vi s(n, 1), c;
  auto dfs = [&](auto&& self, int u, int p) -> void {
    int mx = 0;
    for(int v : g[u]) if(v != p) self(self, v, u), s[u] += s[v], mx = max(mx, s[v]);
    if(2 * max(mx, n - s[u]) <= n) c.push_back(u);
  };
  dfs(dfs, 0, -1); return c;
}
ull unrootedHash(vector<vi>& g){
  ull h = ~0ULL;
  for(int c : centroids(g)) h = min(h, treeHash(g, c));
  return h;
}
map<vi, int> ahuId;
int ahu(vector<vi>& g, vi& res, int u, int p = -1){ // res[v] = id of subtree v
  vi c;
  for(int v : g[u]) if(v != p) c.push_back(ahu(g, res, v, u));
  sort(all(c));
  return res[u] = ahuId.emplace(c, sz(ahuId)).first->second;
}
