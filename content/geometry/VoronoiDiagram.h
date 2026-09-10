/**
 * Description: Voronoi cells as exact integer half-planes.
 * Time: O(n log n)
 * Status: stress-tested
 */
#pragma once

#include "FastDelaunay.h"
#include "HPIGeneralLine.h"

struct VoronoiDiagram {
  vector<P> p;
  vector<vector<IHalfPlane>> cell;
  VoronoiDiagram(const vector<P>& p) : p(p), cell(sz(p)){
    vector<P> s = p;
    sort(all(s)); assert(unique(all(s)) == s.end());
    vector<vi> adj(sz(p));
    auto add = [&](int a, int b){ adj[a].pb(b); adj[b].pb(a); };
    if(sz(p) == 2) add(0, 1);
    if(sz(p) > 2){
      map<P, int> id;
      rep(i, 0, sz(p)) id[p[i]] = i;
      vector<P> tri = triangulate(p);
      for(int i = 0;i < sz(tri);i += 3){
        int a = id[tri[i]], b = id[tri[i + 1]], c = id[tri[i + 2]];
        add(a, b); add(b, c); add(c, a);
      }
      if(tri.empty()){
        vi ord(sz(p)); iota(all(ord), 0);
        sort(all(ord), [&](int a, int b){ return p[a] < p[b]; });
        rep(i, 1, sz(p)) add(ord[i - 1], ord[i]);
      }
    }
    rep(i, 0, sz(p)){
      sort(all(adj[i])); adj[i].erase(unique(all(adj[i])), adj[i].end());
      for(int j : adj[i]) cell[i].pb({
        2*(p[j].x - p[i].x), 2*(p[j].y - p[i].y),
        p[i].dist2() - p[j].dist2()
      });
    }
  }
  vector<DP> polygon(int i, ll inf = (1LL << 60)) const {
    return integerHalfPlaneIntersection(cell[i], inf);
  }
};
