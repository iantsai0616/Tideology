/**
 * Author: Takanori Maehara
 * Source: Library Checker
 * Description: Maximum matching in a general undirected graph.
 * Time: O(N^3)
 * Status: stress-tested, Library Checker
 */
#pragma once

struct GeneralMatching {
  int n, st;
  vector<vi> g;
  vi mt, even, groupBuf;
  vector<pii> nx;
  GeneralMatching(int n) : n(n), g(n), mt(n), even(n), groupBuf(n), nx(n){}
  void addEdge(int a, int b){
    g[a].pb(b); g[b].pb(a);
  }
  int group(int x){
    if(groupBuf[x] == -1 || even[groupBuf[x]] != st) return groupBuf[x];
    return groupBuf[x] = group(groupBuf[x]);
  }
  void rematch(int p, int b){
    int d = mt[p]; mt[p] = b;
    if(d == -1 || mt[d] != p) return;
    if(nx[p].S == -1){
      mt[d] = nx[p].F;
      rematch(nx[p].F, d);
    }else{
      rematch(nx[p].F, nx[p].S);
      rematch(nx[p].S, nx[p].F);
    }
  }
  bool augment(){
    even[st] = st; groupBuf[st] = -1; nx[st] = {-1, -1};
    queue<int> q; q.push(st);
    while(!q.empty()){
      int a = q.front(); q.pop();
      for(int b : g[a]){
        if(b == st) continue;
        if(mt[b] == -1){
          mt[b] = a; rematch(a, b);
          return 1;
        }
        if(even[b] == st){
          int x = group(a), y = group(b), z = -1;
          if(x == y) continue;
          while(x != -1 || y != -1){
            if(y != -1) swap(x, y);
            if(nx[x] == pii(a, b)){
              z = x;
              break;
            }
            nx[x] = {a, b};
            x = group(nx[mt[x]].F);
          }
          for(int v : {group(a), group(b)}){
            while(v != z){
              q.push(v); even[v] = st; groupBuf[v] = z;
              v = group(nx[mt[v]].F);
            }
          }
        }else if(even[mt[b]] != st){
          even[mt[b]] = st; nx[b] = {-1, -1};
          nx[mt[b]] = {a, -1}; groupBuf[mt[b]] = b;
          q.push(mt[b]);
        }
      }
    }
    return 0;
  }
  pair<int, vi> calc(){
    fill(all(mt), -1); fill(all(even), -1); fill(all(groupBuf), 0);
    int ans = 0;
    rep(i, 0, n){
      st = i;
      if(mt[i] == -1) ans += augment();
    }
    return {ans, mt};
  }
};
