/**
 * Description: Builds the perpendicular-bisector half-planes of every Voronoi cell from
 * a Delaunay triangulation. Run half-plane intersection to obtain the actual cells.
 * Time: O(N^2) including Delaunay construction
 */
// all coord. is even, you may want to call halfPlaneInter after then
vector<vector<Line>> vec;
void build_voronoi_line(int n, vector<pll> &pts) {
  Delaunay tool(n, pts); // Delaunay
  vec.clear(), vec.resize(n);
  for (int i = 0; i < n; ++i)
    for (auto e : tool.head[i]) {
      int u = tool.oidx[i], v = tool.oidx[e.id];
      pll m = (pts[v] + pts[u]) / 2LL, d = perp(pts[v] - pts[u]);
      vec[u].pb(Line(m, m + d));
    }
}
