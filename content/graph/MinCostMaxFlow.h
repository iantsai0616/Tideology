/**
 * Author: Stanford, KACTL
 * Source: Stanford notebook, https://github.com/kth-competitive-programming/kactl
 * Description: Successive shortest path min-cost max-flow using potentials and a PBDS heap.
 *  Call setpi before maxflow if initial residual edges can have negative costs.
 *  Negative-cost cycles are not supported.
 * Usage: Prefer when the number of augmentations is small, or each shortest path can push
 *  a large bottleneck flow. Usually the simplest and fastest default for ordinary MCMF.
 *  Initial negative edges need setpi; negative cycles need the lower-bound transformation
 *  described below, or CostScalingMCMF. PBDS requires GNU GCC/libstdc++.
 * Time: O(F E log V), and O(V E) for setpi
 * Status: Stress-tested by KACTL
 */
#pragma once

const ll MCMF_INF = numeric_limits<ll>::max() / 4;
struct MCMF{
  struct edge{
    int from, to, rev;
    ll cap, cost, flow;
  };
  int N;
  vector<vector<edge>>ed;
  vi seen;
  vector<ll>dist, pi;
  vector<edge*>par;
  MCMF(int N) : N(N), ed(N), seen(N), dist(N), pi(N), par(N){}
  void addEdge(int from, int to, ll cap, ll cost){
    if(from == to) return;
    ed[from].push_back(edge{from, to, sz(ed[to]), cap, cost, 0});
    ed[to].push_back(edge{to, from, sz(ed[from]) - 1, 0, -cost, 0});
  }
  void path(int s){
    fill(all(seen), 0);
    fill(all(dist), MCMF_INF);
    fill(all(par), nullptr);
    dist[s] = 0;
    using PQ = __gnu_pbds::priority_queue<pair<ll, int>, greater<pair<ll, int>>>;
    PQ pq;
    vector<PQ::point_iterator> its(N);
    pq.push({0, s});
    while(!pq.empty()){
      int v = pq.top().S;
      pq.pop();
      seen[v] = 1;
      ll di = dist[v] + pi[v];
      for(edge &e : ed[v]){
        if(seen[e.to]) continue;
        if(e.cap - e.flow <= 0) continue;
        ll val = di - pi[e.to] + e.cost;
        if(val < dist[e.to]){
          dist[e.to] = val;
          par[e.to] = &e;
          if(its[e.to] == pq.end()){
            its[e.to] = pq.push({dist[e.to], e.to});
          }else{
            pq.modify(its[e.to], {dist[e.to], e.to});
          }
        }
      }
    }
    rep(i, 0, N){
      if(dist[i] != MCMF_INF){
        pi[i] = min(pi[i] + dist[i], MCMF_INF);
      }
    }
  }
  pair<ll, ll> maxflow(int s, int t){
    ll totflow = 0, totcost = 0;
    while(path(s), seen[t]){
      ll fl = MCMF_INF;
      for(edge *x = par[t]; x; x = par[x->from]){
        fl = min(fl, x->cap - x->flow);
      }
      totflow += fl;
      for(edge *x = par[t]; x; x = par[x->from]){
        x->flow += fl;
        ed[x->to][x->rev].flow -= fl;
      }
    }
    rep(i, 0, N){
      for(edge &e : ed[i]){
        totcost += e.cost * e.flow;
      }
    }
    return {totflow, totcost / 2};
  }
  // 有負邊先 setpi(s)；換源點或改過流量後要重跑。
  // SSP 不支援負環，這類題改用 CostScalingMCMF。
  void setpi(int s){
    fill(all(pi), MCMF_INF);
    pi[s] = 0;
    int it = N, ch = 1;
    ll v;
    while(ch-- && it--){
      rep(i, 0, N){
        if(pi[i] == MCMF_INF) continue;
        for(edge &e : ed[i]){
          if(e.cap - e.flow <= 0) continue;
          if((v = pi[i] + e.cost) < pi[e.to]){
            pi[e.to] = v;
            ch = 1;
          }
        }
      }
    }
    assert(it >= 0); // negative cost cycle
  }
};
