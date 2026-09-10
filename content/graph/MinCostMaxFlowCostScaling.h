/**
 * Author: dacin21, adapted to Tideology style
 * Source: https://github.com/ngthanhtrung23/ACM_Notebook_new/blob/master/Graph/MaxFlow/MinCostMaxFlowPR.h
 * Description: Min-cost max-flow using Dinic followed by epsilon cost-scaling push-relabel.
 *  Supports negative costs and negative-cost cycles. Costs are multiplied by N internally;
 *  make sure this and the final answer fit in ll.
 * Usage: Prefer for large total flow, many unit-capacity edges, integer costs, negative
 *  edges/cycles, or min-cost circulation. SSP is usually faster for only a few augmentations.
 *  Not suitable for floating-point costs. For pure circulation, start with any feasible flow
 *  and run only the cost-scaling phase; do not invent s, t or run maxFlow.
 * Time: O(V^2 E + V E log(V C)), where C is the maximum absolute cost
 * Status: Stress-tested against brute force
 */
#pragma once
const ll CS_INF = numeric_limits<ll>::max() / 4;
struct CostScalingMCMF{
  struct edge{
    int from, to, rev;
    ll cap, cost, flow;
  };
  int N;
  vector<vector<edge>>ed;
  vector<ll>excess, pi;
  vi ptr, inq;
  CostScalingMCMF(int N) : N(N), ed(N), excess(N), pi(N), ptr(N), inq(N){}
  // 支援負邊與有限容量負環；不支援負 cost 自環與無界答案。
  void addEdge(int from, int to, ll cap, ll cost){
    if(from == to){
      assert(cost >= 0);
      return;
    }
    assert(-CS_INF / N <= cost && cost <= CS_INF / N);
    cost *= N;
    ed[from].push_back(edge{from, to, sz(ed[to]), cap, cost, 0});
    ed[to].push_back(edge{to, from, sz(ed[from]) - 1, 0, -cost, 0});
  }
  ll residual(edge &e){
    return e.cap - e.flow;
  }
  void push(edge &e, ll fl){
    e.flow += fl;
    ed[e.to][e.rev].flow -= fl;
    excess[e.from] -= fl;
    excess[e.to] += fl;
  }
  bool admissible(edge &e){
    return residual(e) > 0 && pi[e.from] + e.cost - pi[e.to] < 0;
  }
  void relabel(int v, ll eps){
    ll best = -CS_INF;
    ptr[v] = -1;
    rep(i, 0, sz(ed[v])){
      edge &e = ed[v][i];
      if(residual(e) > 0 && best < pi[e.to] - e.cost){
        best = pi[e.to] - e.cost;
        ptr[v] = i;
      }
    }
    assert(ptr[v] != -1);
    pi[v] = best - eps;
  }
  void refine(ll eps){
    fill(all(excess), 0);
    fill(all(ptr), 0);
    fill(all(inq), 0);
    rep(i, 0, N){
      for(edge &e : ed[i]){
        if(admissible(e)) push(e, residual(e));
      }
    }
    queue<int> q;
    rep(i, 0, N){
      if(excess[i] > 0){
        q.push(i);
        inq[i] = 1;
      }
    }
    while(!q.empty()){
      int v = q.front();
      q.pop();
      inq[v] = 0;
      while(excess[v] > 0){
        if(ptr[v] == sz(ed[v])) relabel(v, eps);
        edge &e = ed[v][ptr[v]];
        if(!admissible(e)){
          ++ptr[v];
          continue;
        }
        ll fl = min(excess[v], residual(e));
        int to = e.to;
        push(e, fl);
        if(excess[to] > 0 && !inq[to]){
          q.push(to);
          inq[to] = 1;
        }
      }
    }
  }
  ll maxFlow(int s, int t){
    vi level(N), work(N);
    auto bfs = [&](){
      fill(all(level), -1);
      queue<int> q;
      level[s] = 0;
      q.push(s);
      while(!q.empty()){
        int v = q.front();
        q.pop();
        for(edge &e : ed[v]){
          if(residual(e) > 0 && level[e.to] == -1){
            level[e.to] = level[v] + 1;
            q.push(e.to);
          }
        }
      }
      return level[t] != -1;
    };
    auto dfs = [&](auto &&self, int v, ll pushed) -> ll {
      if(v == t or pushed == 0) return pushed;
      for(int &i = work[v]; i < sz(ed[v]); ++i){
        edge &e = ed[v][i];
        if(level[e.to] != level[v] + 1) continue;
        ll fl = self(self, e.to, min(pushed, residual(e)));
        if(fl == 0) continue;
        e.flow += fl;
        ed[e.to][e.rev].flow -= fl;
        return fl;
      }
      return 0;
    };
    ll flow = 0;
    while(bfs()){
      fill(all(work), 0);
      while(ll fl = dfs(dfs, s, CS_INF)) flow += fl;
    }
    return flow;
  }
  pair<ll, ll> maxflow(int s, int t){
    // 先求任意最大流，再用 circulation 降低費用。
    ll totflow = maxFlow(s, t);
    ll eps = 0;
    rep(i, 0, N){
      for(edge &e : ed[i]){
        eps = max(eps, abs(e.cost));
      }
    }
    while(eps > 0){
      refine(eps);
      if(eps == 1) break;
      eps = max(1LL, eps / 4);
    }
    __int128 totcost = 0;
    rep(i, 0, N){
      for(edge &e : ed[i]){
        totcost += (__int128)e.cost * e.flow;
      }
    }
    return {totflow, (ll)(totcost / 2 / N)};
  }
};
