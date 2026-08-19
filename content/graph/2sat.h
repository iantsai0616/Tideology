/**
 * Author: Emil Lenngren, Simon Lindholm
 * Date: 2011-11-29
 * License: CC0
 * Source: folklore
 * Description: Calculates a valid assignment to boolean variables a, b, c, ... to a 2-SAT problem,
 * so that an expression of the type $(a||b)\&\&(!a||c)\&\&(d||!b)\&\&...$
 * becomes true, or reports that it is unsatisfiable.
 * Negated variables are represented by bit-inversions (\texttt{\tilde{}x}).
 * Usage:
 *  TwoSat ts(number of boolean variables);
 *  ts.either(0, \tilde3); // Var 0 is true or var 3 is false
 *  ts.setValue(2); // Var 2 is true
 *  ts.atMostOne({0, \tilde1, 2}); // <= 1 of vars 0, \tilde1 and 2 are true
 *  ts.solve(); // Returns true iff it is solvable
 *  ts.values[0..N-1] holds the assigned values to the vars
 * Time: O(N+E), where N is the number of boolean variables, and E is the number of clauses.
 * Status: stress-tested
 */
#pragma once

struct TwoSat {
  int N;
  vector<vi> gr;
  vi values; // 0 = false, 1 = true

  TwoSat(int n = 0) : N(n), gr(2*n){}

  int addVar(){ // (optional)
    gr.emplace_back();
    gr.emplace_back();
    return N++;
  }

  void either(int f, int j){
    f = max(2*f, -1-2*f);
    j = max(2*j, -1-2*j);
    gr[f].push_back(j^1);
    gr[j].push_back(f^1);
  }
  void setValue(int x){ either(x, x); }

  void atMostOne(const vi& li){ // (optional)
    if(sz(li) <= 1) return;
    int cur = ~li[0];
    rep(i, 2, sz(li)){
      int next = addVar();
      either(cur, ~li[i]);
      either(cur, next);
      either(~li[i], next);
      cur = ~next;
    }
    either(cur, ~li[1]);
  }

  bool solve(){
    vector<vi> rg(2*N); vi vis(2*N), ord, comp(2*N, -1);
    rep(i, 0, 2*N) for(int j : gr[i]) rg[j].pb(i);
    rep(s, 0, 2*N) if(!vis[s]){
      vector<pii> st = {{s, 0}}; vis[s] = 1;
      while(!st.empty()){
        int u = st.back().F;
        if(st.back().S < sz(gr[u])){
          int v = gr[u][st.back().S++];
          if(!vis[v]) vis[v] = 1, st.pb({v, 0});
        }else ord.pb(u), st.pop_back();
      }
    }
    int c = 0;
    for(int oi = sz(ord); oi--;){
      int s = ord[oi]; if(comp[s] != -1) continue;
      vi st = {s}; comp[s] = c;
      while(!st.empty()){
        int u = st.back(); st.pop_back();
        for(int v : rg[u]) if(comp[v] == -1) comp[v] = c, st.pb(v);
      }
      ++c;
    }
    values.resize(N);
    rep(i, 0, N){
      if(comp[2*i] == comp[2*i+1]) return 0;
      values[i] = comp[2*i] < comp[2*i+1];
    }
    return 1;
  }
};
