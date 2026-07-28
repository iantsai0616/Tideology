const ll inf = numeric_limits<ll>::max() / 4;
struct MCMF {
  struct edge {
    int from, to, rev;
    ll cap, cost, flow;
  };

  int N;
  vector<vector<edge>> ed;
  vi seen;
  vector<ll> dist, pi;
  vector<edge*> par;

  MCMF(int N) : N(N), ed(N), seen(N), dist(N), pi(N), par(N) {}

  void addEdge(int from, int to, ll cap, ll cost) {
    if (from == to) return;
    ed[from].push_back(edge{from, to, sz(ed[to]), cap, cost, 0});
    ed[to].push_back(edge{to, from, sz(ed[from]) - 1, 0, -cost, 0});
  }

  void path(int s) {
    fill(all(seen), 0);
    fill(all(dist), inf);
    fill(all(par), nullptr);

    dist[s] = 0;
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
    pq.push({0, s});

    while (!pq.empty()) {
      auto [d, v] = pq.top();
      pq.pop();

      if (seen[v]) continue;
      seen[v] = 1;

      ll di = dist[v] + pi[v];

      for (edge& e : ed[v]) {
        if (seen[e.to]) continue;
        if (e.cap - e.flow <= 0) continue;

        ll val = di - pi[e.to] + e.cost;

        if (val < dist[e.to]) {
          dist[e.to] = val;
          par[e.to] = &e;
          pq.push({dist[e.to], e.to});
        }
      }
    }

    rep(i,0,N) {
      if (dist[i] != inf) {
        pi[i] = min(pi[i] + dist[i], inf);
      }
    }
  }

  pair<ll, ll> maxflow(int s, int t) {
    ll totflow = 0, totcost = 0;

    while (path(s), seen[t]) {
      ll fl = inf;

      for (edge* x = par[t]; x; x = par[x->from]) {
        fl = min(fl, x->cap - x->flow);
      }

      totflow += fl;

      for (edge* x = par[t]; x; x = par[x->from]) {
        x->flow += fl;
        ed[x->to][x->rev].flow -= fl;
      }
    }

    rep(i,0,N) {
      for (edge& e : ed[i]) {
        totcost += e.cost * e.flow;
      }
    }

    return {totflow, totcost / 2};
  }

  // 如果一開始可能有負費用邊，先呼叫 setpi(s)
  void setpi(int s) {
    fill(all(pi), inf);
    pi[s] = 0;

    int it = N, ch = 1;
    ll v;

    while (ch-- && it--) {
      rep(i,0,N) {
        if (pi[i] == inf) continue;

        for (edge& e : ed[i]) {
          if (!e.cap) continue;

          if ((v = pi[i] + e.cost) < pi[e.to]) {
            pi[e.to] = v;
            ch = 1;
          }
        }
      }
    }
    assert(it >= 0); // negative cost cycle
  }
};